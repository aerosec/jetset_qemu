#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include <unistd.h>
#include "monitor/monitor.h"
#include "qapi/qapi-events-misc.h" 
#include "exec/synth_controller.h"
#include "exec/taint.h"
#include "hw/misc/simple_synth.h"

static void simple_synth_write(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SimpleSynthState *st = opaque;
    taint_mmio_write(st->mmio.addr + addr, val);
}

static uint64_t simple_synth_read(void *opaque, hwaddr addr, unsigned size) {
    SimpleSynthState* st = opaque;
    return taint_mmio_read(st->mmio.addr + addr, size);
}

static const MemoryRegionOps simple_synth_mmio_ops =
{
    .write = simple_synth_write,
    .read = simple_synth_read,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void simple_synth_init(Object *d){}

static void simple_synth_realize(DeviceState *d, Error **errp)
{
    SysBusDevice *dev = SYS_BUS_DEVICE(d);
    SimpleSynthState *st = SIMPLE_SYNTH(d);
    Object *obj = OBJECT(st);
    MemoryRegion *sysbus = sysbus_address_space(dev);

    memory_region_init_io(
        &st->mmio, obj, &simple_synth_mmio_ops, st, TYPE_SIMPLE_SYNTH, st->size
    );
    sysbus_init_mmio(dev, &st->mmio);
    memory_region_add_subregion(sysbus, st->base_addr, &st->mmio);
}

static void simple_synth_reset(DeviceState *d)
{
    SimpleSynthState *st = SIMPLE_SYNTH(d);
}

static Property simple_synth_properties[] = {
    DEFINE_PROP_UINT32("size", SimpleSynthState, size,   0),
    DEFINE_PROP_UINT32("base_addr", SimpleSynthState, base_addr,   0),
    DEFINE_PROP_END_OF_LIST(),
};

static void simple_synth_class_init(ObjectClass *klass, void *data)
{
        DeviceClass *dc = DEVICE_CLASS(klass);
        dc->realize = simple_synth_realize;
        dc->reset = simple_synth_reset;
        dc->props = simple_synth_properties;
        set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

static const TypeInfo simple_synth_info =
{
        .name           = TYPE_SIMPLE_SYNTH,
        .parent         = TYPE_SYS_BUS_DEVICE,
        .instance_size  = sizeof(SimpleSynthState),
        .instance_init  = simple_synth_init,
        .class_init     = simple_synth_class_init,
};
static void simple_synth_register_types(void)
{
        type_register_static(&simple_synth_info);
}

type_init(simple_synth_register_types)
