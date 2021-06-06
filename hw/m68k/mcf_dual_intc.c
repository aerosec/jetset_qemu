/*
 * ColdFire dual Interrupt Controller emulation.
 *
 * Copyright (c) 2007 CodeSourcery.
 *
 * This code is licensed under the GPL
 */

#include "qemu/osdep.h"
#include "qemu/module.h"
#include "cpu.h"
#include "hw/hw.h"
#include "hw/sysbus.h"
#include "hw/m68k/mcf.h"

#define TYPE_MCF_DUAL_INTC "mcf-dual-intc"
#define MCF_DUAL_INTC(obj) OBJECT_CHECK(mcf_dual_intc_state, (obj), TYPE_MCF_DUAL_INTC)

typedef struct {
    SysBusDevice parent_obj;
    MemoryRegion giack_iomem;

    struct {
        MemoryRegion iomem;
        uint64_t ipr;
        uint64_t imr;
        uint64_t ifr;
        uint64_t enabled;
        uint8_t icr[64];
        int active_vector;
    } single[2];

    int active_vector;
    M68kCPU *cpu;
} mcf_dual_intc_state;

static void mcf_dual_intc_update(mcf_dual_intc_state *s)
{
    uint64_t active;
    int i;
    int best;
    int best_level;
    int best_levels[2];

    for (unsigned char id = 0; id < 2; id++) {
        active = (s->single[id].ipr | s->single[id].ifr) & s->single[id].enabled & ~s->single[id].imr;
        best_level = 0;
        best = 64;
        if (active) {
            for (i = 0; i < 64; i++) {
                if ((active & 1) != 0 && s->single[id].icr[i] >= best_level) {
                    best_level = s->single[id].icr[i];
                    best = i;
                }
                active >>= 1;
            }
        }
        s->single[id].active_vector = ((best == 64) ? 24 : (best + 64 * i));
        best_levels[id] = best_level;
    }

    if (best_levels[0] >= best_levels[1]) {
        m68k_set_irq_level(s->cpu, best_levels[0], s->single[0].active_vector);
        s->active_vector = s->single[0].active_vector;
    } else {
        m68k_set_irq_level(s->cpu, best_levels[1], s->single[1].active_vector);
        s->active_vector = s->single[1].active_vector;
    }
}

static uint64_t mcf_dual_intc_read_common(void *opaque, hwaddr addr,
                                          unsigned size, unsigned char id)
{
    int offset;
    mcf_dual_intc_state *s = (mcf_dual_intc_state *)opaque;
    offset = addr & 0xff;
    if (offset >= 0x40 && offset < 0x80) {
        return s->single[id].icr[offset - 0x40];
    }
    switch (offset) {
    case 0x00:
        return (uint32_t)(s->single[id].ipr >> 32);
    case 0x04:
        return (uint32_t)s->single[id].ipr;
    case 0x08:
        return (uint32_t)(s->single[id].imr >> 32);
    case 0x0c:
        return (uint32_t)s->single[id].imr;
    case 0x10:
        return (uint32_t)(s->single[id].ifr >> 32);
    case 0x14:
        return (uint32_t)s->single[id].ifr;
    case 0xe0: /* SWIACK.  */
        return s->single[id].active_vector;
    case 0xe4: case 0xe8: case 0xec: case 0xf0:
    case 0xf4: case 0xf8: case 0xfc:
        /* LnIACK */
        hw_error("mcf_dual_intc_read: LnIACK not implemented\n");
    default:
        return 0;
    }
}

static void mcf_dual_intc_write_common(void *opaque, hwaddr addr,
                                       uint64_t val, unsigned size, unsigned char id)
{
    int offset;
    mcf_dual_intc_state *s = (mcf_dual_intc_state *)opaque;
    offset = addr & 0xff;
    if (offset >= 0x40 && offset < 0x80) {
        int n = offset - 0x40;
        s->single[id].icr[n] = val;
        if (val == 0)
            s->single[id].enabled &= ~(1ull << n);
        else
            s->single[id].enabled |= (1ull << n);
        mcf_dual_intc_update(s);
        return;
    }
    switch (offset) {
    case 0x00: case 0x04:
        /* Ignore IPR writes.  */
        return;
    case 0x08:
        s->single[id].imr = (s->single[id].imr & 0xffffffff) | ((uint64_t)val << 32);
        break;
    case 0x0c:
        s->single[id].imr = (s->single[id].imr & 0xffffffff00000000ull) | (uint32_t)val;
        break;
    case 0x1c:
        if (val & 0x40) {
            s->single[id].imr = ~0ull;
        } else {
            s->single[id].imr |= (0x1ull << (val & 0x3f));
        }
        break;
    case 0x1d:
        if (val & 0x40) {
            s->single[id].imr = 0ull;
        } else {
            s->single[id].imr &= ~(0x1ull << (val & 0x3f));
        }
        break;
    default:
        hw_error("mcf_dual_intc_write: Bad write offset %d\n", offset);
        break;
    }
    mcf_dual_intc_update(s);
}

static uint64_t mcf_dual_intc_read_intc0(void *opaque, hwaddr addr,
                                         unsigned size)
{
    return mcf_dual_intc_read_common(opaque, addr, size, 0);
}

static void mcf_dual_intc_write_intc0(void *opaque, hwaddr addr,
                                      uint64_t val, unsigned size)
{
    return mcf_dual_intc_write_common(opaque, addr, val, size, 0);
}

static uint64_t mcf_dual_intc_read_intc1(void *opaque, hwaddr addr,
                                         unsigned size)
{
    return mcf_dual_intc_read_common(opaque, addr, size, 1);
}

static void mcf_dual_intc_write_intc1(void *opaque, hwaddr addr,
                                      uint64_t val, unsigned size)
{
    return mcf_dual_intc_write_common(opaque, addr, val, size, 1);
}

static uint64_t mcf_dual_intc_read_giack(void *opaque, hwaddr addr,
                                         unsigned size)
{
    int offset;
    mcf_dual_intc_state *s = (mcf_dual_intc_state *)opaque;
    offset = addr & 0xff;
    switch (offset) {
    case 0xe0: /* SWIACK.  */
        return s->active_vector;
    case 0xe4: case 0xe8: case 0xec: case 0xf0:
    case 0xf4: case 0xf8: case 0xfc:
        /* LnIACK */
        hw_error("mcf_dual_intc_read: GLnIACK not implemented\n");
    default:
        return 0;
    }
}

static void mcf_dual_intc_write_giack(void *opaque, hwaddr addr,
                                      uint64_t val, unsigned size)
{
    int offset;
    mcf_dual_intc_state *s = (mcf_dual_intc_state *)opaque;
    offset = addr & 0xff;
    switch (offset) {
    default:
        hw_error("mcf_dual_intc_write: Bad write offset %d\n", offset);
        break;
    }
    mcf_dual_intc_update(s);
}


static void mcf_dual_intc_set_irq(void *opaque, int irq, int level)
{
    mcf_dual_intc_state *s = (mcf_dual_intc_state *)opaque;
    if (irq >= 128 || irq < 0)
        return;

    unsigned char id = irq / 64;
    irq %= 64;

    if (level)
        s->single[id].ipr |= 1ull << irq;
    else
        s->single[id].ipr &= ~(1ull << irq);
    mcf_dual_intc_update(s);
}

static void mcf_dual_intc_reset(DeviceState *dev)
{
    mcf_dual_intc_state *s = MCF_DUAL_INTC(dev);

    for (unsigned char id = 0; id < 2; id++) {
        s->single[id].imr = ~0ull;
        s->single[id].ipr = 0;
        s->single[id].ifr = 0;
        s->single[id].enabled = 0;
        memset(s->single[id].icr, 0, 64);
        s->single[id].active_vector = 24;
    }
}

static const MemoryRegionOps mcf_dual_intc_ops_intc0 = {
    .read = mcf_dual_intc_read_intc0,
    .write = mcf_dual_intc_write_intc0,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static const MemoryRegionOps mcf_dual_intc_ops_intc1 = {
    .read = mcf_dual_intc_read_intc1,
    .write = mcf_dual_intc_write_intc1,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static const MemoryRegionOps mcf_dual_intc_ops_giack = {
    .read = mcf_dual_intc_read_giack,
    .write = mcf_dual_intc_write_giack,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void mcf_dual_intc_instance_init(Object *obj)
{
    mcf_dual_intc_state *s = MCF_DUAL_INTC(obj);

    memory_region_init_io(&s->single[0].iomem, obj, &mcf_dual_intc_ops_intc0, s, "mcf", 0x100);
    memory_region_init_io(&s->single[1].iomem, obj, &mcf_dual_intc_ops_intc1, s, "mcf", 0x100);
    memory_region_init_io(&s->giack_iomem, obj, &mcf_dual_intc_ops_giack, s, "mcf", 0x100);
}

static void mcf_dual_intc_class_init(ObjectClass *oc, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    set_bit(DEVICE_CATEGORY_MISC, dc->categories);
    dc->reset = mcf_dual_intc_reset;
}

static const TypeInfo mcf_dual_intc_gate_info = {
    .name          = TYPE_MCF_DUAL_INTC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(mcf_dual_intc_state),
    .instance_init = mcf_dual_intc_instance_init,
    .class_init    = mcf_dual_intc_class_init,
};

static void mcf_dual_intc_register_types(void)
{
    type_register_static(&mcf_dual_intc_gate_info);
}

type_init(mcf_dual_intc_register_types)

qemu_irq *mcf_dual_intc_init(MemoryRegion *sysmem,
                             hwaddr base0,
                             hwaddr base1,
                             hwaddr base_giack,
                             M68kCPU *cpu)
{
    DeviceState  *dev;
    mcf_dual_intc_state *s;

    dev = qdev_create(NULL, TYPE_MCF_DUAL_INTC);
    qdev_init_nofail(dev);

    s = MCF_DUAL_INTC(dev);
    s->cpu = cpu;

    memory_region_add_subregion(sysmem, base0, &s->single[0].iomem);
    memory_region_add_subregion(sysmem, base1, &s->single[1].iomem);
    memory_region_add_subregion(sysmem, base_giack, &s->giack_iomem);

    return qemu_allocate_irqs(mcf_dual_intc_set_irq, s, 64 * 2);
}
