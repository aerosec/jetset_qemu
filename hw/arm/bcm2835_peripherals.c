/*
 * Raspberry Pi emulation (c) 2012 Gregory Estrade
 * Upstreaming code cleanup [including bcm2835_*] (c) 2013 Jan Petrous
 *
 * Rasperry Pi 2 emulation and refactoring Copyright (c) 2015, Microsoft
 * Written by Andrew Baumann
 *
 * This code is licensed under the GNU GPLv2 and later.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/arm/bcm2835_peripherals.h"
#include "hw/misc/bcm2835_mbox_defs.h"
#include "hw/arm/raspi_platform.h"
#include "sysemu/sysemu.h"

/* Peripheral base address on the VC (GPU) system bus */
#define BCM2835_VC_PERI_BASE 0x7e000000

/* Capabilities for SD controller: no DMA, high-speed, default clocks etc. */
//#define BCM2835_SDHC_CAPAREG 0x52134b4

static void bcm2835_peripherals_init(Object *obj)
{
    BCM2835PeripheralState *s = BCM2835_PERIPHERALS(obj);

    /* Memory region for peripheral devices, which we export to our parent */
    memory_region_init(&s->peri_mr, obj,"bcm2835-peripherals", 0x1000000);
    object_property_add_child(obj, "peripheral-io", OBJECT(&s->peri_mr), NULL);
    sysbus_init_mmio(SYS_BUS_DEVICE(s), &s->peri_mr);

    /* Internal memory region for peripheral bus addresses (not exported) */
    memory_region_init(&s->gpu_bus_mr, obj, "bcm2835-gpu", (uint64_t)1 << 32);
    object_property_add_child(obj, "gpu-bus", OBJECT(&s->gpu_bus_mr), NULL);

    /* Internal memory region for request/response communication with
     * mailbox-addressable peripherals (not exported)
     */
    memory_region_init(&s->mbox_mr, obj, "bcm2835-mbox",
                       MBOX_CHAN_COUNT << MBOX_AS_CHAN_SHIFT);
    
    /* Mailboxes */
    
    object_initialize(&s->mboxes, sizeof(s->mboxes), TYPE_BCM2835_MBOX);
    object_property_add_child(obj, "mbox", OBJECT(&s->mboxes), NULL);
    qdev_set_parent_bus(DEVICE(&s->mboxes), sysbus_get_default());

    object_property_add_const_link(OBJECT(&s->mboxes), "mbox-mr",
                                   OBJECT(&s->mbox_mr), &error_abort);

    
    /* Framebuffer */
    
    object_initialize(&s->fb, sizeof(s->fb), TYPE_BCM2835_FB);
    object_property_add_child(obj, "fb", OBJECT(&s->fb), NULL);
    object_property_add_alias(obj, "vcram-size", OBJECT(&s->fb), "vcram-size",
                              &error_abort);
    qdev_set_parent_bus(DEVICE(&s->fb), sysbus_get_default());
  
    object_property_add_const_link(OBJECT(&s->fb), "dma-mr",
                                   OBJECT(&s->gpu_bus_mr), &error_abort);
    
    /* Property channel */
    
    object_initialize(&s->property, sizeof(s->property), TYPE_BCM2835_PROPERTY);
    object_property_add_child(obj, "property", OBJECT(&s->property), NULL);
    object_property_add_alias(obj, "board-rev", OBJECT(&s->property),
                              "board-rev", &error_abort);
    qdev_set_parent_bus(DEVICE(&s->property), sysbus_get_default());
    
    object_property_add_const_link(OBJECT(&s->property), "fb",
                                   OBJECT(&s->fb), &error_abort);
    object_property_add_const_link(OBJECT(&s->property), "dma-mr",
                                   OBJECT(&s->gpu_bus_mr), &error_abort);


    
}

static void bcm2835_peripherals_realize(DeviceState *dev, Error **errp)
{
    BCM2835PeripheralState *s = BCM2835_PERIPHERALS(dev);
    Object *obj;
    MemoryRegion *ram;
    Error *err = NULL;
    uint64_t ram_size, vcram_size;
    int n;

    obj = object_property_get_link(OBJECT(dev), "ram", &err);
    if (obj == NULL) {
        error_setg(errp, "%s: required ram link not found: %s",
                   __func__, error_get_pretty(err));
        return;
    }

    ram = MEMORY_REGION(obj);
    ram_size = memory_region_size(ram);

    /* Map peripherals and RAM into the GPU address space. */
    memory_region_init_alias(&s->peri_mr_alias, OBJECT(s),
                             "bcm2835-peripherals", &s->peri_mr, 0,
                             memory_region_size(&s->peri_mr));

    memory_region_add_subregion_overlap(&s->gpu_bus_mr, BCM2835_VC_PERI_BASE,
                                        &s->peri_mr_alias, 1);

    /* RAM is aliased four times (different cache configurations) on the GPU */
    
    for (n = 0; n < 4; n++) {
        memory_region_init_alias(&s->ram_alias[n], OBJECT(s),
                                 "bcm2835-gpu-ram-alias[*]", ram, 0, ram_size);
        memory_region_add_subregion_overlap(&s->gpu_bus_mr, (hwaddr)n << 30,
                                            &s->ram_alias[n], 0);
    }

    /* Mailboxes */
    
    object_property_set_bool(OBJECT(&s->mboxes), true, "realized", &err);
    if (err) {
        error_propagate(errp, err);
        return;
    }

    memory_region_add_subregion(&s->peri_mr, ARMCTRL_0_SBM_OFFSET,
                sysbus_mmio_get_region(SYS_BUS_DEVICE(&s->mboxes), 0));
    sysbus_pass_irq(SYS_BUS_DEVICE(s), SYS_BUS_DEVICE(&s->mboxes));

    /* Framebuffer */
    vcram_size = object_property_get_uint(OBJECT(s), "vcram-size", &err);
    
    if (err) {
        error_propagate(errp, err);
        return;
    }

    object_property_set_uint(OBJECT(&s->fb), ram_size - vcram_size,
                             "vcram-base", &err);
    if (err) {
        error_propagate(errp, err);
        return;
    }

    object_property_set_bool(OBJECT(&s->fb), true, "realized", &err);
    if (err) {
        error_propagate(errp, err);
        return;
    }
 
    memory_region_add_subregion(&s->mbox_mr, MBOX_CHAN_FB << MBOX_AS_CHAN_SHIFT,
                sysbus_mmio_get_region(SYS_BUS_DEVICE(&s->fb), 0));
    sysbus_connect_irq(SYS_BUS_DEVICE(&s->fb), 0,
                       qdev_get_gpio_in(DEVICE(&s->mboxes), MBOX_CHAN_FB));
    
    /* Property channel */
    
    object_property_set_bool(OBJECT(&s->property), true, "realized", &err);
    if (err) {
        error_propagate(errp, err);
        return;
    }

    memory_region_add_subregion(&s->mbox_mr,
                MBOX_CHAN_PROPERTY << MBOX_AS_CHAN_SHIFT,
                sysbus_mmio_get_region(SYS_BUS_DEVICE(&s->property), 0));
    sysbus_connect_irq(SYS_BUS_DEVICE(&s->property), 0,
                      qdev_get_gpio_in(DEVICE(&s->mboxes), MBOX_CHAN_PROPERTY));
    
}

static void bcm2835_peripherals_class_init(ObjectClass *oc, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize = bcm2835_peripherals_realize;
}

static const TypeInfo bcm2835_peripherals_type_info = {
    .name = TYPE_BCM2835_PERIPHERALS,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(BCM2835PeripheralState),
    .instance_init = bcm2835_peripherals_init,
    .class_init = bcm2835_peripherals_class_init,
};

static void bcm2835_peripherals_register_types(void)
{
    type_register_static(&bcm2835_peripherals_type_info);
}

type_init(bcm2835_peripherals_register_types)
