
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "plc_device"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_block1;

    uint64_t io_read_trace_block1_0x40023800[7];

    uint64_t io_read_trace_block1_0x40023c00[7];

    uint64_t io_read_trace_block1_0x40023840[8];

    uint64_t io_read_trace_block1_0x40007000[6];

    uint64_t io_read_trace_block1_0x40023808[18];

    uint64_t io_read_trace_block1_0x40007004[4];

    uint64_t io_read_trace_block1_0x40023820[4];

    uint64_t io_read_trace_block1_0x40023830[6];

    uint64_t io_read_trace_block1_0x40020c24[4];

    uint64_t io_read_trace_block1_0x40020c00[4];

    uint64_t io_read_trace_block1_0x40020c08[4];

    uint64_t io_read_trace_block1_0x40020c04[4];

    uint64_t io_read_trace_block1_0x40020c0c[4];

    uint64_t io_read_trace_block1_0x4000480c[6];

    uint64_t io_read_trace_block1_0x40004810[4];

    uint64_t io_read_trace_block1_0x40004814[5];

    MemoryRegion io_block2;

    MemoryRegion io_fsmc_control_register;

    uint32_t irq_reg2;
} SynthState;


static void synth_write_block1(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE block1 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_block1(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {
        
        case 0x40023800 - 0x40000000:
            if (sio->io_read_trace_block1_0x40023800[1] < sio->io_read_trace_block1_0x40023800[0]) {
                sio->io_read_trace_block1_0x40023800[1]++;
            } else {
                sio->io_read_trace_block1_0x40023800[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40023800[sio->io_read_trace_block1_0x40023800[1] + 1];
            break;


        case 0x40023c00 - 0x40000000:
            if (sio->io_read_trace_block1_0x40023c00[1] < sio->io_read_trace_block1_0x40023c00[0]) {
                sio->io_read_trace_block1_0x40023c00[1]++;
            } else {
                sio->io_read_trace_block1_0x40023c00[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40023c00[sio->io_read_trace_block1_0x40023c00[1] + 1];
            break;


        case 0x40023840 - 0x40000000:
            if (sio->io_read_trace_block1_0x40023840[1] < sio->io_read_trace_block1_0x40023840[0]) {
                sio->io_read_trace_block1_0x40023840[1]++;
            } else {
                sio->io_read_trace_block1_0x40023840[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40023840[sio->io_read_trace_block1_0x40023840[1] + 1];
            break;


        case 0x40007000 - 0x40000000:
            if (sio->io_read_trace_block1_0x40007000[1] < sio->io_read_trace_block1_0x40007000[0]) {
                sio->io_read_trace_block1_0x40007000[1]++;
            } else {
                sio->io_read_trace_block1_0x40007000[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40007000[sio->io_read_trace_block1_0x40007000[1] + 1];
            break;


        case 0x40023808 - 0x40000000:
            if (sio->io_read_trace_block1_0x40023808[1] < sio->io_read_trace_block1_0x40023808[0]) {
                sio->io_read_trace_block1_0x40023808[1]++;
            } else {
                sio->io_read_trace_block1_0x40023808[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40023808[sio->io_read_trace_block1_0x40023808[1] + 1];
            break;


        case 0x40007004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40007004[1] < sio->io_read_trace_block1_0x40007004[0]) {
                sio->io_read_trace_block1_0x40007004[1]++;
            } else {
                sio->io_read_trace_block1_0x40007004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40007004[sio->io_read_trace_block1_0x40007004[1] + 1];
            break;


        case 0x40023820 - 0x40000000:
            if (sio->io_read_trace_block1_0x40023820[1] < sio->io_read_trace_block1_0x40023820[0]) {
                sio->io_read_trace_block1_0x40023820[1]++;
            } else {
                sio->io_read_trace_block1_0x40023820[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40023820[sio->io_read_trace_block1_0x40023820[1] + 1];
            break;


        case 0x40023830 - 0x40000000:
            if (sio->io_read_trace_block1_0x40023830[1] < sio->io_read_trace_block1_0x40023830[0]) {
                sio->io_read_trace_block1_0x40023830[1]++;
            } else {
                sio->io_read_trace_block1_0x40023830[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40023830[sio->io_read_trace_block1_0x40023830[1] + 1];
            break;


        case 0x40020c24 - 0x40000000:
            if (sio->io_read_trace_block1_0x40020c24[1] < sio->io_read_trace_block1_0x40020c24[0]) {
                sio->io_read_trace_block1_0x40020c24[1]++;
            } else {
                sio->io_read_trace_block1_0x40020c24[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40020c24[sio->io_read_trace_block1_0x40020c24[1] + 1];
            break;


        case 0x40020c00 - 0x40000000:
            if (sio->io_read_trace_block1_0x40020c00[1] < sio->io_read_trace_block1_0x40020c00[0]) {
                sio->io_read_trace_block1_0x40020c00[1]++;
            } else {
                sio->io_read_trace_block1_0x40020c00[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40020c00[sio->io_read_trace_block1_0x40020c00[1] + 1];
            break;


        case 0x40020c08 - 0x40000000:
            if (sio->io_read_trace_block1_0x40020c08[1] < sio->io_read_trace_block1_0x40020c08[0]) {
                sio->io_read_trace_block1_0x40020c08[1]++;
            } else {
                sio->io_read_trace_block1_0x40020c08[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40020c08[sio->io_read_trace_block1_0x40020c08[1] + 1];
            break;


        case 0x40020c04 - 0x40000000:
            if (sio->io_read_trace_block1_0x40020c04[1] < sio->io_read_trace_block1_0x40020c04[0]) {
                sio->io_read_trace_block1_0x40020c04[1]++;
            } else {
                sio->io_read_trace_block1_0x40020c04[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40020c04[sio->io_read_trace_block1_0x40020c04[1] + 1];
            break;


        case 0x40020c0c - 0x40000000:
            if (sio->io_read_trace_block1_0x40020c0c[1] < sio->io_read_trace_block1_0x40020c0c[0]) {
                sio->io_read_trace_block1_0x40020c0c[1]++;
            } else {
                sio->io_read_trace_block1_0x40020c0c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40020c0c[sio->io_read_trace_block1_0x40020c0c[1] + 1];
            break;


        case 0x4000480c - 0x40000000:
            if (sio->io_read_trace_block1_0x4000480c[1] < sio->io_read_trace_block1_0x4000480c[0]) {
                sio->io_read_trace_block1_0x4000480c[1]++;
            } else {
                sio->io_read_trace_block1_0x4000480c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4000480c[sio->io_read_trace_block1_0x4000480c[1] + 1];
            break;


        case 0x40004810 - 0x40000000:
            if (sio->io_read_trace_block1_0x40004810[1] < sio->io_read_trace_block1_0x40004810[0]) {
                sio->io_read_trace_block1_0x40004810[1]++;
            } else {
                sio->io_read_trace_block1_0x40004810[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40004810[sio->io_read_trace_block1_0x40004810[1] + 1];
            break;


        case 0x40004814 - 0x40000000:
            if (sio->io_read_trace_block1_0x40004814[1] < sio->io_read_trace_block1_0x40004814[0]) {
                sio->io_read_trace_block1_0x40004814[1]++;
            } else {
                sio->io_read_trace_block1_0x40004814[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40004814[sio->io_read_trace_block1_0x40004814[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ block1 ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
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
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE block2 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_block2(void *opaque, hwaddr addr, unsigned size) {
#ifdef PAPER_EVAL
    fprintf(stderr, "READ block2 ADDR 0x%lx VAL 0xffffffffffffffff\n", addr);
#endif
    return 0xffffffffffffffff;
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
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE fsmc_control_register ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_fsmc_control_register(void *opaque, hwaddr addr, unsigned size) {
#ifdef PAPER_EVAL
    fprintf(stderr, "READ fsmc_control_register ADDR 0x%lx VAL 0xffffffffffffffff\n", addr);
#endif
    return 0xffffffffffffffff;
}

static const MemoryRegionOps synth_io_ops_fsmc_control_register =
{
    .write = synth_write_fsmc_control_register,
    .read = synth_read_fsmc_control_register,
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
        &sio->io_block2, obj, &synth_io_ops_block2, sio, TYPE_SYNTH, 0x60c00
    );
    sysbus_init_mmio(dev, &sio->io_block2);
    memory_region_add_subregion(sysbus, 0x50000000, &sio->io_block2);

    memory_region_init_io(
        &sio->io_fsmc_control_register, obj, &synth_io_ops_fsmc_control_register, sio, TYPE_SYNTH, 0x1000
    );
    sysbus_init_mmio(dev, &sio->io_fsmc_control_register);
    memory_region_add_subregion(sysbus, 0xa0000000, &sio->io_fsmc_control_register);

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;

    uint64_t trace_block1_0x40023800[] = {5, 0, 0x0, 0x0, 0x0, 0x0, 0x2000000};
    for (int i = 0; i < 7; i++) {
        sio->io_read_trace_block1_0x40023800[i] = trace_block1_0x40023800[i];
    }

    uint64_t trace_block1_0x40023c00[] = {5, 0, 0x0, 0x0, 0x0, 0x5, 0x5};
    for (int i = 0; i < 7; i++) {
        sio->io_read_trace_block1_0x40023c00[i] = trace_block1_0x40023c00[i];
    }

    uint64_t trace_block1_0x40023840[] = {6, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 8; i++) {
        sio->io_read_trace_block1_0x40023840[i] = trace_block1_0x40023840[i];
    }

    uint64_t trace_block1_0x40007000[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40007000[i] = trace_block1_0x40007000[i];
    }

    uint64_t trace_block1_0x40023808[] = {16, 0, 0x4, 0x8, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 18; i++) {
        sio->io_read_trace_block1_0x40023808[i] = trace_block1_0x40023808[i];
    }

    uint64_t trace_block1_0x40007004[] = {2, 0, 0x10000, 0x20000};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40007004[i] = trace_block1_0x40007004[i];
    }

    uint64_t trace_block1_0x40023820[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40023820[i] = trace_block1_0x40023820[i];
    }

    uint64_t trace_block1_0x40023830[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40023830[i] = trace_block1_0x40023830[i];
    }

    uint64_t trace_block1_0x40020c24[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40020c24[i] = trace_block1_0x40020c24[i];
    }

    uint64_t trace_block1_0x40020c00[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40020c00[i] = trace_block1_0x40020c00[i];
    }

    uint64_t trace_block1_0x40020c08[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40020c08[i] = trace_block1_0x40020c08[i];
    }

    uint64_t trace_block1_0x40020c04[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40020c04[i] = trace_block1_0x40020c04[i];
    }

    uint64_t trace_block1_0x40020c0c[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40020c0c[i] = trace_block1_0x40020c0c[i];
    }

    uint64_t trace_block1_0x4000480c[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x4000480c[i] = trace_block1_0x4000480c[i];
    }

    uint64_t trace_block1_0x40004810[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40004810[i] = trace_block1_0x40004810[i];
    }

    uint64_t trace_block1_0x40004814[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40004814[i] = trace_block1_0x40004814[i];
    }
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
