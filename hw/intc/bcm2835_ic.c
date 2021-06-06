/*
 * Raspberry Pi emulation (c) 2012 Gregory Estrade
 * Refactoring for Pi2 Copyright (c) 2015, Microsoft. Written by Andrew Baumann.
 * This code is licensed under the GNU GPLv2 and later.
 * Heavily based on pl190.c, copyright terms below:
 *
 * Arm PrimeCell PL190 Vector Interrupt Controller
 *
 * Copyright (c) 2006 CodeSourcery.
 * Written by Paul Brook
 *
 * This code is licensed under the GPL.
 */

#include "qemu/osdep.h"
#include "hw/intc/bcm2835_ic.h"
#include "qemu/log.h"

#define GPU_IRQS 64
#define ARM_IRQS 8

static void bcm2835_ic_set_arm_irq(void *opaque, int irq, int level)
{
    BCM2835ICState *s = opaque;
    s->arm_irq_level = 0;

    if (level){
        s->arm_irq_level |= 1 << irq;
    }
    
    qemu_set_irq(s->irq, s->arm_irq_level != 0);

}

static uint64_t bcm2835_ic_read(void *opaque, hwaddr offset, unsigned size)
{
    BCM2835ICState *s = opaque;
    return s->arm_irq_level;
}

static void bcm2835_ic_write(void *opaque, hwaddr offset, uint64_t val,
                             unsigned size)
{

    printf("wow IM A BCM WRITE val = 0x%lx\n", val);
    BCM2835ICState *s = opaque;
    s->arm_irq_enable |= val & 0xff;
}

static const MemoryRegionOps bcm2835_ic_ops = {
    .read = bcm2835_ic_read,
    .write = bcm2835_ic_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};

static void bcm2835_ic_reset(DeviceState *d)
{
    BCM2835ICState *s = BCM2835_IC(d);

    s->gpu_irq_enable = 0;
    s->arm_irq_enable = 0;
    s->fiq_enable = false;
    s->fiq_select = 0;
}

static void bcm2835_ic_init(Object *obj)
{
    BCM2835ICState *s = BCM2835_IC(obj);

    memory_region_init_io(&s->iomem, obj, &bcm2835_ic_ops, s, TYPE_BCM2835_IC,
                          0x200);
    sysbus_init_mmio(SYS_BUS_DEVICE(s), &s->iomem);

    qdev_init_gpio_in_named(DEVICE(s), bcm2835_ic_set_arm_irq,
                            BCM2835_IC_ARM_IRQ, ARM_IRQS);

    sysbus_init_irq(SYS_BUS_DEVICE(s), &s->irq);
    sysbus_init_irq(SYS_BUS_DEVICE(s), &s->fiq);
}

static void bcm2835_ic_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    dc->reset = bcm2835_ic_reset;
}

static TypeInfo bcm2835_ic_info = {
    .name          = TYPE_BCM2835_IC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(BCM2835ICState),
    .class_init    = bcm2835_ic_class_init,
    .instance_init = bcm2835_ic_init,
};

static void bcm2835_ic_register_types(void)
{
    type_register_static(&bcm2835_ic_info);
}

type_init(bcm2835_ic_register_types)
