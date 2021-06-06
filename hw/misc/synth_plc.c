#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include <unistd.h>
#include "monitor/monitor.h"
#include "qapi/qapi-events-misc.h" 
#include "exec/synth_controller.h"
#include "exec/taint.h"
#include "hw/misc/synth_plc.h"

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

static void synth_write_block2(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_block2.addr + addr, val);
}

static uint64_t synth_read_block2(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_block2.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_block2 =
{
    .write = synth_write_block2,
    .read = synth_read_block2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};



static void synth_write_fsmc_control_register(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_fsmc_control_register.addr + addr, val);
}

static uint64_t synth_read_fsmc_control_register(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_fsmc_control_register.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_fsmc_control_register =
{
    .write = synth_write_fsmc_control_register,
    .read = synth_read_fsmc_control_register,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};


static void synth_write_block3(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_block3.addr + addr, val);
}

static uint64_t synth_read_block3(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_block3.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_block3 =
{
    .write = synth_write_block3,
    .read = synth_read_block3,
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
        &sio->io_block1, obj, &synth_io_ops_block1, sio, TYPE_SYNTH, 0x80000
    );
    sysbus_init_mmio(dev, &sio->io_block1);
    memory_region_add_subregion(sysbus, 0x40000000, &sio->io_block1);



    memory_region_init_io(
        &sio->io_block2, obj, &synth_io_ops_block2, sio, TYPE_SYNTH, 0x60C00
    );
    sysbus_init_mmio(dev, &sio->io_block2);
    memory_region_add_subregion(sysbus, 0x50000000, &sio->io_block2);



    memory_region_init_io(
        &sio->io_fsmc_control_register, obj, &synth_io_ops_fsmc_control_register, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_fsmc_control_register);
    memory_region_add_subregion(sysbus, 0xA0000000, &sio->io_fsmc_control_register);
    
    if (use_robot_dma == 1){
        memory_region_init_io(
            &sio->io_block3, obj, &synth_io_ops_block3, sio, TYPE_SYNTH, 0x4
        );
        sysbus_init_mmio(dev, &sio->io_block3);
        memory_region_add_subregion_overlap(sysbus, 0x20000018, &             sio->io_block3, 10);
    }
   
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
