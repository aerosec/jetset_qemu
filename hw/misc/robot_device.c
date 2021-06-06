
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "robot_device"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_block1;

    uint64_t io_read_trace_block1_0x40021000[19];

    uint64_t io_read_trace_block1_0x40021004[25];

    uint64_t io_read_trace_block1_0x40022000[5];

    uint64_t io_read_trace_block1_0x40021018[8];

    uint64_t io_read_trace_block1_0x40010800[6];

    uint64_t io_read_trace_block1_0x40005400[21];

    uint64_t io_read_trace_block1_0x4001380c[5];

    uint64_t io_read_trace_block1_0x40013810[4];

    uint64_t io_read_trace_block1_0x40013814[4];

    uint64_t io_read_trace_block1_0x40000000[4];

    uint64_t io_read_trace_block1_0x40000008[6];

    uint64_t io_read_trace_block1_0x40000004[4];

    uint64_t io_read_trace_block1_0x40012c00[6];

    uint64_t io_read_trace_block1_0x40012c08[6];

    uint64_t io_read_trace_block1_0x40012c04[6];

    uint64_t io_read_trace_block1_0x40012c20[10];

    uint64_t io_read_trace_block1_0x40012c18[6];

    uint64_t io_read_trace_block1_0x40012c1c[6];

    uint64_t io_read_trace_block1_0x40010804[4];

    uint64_t io_read_trace_block1_0x40012c44[4];

    uint64_t io_read_trace_block1_0x40005418[24];

    uint64_t io_read_trace_block1_0x40005414[52];

    uint64_t io_read_trace_block1_0x4000000c[3];

    MemoryRegion io_block2;

    MemoryRegion io_fsmc_control_register;

    MemoryRegion io_dma_region;

    uint64_t io_read_trace_dma_region_0x20000018[11];

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


        case 0x40005400 - 0x40000000:
            if (sio->io_read_trace_block1_0x40005400[1] < sio->io_read_trace_block1_0x40005400[0]) {
                sio->io_read_trace_block1_0x40005400[1]++;
            } else {
                sio->io_read_trace_block1_0x40005400[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40005400[sio->io_read_trace_block1_0x40005400[1] + 1];
            break;


        case 0x4001380c - 0x40000000:
            if (sio->io_read_trace_block1_0x4001380c[1] < sio->io_read_trace_block1_0x4001380c[0]) {
                sio->io_read_trace_block1_0x4001380c[1]++;
            } else {
                sio->io_read_trace_block1_0x4001380c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4001380c[sio->io_read_trace_block1_0x4001380c[1] + 1];
            break;


        case 0x40013810 - 0x40000000:
            if (sio->io_read_trace_block1_0x40013810[1] < sio->io_read_trace_block1_0x40013810[0]) {
                sio->io_read_trace_block1_0x40013810[1]++;
            } else {
                sio->io_read_trace_block1_0x40013810[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40013810[sio->io_read_trace_block1_0x40013810[1] + 1];
            break;


        case 0x40013814 - 0x40000000:
            if (sio->io_read_trace_block1_0x40013814[1] < sio->io_read_trace_block1_0x40013814[0]) {
                sio->io_read_trace_block1_0x40013814[1]++;
            } else {
                sio->io_read_trace_block1_0x40013814[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40013814[sio->io_read_trace_block1_0x40013814[1] + 1];
            break;


        case 0x40000000 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000000[1] < sio->io_read_trace_block1_0x40000000[0]) {
                sio->io_read_trace_block1_0x40000000[1]++;
            } else {
                sio->io_read_trace_block1_0x40000000[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000000[sio->io_read_trace_block1_0x40000000[1] + 1];
            break;


        case 0x40000008 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000008[1] < sio->io_read_trace_block1_0x40000008[0]) {
                sio->io_read_trace_block1_0x40000008[1]++;
            } else {
                sio->io_read_trace_block1_0x40000008[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000008[sio->io_read_trace_block1_0x40000008[1] + 1];
            break;


        case 0x40000004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000004[1] < sio->io_read_trace_block1_0x40000004[0]) {
                sio->io_read_trace_block1_0x40000004[1]++;
            } else {
                sio->io_read_trace_block1_0x40000004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000004[sio->io_read_trace_block1_0x40000004[1] + 1];
            break;


        case 0x40012c00 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c00[1] < sio->io_read_trace_block1_0x40012c00[0]) {
                sio->io_read_trace_block1_0x40012c00[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c00[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c00[sio->io_read_trace_block1_0x40012c00[1] + 1];
            break;


        case 0x40012c08 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c08[1] < sio->io_read_trace_block1_0x40012c08[0]) {
                sio->io_read_trace_block1_0x40012c08[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c08[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c08[sio->io_read_trace_block1_0x40012c08[1] + 1];
            break;


        case 0x40012c04 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c04[1] < sio->io_read_trace_block1_0x40012c04[0]) {
                sio->io_read_trace_block1_0x40012c04[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c04[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c04[sio->io_read_trace_block1_0x40012c04[1] + 1];
            break;


        case 0x40012c20 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c20[1] < sio->io_read_trace_block1_0x40012c20[0]) {
                sio->io_read_trace_block1_0x40012c20[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c20[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c20[sio->io_read_trace_block1_0x40012c20[1] + 1];
            break;


        case 0x40012c18 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c18[1] < sio->io_read_trace_block1_0x40012c18[0]) {
                sio->io_read_trace_block1_0x40012c18[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c18[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c18[sio->io_read_trace_block1_0x40012c18[1] + 1];
            break;


        case 0x40012c1c - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c1c[1] < sio->io_read_trace_block1_0x40012c1c[0]) {
                sio->io_read_trace_block1_0x40012c1c[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c1c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c1c[sio->io_read_trace_block1_0x40012c1c[1] + 1];
            break;


        case 0x40010804 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010804[1] < sio->io_read_trace_block1_0x40010804[0]) {
                sio->io_read_trace_block1_0x40010804[1]++;
            } else {
                sio->io_read_trace_block1_0x40010804[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010804[sio->io_read_trace_block1_0x40010804[1] + 1];
            break;


        case 0x40012c44 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c44[1] < sio->io_read_trace_block1_0x40012c44[0]) {
                sio->io_read_trace_block1_0x40012c44[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c44[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c44[sio->io_read_trace_block1_0x40012c44[1] + 1];
            break;


        case 0x40005418 - 0x40000000:
            if (sio->io_read_trace_block1_0x40005418[1] < sio->io_read_trace_block1_0x40005418[0]) {
                sio->io_read_trace_block1_0x40005418[1]++;
            } else {
                sio->io_read_trace_block1_0x40005418[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40005418[sio->io_read_trace_block1_0x40005418[1] + 1];
            break;


        case 0x40005414 - 0x40000000:
            if (sio->io_read_trace_block1_0x40005414[1] < sio->io_read_trace_block1_0x40005414[0]) {
                sio->io_read_trace_block1_0x40005414[1]++;
            } else {
                sio->io_read_trace_block1_0x40005414[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40005414[sio->io_read_trace_block1_0x40005414[1] + 1];
            break;


        case 0x4000000c - 0x40000000:
            if (sio->io_read_trace_block1_0x4000000c[1] < sio->io_read_trace_block1_0x4000000c[0]) {
                sio->io_read_trace_block1_0x4000000c[1]++;
            } else {
                sio->io_read_trace_block1_0x4000000c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4000000c[sio->io_read_trace_block1_0x4000000c[1] + 1];
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

static void synth_write_dma_region(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE dma_region ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_dma_region(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {
        
        case 0x20000018 - 0x20000018:
            if (sio->io_read_trace_dma_region_0x20000018[1] < sio->io_read_trace_dma_region_0x20000018[0]) {
                sio->io_read_trace_dma_region_0x20000018[1]++;
            } else {
                sio->io_read_trace_dma_region_0x20000018[1] -= 0;
            }
            res = sio->io_read_trace_dma_region_0x20000018[sio->io_read_trace_dma_region_0x20000018[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ dma_region ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_dma_region =
{
    .write = synth_write_dma_region,
    .read = synth_read_dma_region,
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

    memory_region_init_io(
        &sio->io_dma_region, obj, &synth_io_ops_dma_region, sio, TYPE_SYNTH, 0x5
    );
    sysbus_init_mmio(dev, &sio->io_dma_region);
    memory_region_add_subregion(sysbus, 0x20000018, &sio->io_dma_region);

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;

    uint64_t trace_block1_0x40021000[] = {17, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2000000, 0x2000000, 0x2000000, 0x2000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2000000, 0x0};
    for (int i = 0; i < 19; i++) {
        sio->io_read_trace_block1_0x40021000[i] = trace_block1_0x40021000[i];
    }

    uint64_t trace_block1_0x40021004[] = {23, 0, 0x0, 0x0, 0x4, 0xc, 0x0, 0x0, 0x0, 0x0, 0xc, 0xc, 0xc, 0xc, 0x8, 0x0, 0x0, 0x100008, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 25; i++) {
        sio->io_read_trace_block1_0x40021004[i] = trace_block1_0x40021004[i];
    }

    uint64_t trace_block1_0x40022000[] = {3, 0, 0x0, 0x3, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40022000[i] = trace_block1_0x40022000[i];
    }

    uint64_t trace_block1_0x40021018[] = {6, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 8; i++) {
        sio->io_read_trace_block1_0x40021018[i] = trace_block1_0x40021018[i];
    }

    uint64_t trace_block1_0x40010800[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40010800[i] = trace_block1_0x40010800[i];
    }

    uint64_t trace_block1_0x40005400[] = {19, 0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 21; i++) {
        sio->io_read_trace_block1_0x40005400[i] = trace_block1_0x40005400[i];
    }

    uint64_t trace_block1_0x4001380c[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x4001380c[i] = trace_block1_0x4001380c[i];
    }

    uint64_t trace_block1_0x40013810[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40013810[i] = trace_block1_0x40013810[i];
    }

    uint64_t trace_block1_0x40013814[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40013814[i] = trace_block1_0x40013814[i];
    }

    uint64_t trace_block1_0x40000000[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000000[i] = trace_block1_0x40000000[i];
    }

    uint64_t trace_block1_0x40000008[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40000008[i] = trace_block1_0x40000008[i];
    }

    uint64_t trace_block1_0x40000004[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000004[i] = trace_block1_0x40000004[i];
    }

    uint64_t trace_block1_0x40012c00[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40012c00[i] = trace_block1_0x40012c00[i];
    }

    uint64_t trace_block1_0x40012c08[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40012c08[i] = trace_block1_0x40012c08[i];
    }

    uint64_t trace_block1_0x40012c04[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40012c04[i] = trace_block1_0x40012c04[i];
    }

    uint64_t trace_block1_0x40012c20[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x40012c20[i] = trace_block1_0x40012c20[i];
    }

    uint64_t trace_block1_0x40012c18[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40012c18[i] = trace_block1_0x40012c18[i];
    }

    uint64_t trace_block1_0x40012c1c[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40012c1c[i] = trace_block1_0x40012c1c[i];
    }

    uint64_t trace_block1_0x40010804[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40010804[i] = trace_block1_0x40010804[i];
    }

    uint64_t trace_block1_0x40012c44[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40012c44[i] = trace_block1_0x40012c44[i];
    }

    uint64_t trace_block1_0x40005418[] = {22, 0, 0x100002, 0x100002, 0x100002, 0x100002, 0x100000, 0x0, 0x500812, 0x100002, 0x100002, 0x100002, 0x100000, 0x100002, 0x100002, 0x100002, 0x100002, 0x100000, 0x0, 0x100002, 0x100002, 0x100002, 0x100042, 0x100000};
    for (int i = 0; i < 24; i++) {
        sio->io_read_trace_block1_0x40005418[i] = trace_block1_0x40005418[i];
    }

    uint64_t trace_block1_0x40005414[] = {50, 0, 0x10001, 0x10000, 0x0, 0x10000, 0x0, 0x10000, 0x0, 0x10000, 0x0, 0x10002, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x400, 0x10001, 0x10080, 0x400, 0x10001, 0x10000, 0x0, 0x10000, 0x0, 0x13000, 0x0, 0x10002, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x400, 0x10001, 0x10000, 0x0, 0x10000, 0x400};
    for (int i = 0; i < 52; i++) {
        sio->io_read_trace_block1_0x40005414[i] = trace_block1_0x40005414[i];
    }

    uint64_t trace_block1_0x4000000c[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_block1_0x4000000c[i] = trace_block1_0x4000000c[i];
    }

    uint64_t trace_dma_region_0x20000018[] = {9, 0, 0x8000000, 0x3b6e9e62, 0xa9ded23e, 0x3d10000, 0x0, 0x8f5c4550, 0x8a3d70c0, 0xd00, 0x0};
    for (int i = 0; i < 11; i++) {
        sio->io_read_trace_dma_region_0x20000018[i] = trace_dma_region_0x20000018[i];
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
