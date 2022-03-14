#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "synth_cmu900_concrete"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_0x0;

    MemoryRegion io_0x1000;

    MemoryRegion io_0x2004;

    MemoryRegion io_0x3000;

    MemoryRegion io_0x4000;

    MemoryRegion io_0x5000;

    MemoryRegion io_0x6000;

    MemoryRegion io_0x7000;

    uint64_t io_read_trace_0x0_0x0[2];

    uint64_t io_read_trace_0x0_0x1[2];

    uint64_t io_read_trace_0x1000_0x1000[2];

    uint64_t io_read_trace_0x1000_0x1001[2];

    uint64_t io_read_trace_0x1000_0x1002[2];

    uint64_t io_read_trace_0x1000_0x1003[2];

    uint64_t io_read_trace_0x2004_0x2004[264];

    uint64_t io_read_trace_0x2004_0x2006[2];

    uint64_t io_read_trace_0x3000_0x3000[2];

    uint64_t io_read_trace_0x3000_0x3001[7];

    uint64_t io_read_trace_0x4000_0x4000[2];

    uint64_t io_read_trace_0x5000_0x5000[7];

    uint64_t io_read_trace_0x6000_0x6000[11];

    uint64_t io_read_trace_0x7000_0x7000[2];

    MemoryRegion io_mmio;

    uint64_t io_read_trace_mmio_0x21e40080[3];

    uint32_t irq_reg2;
} SynthState;


static void synth_write_0x0(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x0 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x0(void *opaque, hwaddr addr, unsigned size) {
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x0 ADDR 0x%lx VAL 0xffffffffffffffff\n", addr);
#endif
    return 0xffffffffffffffff;
}

static const MemoryRegionOps synth_io_ops_0x0 =
{
    .write = synth_write_0x0,
    .read = synth_read_0x0,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x1000(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x1000 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x1000(void *opaque, hwaddr addr, unsigned size) {
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x1000 ADDR 0x%lx VAL 0xffffffffffffffff\n", addr);
#endif
    return 0xffffffffffffffff;
}

static const MemoryRegionOps synth_io_ops_0x1000 =
{
    .write = synth_write_0x1000,
    .read = synth_read_0x1000,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x2004(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x2004 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x2004(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {

        case 0x2004 - 0x2004:
            if (sio->io_read_trace_0x2004_0x2004[1] < sio->io_read_trace_0x2004_0x2004[0]) {
                sio->io_read_trace_0x2004_0x2004[1]++;
            } else {
                sio->io_read_trace_0x2004_0x2004[1] -= 0;
            }
            res = sio->io_read_trace_0x2004_0x2004[sio->io_read_trace_0x2004_0x2004[1] + 1];
            break;


        case 0x2006 - 0x2004:
            if (sio->io_read_trace_0x2004_0x2006[1] < sio->io_read_trace_0x2004_0x2006[0]) {
                sio->io_read_trace_0x2004_0x2006[1]++;
            } else {
                sio->io_read_trace_0x2004_0x2006[1] -= 0;
            }
            res = sio->io_read_trace_0x2004_0x2006[sio->io_read_trace_0x2004_0x2006[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x2004 ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_0x2004 =
{
    .write = synth_write_0x2004,
    .read = synth_read_0x2004,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x3000(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x3000 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x3000(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {

        case 0x3000 - 0x3000:
            if (sio->io_read_trace_0x3000_0x3000[1] < sio->io_read_trace_0x3000_0x3000[0]) {
                sio->io_read_trace_0x3000_0x3000[1]++;
            } else {
                sio->io_read_trace_0x3000_0x3000[1] -= 0;
            }
            res = sio->io_read_trace_0x3000_0x3000[sio->io_read_trace_0x3000_0x3000[1] + 1];
            break;


        case 0x3001 - 0x3000:
            if (sio->io_read_trace_0x3000_0x3001[1] < sio->io_read_trace_0x3000_0x3001[0]) {
                sio->io_read_trace_0x3000_0x3001[1]++;
            } else {
                sio->io_read_trace_0x3000_0x3001[1] -= 0;
            }
            res = sio->io_read_trace_0x3000_0x3001[sio->io_read_trace_0x3000_0x3001[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x3000 ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_0x3000 =
{
    .write = synth_write_0x3000,
    .read = synth_read_0x3000,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x4000(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x4000 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x4000(void *opaque, hwaddr addr, unsigned size) {
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x4000 ADDR 0x%lx VAL 0xffffffffffffffff\n", addr);
#endif
    return 0xffffffffffffffff;
}

static const MemoryRegionOps synth_io_ops_0x4000 =
{
    .write = synth_write_0x4000,
    .read = synth_read_0x4000,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x5000(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x5000 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x5000(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {

        case 0x5000 - 0x5000:
            if (sio->io_read_trace_0x5000_0x5000[1] < sio->io_read_trace_0x5000_0x5000[0]) {
                sio->io_read_trace_0x5000_0x5000[1]++;
            } else {
                sio->io_read_trace_0x5000_0x5000[1] -= 0;
            }
            res = sio->io_read_trace_0x5000_0x5000[sio->io_read_trace_0x5000_0x5000[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x5000 ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_0x5000 =
{
    .write = synth_write_0x5000,
    .read = synth_read_0x5000,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x6000(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x6000 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x6000(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {

        case 0x6000 - 0x6000:
            if (sio->io_read_trace_0x6000_0x6000[1] < sio->io_read_trace_0x6000_0x6000[0]) {
                sio->io_read_trace_0x6000_0x6000[1]++;
            } else {
                sio->io_read_trace_0x6000_0x6000[1] -= 0;
            }
            res = sio->io_read_trace_0x6000_0x6000[sio->io_read_trace_0x6000_0x6000[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x6000 ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_0x6000 =
{
    .write = synth_write_0x6000,
    .read = synth_read_0x6000,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_0x7000(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE 0x7000 ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_0x7000(void *opaque, hwaddr addr, unsigned size) {
#ifdef PAPER_EVAL
    fprintf(stderr, "READ 0x7000 ADDR 0x%lx VAL 0xffffffffffffffff\n", addr);
#endif
    return 0xffffffffffffffff;
}

static const MemoryRegionOps synth_io_ops_0x7000 =
{
    .write = synth_write_0x7000,
    .read = synth_read_0x7000,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_mmio(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE mmio ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_mmio(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {

        case 0x21e40080 - 0x21d00000:
            if (sio->io_read_trace_mmio_0x21e40080[1] < sio->io_read_trace_mmio_0x21e40080[0]) {
                sio->io_read_trace_mmio_0x21e40080[1]++;
            } else {
                sio->io_read_trace_mmio_0x21e40080[1] -= 0;
            }
            res = sio->io_read_trace_mmio_0x21e40080[sio->io_read_trace_mmio_0x21e40080[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ mmio ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_mmio =
{
    .write = synth_write_mmio,
    .read = synth_read_mmio,
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
        &sio->io_0x0, OBJECT(sio), &synth_io_ops_0x0, sio, TYPE_SYNTH, 2
    );
    sysbus_init_ioports(dev, 0x0, 2);
    sysbus_add_io(dev, 0x0, &sio->io_0x0);

    memory_region_init_io(
        &sio->io_0x1000, OBJECT(sio), &synth_io_ops_0x1000, sio, TYPE_SYNTH, 4
    );
    sysbus_init_ioports(dev, 0x1000, 4);
    sysbus_add_io(dev, 0x1000, &sio->io_0x1000);

    memory_region_init_io(
        &sio->io_0x2004, OBJECT(sio), &synth_io_ops_0x2004, sio, TYPE_SYNTH, 3
    );
    sysbus_init_ioports(dev, 0x2004, 3);
    sysbus_add_io(dev, 0x2004, &sio->io_0x2004);

    memory_region_init_io(
        &sio->io_0x3000, OBJECT(sio), &synth_io_ops_0x3000, sio, TYPE_SYNTH, 2
    );
    sysbus_init_ioports(dev, 0x3000, 2);
    sysbus_add_io(dev, 0x3000, &sio->io_0x3000);

    memory_region_init_io(
        &sio->io_0x4000, OBJECT(sio), &synth_io_ops_0x4000, sio, TYPE_SYNTH, 1
    );
    sysbus_init_ioports(dev, 0x4000, 1);
    sysbus_add_io(dev, 0x4000, &sio->io_0x4000);

    memory_region_init_io(
        &sio->io_0x5000, OBJECT(sio), &synth_io_ops_0x5000, sio, TYPE_SYNTH, 1
    );
    sysbus_init_ioports(dev, 0x5000, 1);
    sysbus_add_io(dev, 0x5000, &sio->io_0x5000);

    memory_region_init_io(
        &sio->io_0x6000, OBJECT(sio), &synth_io_ops_0x6000, sio, TYPE_SYNTH, 1
    );
    sysbus_init_ioports(dev, 0x6000, 1);
    sysbus_add_io(dev, 0x6000, &sio->io_0x6000);

    memory_region_init_io(
        &sio->io_0x7000, OBJECT(sio), &synth_io_ops_0x7000, sio, TYPE_SYNTH, 1
    );
    sysbus_init_ioports(dev, 0x7000, 1);
    sysbus_add_io(dev, 0x7000, &sio->io_0x7000);

    memory_region_init_io(
        &sio->io_mmio, obj, &synth_io_ops_mmio, sio, TYPE_SYNTH, 0x1400a4
    );
    sysbus_init_mmio(dev, &sio->io_mmio);
    memory_region_add_subregion(sysbus, 0x21d00000, &sio->io_mmio);

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;

    uint64_t trace_0x0_0x0[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x0_0x0[i] = trace_0x0_0x0[i];
    }

    uint64_t trace_0x0_0x1[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x0_0x1[i] = trace_0x0_0x1[i];
    }

    uint64_t trace_0x1000_0x1000[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x1000_0x1000[i] = trace_0x1000_0x1000[i];
    }

    uint64_t trace_0x1000_0x1001[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x1000_0x1001[i] = trace_0x1000_0x1001[i];
    }

    uint64_t trace_0x1000_0x1002[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x1000_0x1002[i] = trace_0x1000_0x1002[i];
    }

    uint64_t trace_0x1000_0x1003[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x1000_0x1003[i] = trace_0x1000_0x1003[i];
    }

    uint64_t trace_0x2004_0x2004[] = {262, 0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x0, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x0, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0, 0x4};
    for (int i = 0; i < 264; i++) {
        sio->io_read_trace_0x2004_0x2004[i] = trace_0x2004_0x2004[i];
    }

    uint64_t trace_0x2004_0x2006[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x2004_0x2006[i] = trace_0x2004_0x2006[i];
    }

    uint64_t trace_0x3000_0x3000[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x3000_0x3000[i] = trace_0x3000_0x3000[i];
    }

    uint64_t trace_0x3000_0x3001[] = {5, 0, 0x80, 0x1, 0x55, 0x43, 0x43};
    for (int i = 0; i < 7; i++) {
        sio->io_read_trace_0x3000_0x3001[i] = trace_0x3000_0x3001[i];
    }

    uint64_t trace_0x4000_0x4000[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x4000_0x4000[i] = trace_0x4000_0x4000[i];
    }

    uint64_t trace_0x5000_0x5000[] = {5, 0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 7; i++) {
        sio->io_read_trace_0x5000_0x5000[i] = trace_0x5000_0x5000[i];
    }

    uint64_t trace_0x6000_0x6000[] = {9, 0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0, 0x20, 0x0};
    for (int i = 0; i < 11; i++) {
        sio->io_read_trace_0x6000_0x6000[i] = trace_0x6000_0x6000[i];
    }

    uint64_t trace_0x7000_0x7000[] = {0, 0};
    for (int i = 0; i < 2; i++) {
        sio->io_read_trace_0x7000_0x7000[i] = trace_0x7000_0x7000[i];
    }

    uint64_t trace_mmio_0x21e40080[] = {1, 0, 0x20};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_mmio_0x21e40080[i] = trace_mmio_0x21e40080[i];
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
