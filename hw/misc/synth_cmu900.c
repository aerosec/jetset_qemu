
#include "qemu/osdep.h" 
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>
#include "qapi/qapi-events-misc.h"
#include "exec/synth_controller.h"
#include "exec/taint.h"

#define TYPE_SYNTH "synth_cmu900"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
#define NUM_IRQS 64

int global_idx = 0;

typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;

 
    MemoryRegion io0; 
    uint32_t index0;
 
    MemoryRegion io1; 
    uint32_t index1;
 
    MemoryRegion io2; 
    uint32_t index2;
 
    MemoryRegion io3; 
    uint32_t index3;
 
    MemoryRegion io4; 
    uint32_t index4;
 
    MemoryRegion io5; 
    uint32_t index5;
 
    MemoryRegion io6; 
    uint32_t index6;
 
    MemoryRegion io7; 
    uint32_t index7;
 
    MemoryRegion io8; 
    uint32_t index8;
} SynthState;

static void synth_write0(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io0.addr + addr, val);
}

int io_read_idx0 = 0;
int num_recorded_reads0 = 0;

static uint64_t synth_read0(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    taint_ioport_read(sio->io0.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops0 =
{
    .write = synth_write0,
    .read = synth_read0,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write1(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io1.addr + addr, val);
}

int io_read_idx1 = 0;
int num_recorded_reads1 = 0;

static uint64_t synth_read1(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    taint_ioport_read(sio->io1.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops1 =
{
    .write = synth_write1,
    .read = synth_read1,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write2(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io2.addr + addr, val);
}

int io_read_idx2 = 0;
int num_recorded_reads2 = 240;

static uint64_t synth_read2(void *opaque, hwaddr addr, unsigned size) {
	SynthState* sio = opaque;
    taint_ioport_read(sio->io2.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops2 =
{
    .write = synth_write2,
    .read = synth_read2,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write3(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io3.addr + addr, val);
}

int io_read_idx3 = 0;
int num_recorded_reads3 = 5;

static uint64_t synth_read3(void *opaque, hwaddr addr, unsigned size) {
	SynthState* sio = opaque;
    taint_ioport_read(sio->io3.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops3 =
{
    .write = synth_write3,
    .read = synth_read3,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write4(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io4.addr + addr, val);
}

int io_read_idx4 = 0;
int num_recorded_reads4 = 0;

static uint64_t synth_read4(void *opaque, hwaddr addr, unsigned size) {
	SynthState* sio = opaque;
    taint_ioport_read(sio->io4.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops4 =
{
    .write = synth_write4,
    .read = synth_read4,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write5(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io5.addr + addr, val);
}

int io_read_idx5 = 0;
int num_recorded_reads5 = 5;

static uint64_t synth_read5(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    taint_ioport_read(sio->io5.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops5 =
{
    .write = synth_write5,
    .read = synth_read5,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write6(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io0.addr + addr, val);
}

int io_read_idx6 = 0;
int num_recorded_reads6 = 4;

static uint64_t synth_read6(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    taint_ioport_read(sio->io6.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops6 =
{
    .write = synth_write6,
    .read = synth_read6,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write7(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_ioport_write( sio->io7.addr + addr, val);
}

int io_read_idx7 = 0;
int num_recorded_reads7 = 0;

static uint64_t synth_read7(void *opaque, hwaddr addr, unsigned size) 
{
    SynthState* sio = opaque;
    taint_ioport_read(sio->io7.addr + addr, size);
    return 0xffffffff;
}

static const MemoryRegionOps synth_io_ops7 =
{
    .write = synth_write7,
    .read = synth_read7,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_write8(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_mmio_write(sio->io8.addr + addr, size);
}

int io_read_idx8 = 0;
int num_recorded_reads8 = 1;

static uint64_t synth_read8(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io8.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops8 =
{
    .write = synth_write8,
    .read = synth_read8,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_LITTLE_ENDIAN,
};

static void synth_init(Object *d){}

static void set_irq(void *opaque, int irq, int level)
{
    SynthState* sio = opaque;
    qemu_irq_raise(sio->irq_set[irq]);
}

static void synth_realize(DeviceState *d, Error **errp)
{
    SysBusDevice *dev = SYS_BUS_DEVICE(d);
    SynthState *sio = SYNTH(d);
    Object *obj = OBJECT(sio);
    MemoryRegion *sysbus = sysbus_address_space(dev);
    int idx;
    
    memory_region_init_io(&sio->io0, OBJECT(sio), &synth_io_ops0, sio, TYPE_SYNTH, 2);
    sysbus_init_ioports(dev, 0x0, 2);
    sysbus_add_io(dev, 0x0, &sio->io0);

    memory_region_init_io(&sio->io1, OBJECT(sio), &synth_io_ops1, sio, TYPE_SYNTH, 4);
    sysbus_init_ioports(dev, 0x1000, 4);
    sysbus_add_io(dev, 0x1000, &sio->io1);

    memory_region_init_io(&sio->io2, OBJECT(sio), &synth_io_ops2, sio, TYPE_SYNTH, 3);
    sysbus_init_ioports(dev, 0x2004, 3);
    sysbus_add_io(dev, 0x2004, &sio->io2);

    memory_region_init_io(&sio->io3, OBJECT(sio), &synth_io_ops3, sio, TYPE_SYNTH, 2);
    sysbus_init_ioports(dev, 0x3000, 2);
    sysbus_add_io(dev, 0x3000, &sio->io3);

    memory_region_init_io(&sio->io4, OBJECT(sio), &synth_io_ops4, sio, TYPE_SYNTH, 1);
    sysbus_init_ioports(dev, 0x4000, 1);
    sysbus_add_io(dev, 0x4000, &sio->io4);

    memory_region_init_io(&sio->io5, OBJECT(sio), &synth_io_ops5, sio, TYPE_SYNTH, 1);
    sysbus_init_ioports(dev, 0x5000, 1);
    sysbus_add_io(dev, 0x5000, &sio->io5);

    memory_region_init_io(&sio->io6, OBJECT(sio), &synth_io_ops6, sio, TYPE_SYNTH, 1);
    sysbus_init_ioports(dev, 0x6000, 1);
    sysbus_add_io(dev, 0x6000, &sio->io6);

    memory_region_init_io(&sio->io7, OBJECT(sio), &synth_io_ops7, sio, TYPE_SYNTH, 1);
    sysbus_init_ioports(dev, 0x7000, 1);
    sysbus_add_io(dev, 0x7000, &sio->io7);
  
    memory_region_init_io(&sio->io8, obj, &synth_io_ops8, sio, TYPE_SYNTH, 0x1400a4);
    sysbus_init_mmio(dev, &sio->io8);
    memory_region_add_subregion(sysbus, 0x21d00000, &sio->io8);

    sio->irq_set = g_new0(qemu_irq, NUM_IRQS);
    qdev_init_gpio_out(d, sio->irq_set, NUM_IRQS);
    qdev_init_gpio_in(d, set_irq, NUM_IRQS);

    qdev_connect_gpio_out(d, 0, pc_allocate_cpu_irq());

    for (idx = 0 ; idx < NUM_IRQS; idx++) {
        sio->irq_set[idx] = qdev_get_gpio_in(d, idx);
    }

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;
        sio->index0 = 0;
    sio->index1 = 0;
    sio->index2 = 0;
    sio->index3 = 0;
    sio->index4 = 0;
    sio->index5 = 0;
    sio->index6 = 0;
    sio->index7 = 0;
    sio->index8 = 0;
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

