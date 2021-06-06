#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include <unistd.h>
#include "monitor/monitor.h"
#include "qapi/qapi-events-misc.h" 
#include "exec/synth_controller.h"
#include "exec/taint.h"
#include "hw/misc/synth_sam3x8e.h"

static void synth_write_block1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_block1.addr + addr, val);
}

static uint64_t synth_read_block1(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_block1.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_block1 =
{
    .write = synth_write_block1,
    .read = synth_read_block1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_init(Object *d){}

static void synth_realize(DeviceState *d, Error **errp)
{
    SysBusDevice *dev = SYS_BUS_DEVICE(d);
    SynthState *sio = SYNTH(d);
    Object *obj = OBJECT(sio);
    MemoryRegion *sysbus = sysbus_address_space(dev);

    memory_region_init_io(
        &sio->io_block1, obj, &synth_io_ops_block1, sio, TYPE_SYNTH, 0x1FFFFFFF
    );
    sysbus_init_mmio(dev, &sio->io_block1);
    memory_region_add_subregion(sysbus, 0x40000000, &sio->io_block1);

}

static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);
}

static void synth_class_init(ObjectClass *klass, void *data)
{
        DeviceClass *dc = DEVICE_CLASS(klass);
        dc->realize = synth_realize;
        dc->reset = synth_reset;
        set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

static const TypeInfo synth_info =
{
        .name           = TYPE_SYNTH,
        .parent         = TYPE_SYS_BUS_DEVICE,
        .instance_size  = sizeof(SynthState),
        .instance_init  = synth_init,
        .class_init     = synth_class_init,
};
static void synth_register_types(void)
{
        type_register_static(&synth_info);
}

type_init(synth_register_types)
