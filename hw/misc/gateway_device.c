
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "gateway_device"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_block1;

    uint64_t io_read_trace_block1_0x40021000[12];

    uint64_t io_read_trace_block1_0x40021004[20];

    uint64_t io_read_trace_block1_0x40022000[5];

    uint64_t io_read_trace_block1_0x40021010[4];

    uint64_t io_read_trace_block1_0x4002101c[4];

    uint64_t io_read_trace_block1_0x40021018[240];

    uint64_t io_read_trace_block1_0x40010800[14];

    uint64_t io_read_trace_block1_0x4000440c[8];

    uint64_t io_read_trace_block1_0x40004410[4];

    uint64_t io_read_trace_block1_0x40004414[5];

    uint64_t io_read_trace_block1_0x40010804[10];

    uint64_t io_read_trace_block1_0x40010004[7];

    uint64_t io_read_trace_block1_0x40010c00[11];

    uint64_t io_read_trace_block1_0x40010c04[10];

    uint64_t io_read_trace_block1_0x40011000[14];

    uint64_t io_read_trace_block1_0x40011004[10];

    uint64_t io_read_trace_block1_0x40011400[5];

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
        
        case 0x40021000 - 0x40000000:
            if (sio->io_read_trace_block1_0x40021000[1] < sio->io_read_trace_block1_0x40021000[0]) {
                sio->io_read_trace_block1_0x40021000[1]++;
            } else {
                sio->io_read_trace_block1_0x40021000[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40021000[sio->io_read_trace_block1_0x40021000[1] + 1];
            break;


        case 0x40021004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40021004[1] < sio->io_read_trace_block1_0x40021004[0]) {
                sio->io_read_trace_block1_0x40021004[1]++;
            } else {
                sio->io_read_trace_block1_0x40021004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40021004[sio->io_read_trace_block1_0x40021004[1] + 1];
            break;


        case 0x40022000 - 0x40000000:
            if (sio->io_read_trace_block1_0x40022000[1] < sio->io_read_trace_block1_0x40022000[0]) {
                sio->io_read_trace_block1_0x40022000[1]++;
            } else {
                sio->io_read_trace_block1_0x40022000[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40022000[sio->io_read_trace_block1_0x40022000[1] + 1];
            break;


        case 0x40021010 - 0x40000000:
            if (sio->io_read_trace_block1_0x40021010[1] < sio->io_read_trace_block1_0x40021010[0]) {
                sio->io_read_trace_block1_0x40021010[1]++;
            } else {
                sio->io_read_trace_block1_0x40021010[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40021010[sio->io_read_trace_block1_0x40021010[1] + 1];
            break;


        case 0x4002101c - 0x40000000:
            if (sio->io_read_trace_block1_0x4002101c[1] < sio->io_read_trace_block1_0x4002101c[0]) {
                sio->io_read_trace_block1_0x4002101c[1]++;
            } else {
                sio->io_read_trace_block1_0x4002101c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4002101c[sio->io_read_trace_block1_0x4002101c[1] + 1];
            break;


        case 0x40021018 - 0x40000000:
            if (sio->io_read_trace_block1_0x40021018[1] < sio->io_read_trace_block1_0x40021018[0]) {
                sio->io_read_trace_block1_0x40021018[1]++;
            } else {
                sio->io_read_trace_block1_0x40021018[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40021018[sio->io_read_trace_block1_0x40021018[1] + 1];
            break;


        case 0x40010800 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010800[1] < sio->io_read_trace_block1_0x40010800[0]) {
                sio->io_read_trace_block1_0x40010800[1]++;
            } else {
                sio->io_read_trace_block1_0x40010800[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010800[sio->io_read_trace_block1_0x40010800[1] + 1];
            break;


        case 0x4000440c - 0x40000000:
            if (sio->io_read_trace_block1_0x4000440c[1] < sio->io_read_trace_block1_0x4000440c[0]) {
                sio->io_read_trace_block1_0x4000440c[1]++;
            } else {
                sio->io_read_trace_block1_0x4000440c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4000440c[sio->io_read_trace_block1_0x4000440c[1] + 1];
            break;


        case 0x40004410 - 0x40000000:
            if (sio->io_read_trace_block1_0x40004410[1] < sio->io_read_trace_block1_0x40004410[0]) {
                sio->io_read_trace_block1_0x40004410[1]++;
            } else {
                sio->io_read_trace_block1_0x40004410[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40004410[sio->io_read_trace_block1_0x40004410[1] + 1];
            break;


        case 0x40004414 - 0x40000000:
            if (sio->io_read_trace_block1_0x40004414[1] < sio->io_read_trace_block1_0x40004414[0]) {
                sio->io_read_trace_block1_0x40004414[1]++;
            } else {
                sio->io_read_trace_block1_0x40004414[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40004414[sio->io_read_trace_block1_0x40004414[1] + 1];
            break;


        case 0x40010804 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010804[1] < sio->io_read_trace_block1_0x40010804[0]) {
                sio->io_read_trace_block1_0x40010804[1]++;
            } else {
                sio->io_read_trace_block1_0x40010804[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010804[sio->io_read_trace_block1_0x40010804[1] + 1];
            break;


        case 0x40010004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010004[1] < sio->io_read_trace_block1_0x40010004[0]) {
                sio->io_read_trace_block1_0x40010004[1]++;
            } else {
                sio->io_read_trace_block1_0x40010004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010004[sio->io_read_trace_block1_0x40010004[1] + 1];
            break;


        case 0x40010c00 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010c00[1] < sio->io_read_trace_block1_0x40010c00[0]) {
                sio->io_read_trace_block1_0x40010c00[1]++;
            } else {
                sio->io_read_trace_block1_0x40010c00[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010c00[sio->io_read_trace_block1_0x40010c00[1] + 1];
            break;


        case 0x40010c04 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010c04[1] < sio->io_read_trace_block1_0x40010c04[0]) {
                sio->io_read_trace_block1_0x40010c04[1]++;
            } else {
                sio->io_read_trace_block1_0x40010c04[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010c04[sio->io_read_trace_block1_0x40010c04[1] + 1];
            break;


        case 0x40011000 - 0x40000000:
            if (sio->io_read_trace_block1_0x40011000[1] < sio->io_read_trace_block1_0x40011000[0]) {
                sio->io_read_trace_block1_0x40011000[1]++;
            } else {
                sio->io_read_trace_block1_0x40011000[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40011000[sio->io_read_trace_block1_0x40011000[1] + 1];
            break;


        case 0x40011004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40011004[1] < sio->io_read_trace_block1_0x40011004[0]) {
                sio->io_read_trace_block1_0x40011004[1]++;
            } else {
                sio->io_read_trace_block1_0x40011004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40011004[sio->io_read_trace_block1_0x40011004[1] + 1];
            break;


        case 0x40011400 - 0x40000000:
            if (sio->io_read_trace_block1_0x40011400[1] < sio->io_read_trace_block1_0x40011400[0]) {
                sio->io_read_trace_block1_0x40011400[1]++;
            } else {
                sio->io_read_trace_block1_0x40011400[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40011400[sio->io_read_trace_block1_0x40011400[1] + 1];
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

    uint64_t trace_block1_0x40021000[] = {10, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2000000, 0x0};
    for (int i = 0; i < 12; i++) {
        sio->io_read_trace_block1_0x40021000[i] = trace_block1_0x40021000[i];
    }

    uint64_t trace_block1_0x40021004[] = {18, 0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 20; i++) {
        sio->io_read_trace_block1_0x40021004[i] = trace_block1_0x40021004[i];
    }

    uint64_t trace_block1_0x40022000[] = {3, 0, 0x0, 0x2, 0x2};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40022000[i] = trace_block1_0x40022000[i];
    }

    uint64_t trace_block1_0x40021010[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40021010[i] = trace_block1_0x40021010[i];
    }

    uint64_t trace_block1_0x4002101c[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x4002101c[i] = trace_block1_0x4002101c[i];
    }

    uint64_t trace_block1_0x40021018[] = {238, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 240; i++) {
        sio->io_read_trace_block1_0x40021018[i] = trace_block1_0x40021018[i];
    }

    uint64_t trace_block1_0x40010800[] = {12, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 14; i++) {
        sio->io_read_trace_block1_0x40010800[i] = trace_block1_0x40010800[i];
    }

    uint64_t trace_block1_0x4000440c[] = {6, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 8; i++) {
        sio->io_read_trace_block1_0x4000440c[i] = trace_block1_0x4000440c[i];
    }

    uint64_t trace_block1_0x40004410[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40004410[i] = trace_block1_0x40004410[i];
    }

    uint64_t trace_block1_0x40004414[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40004414[i] = trace_block1_0x40004414[i];
    }

    uint64_t trace_block1_0x40010804[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x40010804[i] = trace_block1_0x40010804[i];
    }

    uint64_t trace_block1_0x40010004[] = {5, 0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 7; i++) {
        sio->io_read_trace_block1_0x40010004[i] = trace_block1_0x40010004[i];
    }

    uint64_t trace_block1_0x40010c00[] = {9, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 11; i++) {
        sio->io_read_trace_block1_0x40010c00[i] = trace_block1_0x40010c00[i];
    }

    uint64_t trace_block1_0x40010c04[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x40010c04[i] = trace_block1_0x40010c04[i];
    }

    uint64_t trace_block1_0x40011000[] = {12, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 14; i++) {
        sio->io_read_trace_block1_0x40011000[i] = trace_block1_0x40011000[i];
    }

    uint64_t trace_block1_0x40011004[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x40011004[i] = trace_block1_0x40011004[i];
    }

    uint64_t trace_block1_0x40011400[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40011400[i] = trace_block1_0x40011400[i];
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
