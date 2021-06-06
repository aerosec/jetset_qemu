
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "console_device"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_peripherals;

    uint64_t io_read_trace_peripherals_0x40048040[3];

    uint64_t io_read_trace_peripherals_0x40048038[8];

    uint64_t io_read_trace_peripherals_0x40049048[3];

    uint64_t io_read_trace_peripherals_0x4007e000[3];

    uint64_t io_read_trace_peripherals_0x40064001[8];

    uint64_t io_read_trace_peripherals_0x40064005[5];

    uint64_t io_read_trace_peripherals_0x40064003[4];

    uint64_t io_read_trace_peripherals_0x40064000[9];

    uint64_t io_read_trace_peripherals_0x40064006[37];

    uint64_t io_read_trace_peripherals_0x40064008[3];

    uint64_t io_read_trace_peripherals_0x4004803c[4];

    uint64_t io_read_trace_peripherals_0x4003d010[3];

    uint64_t io_read_trace_peripherals_0x40047000[3];

    uint64_t io_read_trace_peripherals_0x4003d014[4];

    uint64_t io_read_trace_peripherals_0x4004a058[3];

    uint64_t io_read_trace_peripherals_0x400ff054[4];

    uint64_t io_read_trace_peripherals_0x4004d068[3];

    uint64_t io_read_trace_peripherals_0x400ff114[3];

    uint64_t io_read_trace_peripherals_0x4004a054[3];

    uint64_t io_read_trace_peripherals_0x4004a040[3];

    uint64_t io_read_trace_peripherals_0x4004a044[3];

    uint64_t io_read_trace_peripherals_0x40048034[3];

    uint64_t io_read_trace_peripherals_0x4006a003[4];

    uint64_t io_read_trace_peripherals_0x4006a010[4];

    uint64_t io_read_trace_peripherals_0x4006a004[247];

    uint32_t irq_reg2;
} SynthState;


static void synth_write_peripherals(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
#ifdef PAPER_EVAL
        fprintf(stderr, "WRITE peripherals ADDR 0x%lx\n", addr);
#endif
        printf("\%c" ,(char)val);
        fflush(stdout);
}

static uint64_t synth_read_peripherals(void *opaque, hwaddr addr, unsigned size) {
    SynthState * sio = opaque;
    uint64_t res;
    switch(addr) {
        
        case 0x40048040 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40048040[1] < sio->io_read_trace_peripherals_0x40048040[0]) {
                sio->io_read_trace_peripherals_0x40048040[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40048040[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40048040[sio->io_read_trace_peripherals_0x40048040[1] + 1];
            break;


        case 0x40048038 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40048038[1] < sio->io_read_trace_peripherals_0x40048038[0]) {
                sio->io_read_trace_peripherals_0x40048038[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40048038[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40048038[sio->io_read_trace_peripherals_0x40048038[1] + 1];
            break;


        case 0x40049048 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40049048[1] < sio->io_read_trace_peripherals_0x40049048[0]) {
                sio->io_read_trace_peripherals_0x40049048[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40049048[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40049048[sio->io_read_trace_peripherals_0x40049048[1] + 1];
            break;


        case 0x4007e000 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4007e000[1] < sio->io_read_trace_peripherals_0x4007e000[0]) {
                sio->io_read_trace_peripherals_0x4007e000[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4007e000[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4007e000[sio->io_read_trace_peripherals_0x4007e000[1] + 1];
            break;


        case 0x40064001 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40064001[1] < sio->io_read_trace_peripherals_0x40064001[0]) {
                sio->io_read_trace_peripherals_0x40064001[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40064001[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40064001[sio->io_read_trace_peripherals_0x40064001[1] + 1];
            break;


        case 0x40064005 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40064005[1] < sio->io_read_trace_peripherals_0x40064005[0]) {
                sio->io_read_trace_peripherals_0x40064005[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40064005[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40064005[sio->io_read_trace_peripherals_0x40064005[1] + 1];
            break;


        case 0x40064003 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40064003[1] < sio->io_read_trace_peripherals_0x40064003[0]) {
                sio->io_read_trace_peripherals_0x40064003[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40064003[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40064003[sio->io_read_trace_peripherals_0x40064003[1] + 1];
            break;


        case 0x40064000 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40064000[1] < sio->io_read_trace_peripherals_0x40064000[0]) {
                sio->io_read_trace_peripherals_0x40064000[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40064000[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40064000[sio->io_read_trace_peripherals_0x40064000[1] + 1];
            break;


        case 0x40064006 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40064006[1] < sio->io_read_trace_peripherals_0x40064006[0]) {
                sio->io_read_trace_peripherals_0x40064006[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40064006[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40064006[sio->io_read_trace_peripherals_0x40064006[1] + 1];
            break;


        case 0x40064008 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40064008[1] < sio->io_read_trace_peripherals_0x40064008[0]) {
                sio->io_read_trace_peripherals_0x40064008[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40064008[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40064008[sio->io_read_trace_peripherals_0x40064008[1] + 1];
            break;


        case 0x4004803c - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4004803c[1] < sio->io_read_trace_peripherals_0x4004803c[0]) {
                sio->io_read_trace_peripherals_0x4004803c[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4004803c[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4004803c[sio->io_read_trace_peripherals_0x4004803c[1] + 1];
            break;


        case 0x4003d010 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4003d010[1] < sio->io_read_trace_peripherals_0x4003d010[0]) {
                sio->io_read_trace_peripherals_0x4003d010[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4003d010[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4003d010[sio->io_read_trace_peripherals_0x4003d010[1] + 1];
            break;


        case 0x40047000 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40047000[1] < sio->io_read_trace_peripherals_0x40047000[0]) {
                sio->io_read_trace_peripherals_0x40047000[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40047000[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40047000[sio->io_read_trace_peripherals_0x40047000[1] + 1];
            break;


        case 0x4003d014 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4003d014[1] < sio->io_read_trace_peripherals_0x4003d014[0]) {
                sio->io_read_trace_peripherals_0x4003d014[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4003d014[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4003d014[sio->io_read_trace_peripherals_0x4003d014[1] + 1];
            break;


        case 0x4004a058 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4004a058[1] < sio->io_read_trace_peripherals_0x4004a058[0]) {
                sio->io_read_trace_peripherals_0x4004a058[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4004a058[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4004a058[sio->io_read_trace_peripherals_0x4004a058[1] + 1];
            break;


        case 0x400ff054 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400ff054[1] < sio->io_read_trace_peripherals_0x400ff054[0]) {
                sio->io_read_trace_peripherals_0x400ff054[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400ff054[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400ff054[sio->io_read_trace_peripherals_0x400ff054[1] + 1];
            break;


        case 0x4004d068 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4004d068[1] < sio->io_read_trace_peripherals_0x4004d068[0]) {
                sio->io_read_trace_peripherals_0x4004d068[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4004d068[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4004d068[sio->io_read_trace_peripherals_0x4004d068[1] + 1];
            break;


        case 0x400ff114 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400ff114[1] < sio->io_read_trace_peripherals_0x400ff114[0]) {
                sio->io_read_trace_peripherals_0x400ff114[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400ff114[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400ff114[sio->io_read_trace_peripherals_0x400ff114[1] + 1];
            break;


        case 0x4004a054 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4004a054[1] < sio->io_read_trace_peripherals_0x4004a054[0]) {
                sio->io_read_trace_peripherals_0x4004a054[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4004a054[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4004a054[sio->io_read_trace_peripherals_0x4004a054[1] + 1];
            break;


        case 0x4004a040 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4004a040[1] < sio->io_read_trace_peripherals_0x4004a040[0]) {
                sio->io_read_trace_peripherals_0x4004a040[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4004a040[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4004a040[sio->io_read_trace_peripherals_0x4004a040[1] + 1];
            break;


        case 0x4004a044 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4004a044[1] < sio->io_read_trace_peripherals_0x4004a044[0]) {
                sio->io_read_trace_peripherals_0x4004a044[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4004a044[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4004a044[sio->io_read_trace_peripherals_0x4004a044[1] + 1];
            break;


        case 0x40048034 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x40048034[1] < sio->io_read_trace_peripherals_0x40048034[0]) {
                sio->io_read_trace_peripherals_0x40048034[1]++;
            } else {
                sio->io_read_trace_peripherals_0x40048034[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x40048034[sio->io_read_trace_peripherals_0x40048034[1] + 1];
            break;


        case 0x4006a003 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4006a003[1] < sio->io_read_trace_peripherals_0x4006a003[0]) {
                sio->io_read_trace_peripherals_0x4006a003[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4006a003[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4006a003[sio->io_read_trace_peripherals_0x4006a003[1] + 1];
            break;


        case 0x4006a010 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4006a010[1] < sio->io_read_trace_peripherals_0x4006a010[0]) {
                sio->io_read_trace_peripherals_0x4006a010[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4006a010[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4006a010[sio->io_read_trace_peripherals_0x4006a010[1] + 1];
            break;


        case 0x4006a004 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x4006a004[1] < sio->io_read_trace_peripherals_0x4006a004[0]) {
                sio->io_read_trace_peripherals_0x4006a004[1]++;
            } else {
                sio->io_read_trace_peripherals_0x4006a004[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x4006a004[sio->io_read_trace_peripherals_0x4006a004[1] + 1];
            break;

        default:
            res = 0xffffffffffffffff;
            break;
    }
#ifdef PAPER_EVAL
    fprintf(stderr, "READ peripherals ADDR 0x%lx VAL 0x%lx\n", addr, res);
#endif
    return res;
}

static const MemoryRegionOps synth_io_ops_peripherals =
{
    .write = synth_write_peripherals,
    .read = synth_read_peripherals,
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
        &sio->io_peripherals, obj, &synth_io_ops_peripherals, sio, TYPE_SYNTH, 0x10000000
    );
    sysbus_init_mmio(dev, &sio->io_peripherals);
    memory_region_add_subregion(sysbus, 0x40000000, &sio->io_peripherals);

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;

    uint64_t trace_peripherals_0x40048040[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x40048040[i] = trace_peripherals_0x40048040[i];
    }

    uint64_t trace_peripherals_0x40048038[] = {6, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80000000};
    for (int i = 0; i < 8; i++) {
        sio->io_read_trace_peripherals_0x40048038[i] = trace_peripherals_0x40048038[i];
    }

    uint64_t trace_peripherals_0x40049048[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x40049048[i] = trace_peripherals_0x40049048[i];
    }

    uint64_t trace_peripherals_0x4007e000[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4007e000[i] = trace_peripherals_0x4007e000[i];
    }

    uint64_t trace_peripherals_0x40064001[] = {6, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 8; i++) {
        sio->io_read_trace_peripherals_0x40064001[i] = trace_peripherals_0x40064001[i];
    }

    uint64_t trace_peripherals_0x40064005[] = {3, 0, 0x0, 0x80, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_peripherals_0x40064005[i] = trace_peripherals_0x40064005[i];
    }

    uint64_t trace_peripherals_0x40064003[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x40064003[i] = trace_peripherals_0x40064003[i];
    }

    uint64_t trace_peripherals_0x40064000[] = {7, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 9; i++) {
        sio->io_read_trace_peripherals_0x40064000[i] = trace_peripherals_0x40064000[i];
    }

    uint64_t trace_peripherals_0x40064006[] = {35, 0, 0x0, 0x0, 0x0, 0x0, 0x10, 0x8, 0x4, 0x4, 0x4, 0x0, 0xc, 0xc, 0xc, 0xc, 0x8, 0xc, 0xc, 0xc, 0xc, 0x8, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0xc};
    for (int i = 0; i < 37; i++) {
        sio->io_read_trace_peripherals_0x40064006[i] = trace_peripherals_0x40064006[i];
    }

    uint64_t trace_peripherals_0x40064008[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x40064008[i] = trace_peripherals_0x40064008[i];
    }

    uint64_t trace_peripherals_0x4004803c[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x4004803c[i] = trace_peripherals_0x4004803c[i];
    }

    uint64_t trace_peripherals_0x4003d010[] = {1, 0, 0x100};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4003d010[i] = trace_peripherals_0x4003d010[i];
    }

    uint64_t trace_peripherals_0x40047000[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x40047000[i] = trace_peripherals_0x40047000[i];
    }

    uint64_t trace_peripherals_0x4003d014[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x4003d014[i] = trace_peripherals_0x4003d014[i];
    }

    uint64_t trace_peripherals_0x4004a058[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4004a058[i] = trace_peripherals_0x4004a058[i];
    }

    uint64_t trace_peripherals_0x400ff054[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x400ff054[i] = trace_peripherals_0x400ff054[i];
    }

    uint64_t trace_peripherals_0x4004d068[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4004d068[i] = trace_peripherals_0x4004d068[i];
    }

    uint64_t trace_peripherals_0x400ff114[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x400ff114[i] = trace_peripherals_0x400ff114[i];
    }

    uint64_t trace_peripherals_0x4004a054[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4004a054[i] = trace_peripherals_0x4004a054[i];
    }

    uint64_t trace_peripherals_0x4004a040[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4004a040[i] = trace_peripherals_0x4004a040[i];
    }

    uint64_t trace_peripherals_0x4004a044[] = {1, 0, 0x10000};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x4004a044[i] = trace_peripherals_0x4004a044[i];
    }

    uint64_t trace_peripherals_0x40048034[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x40048034[i] = trace_peripherals_0x40048034[i];
    }

    uint64_t trace_peripherals_0x4006a003[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x4006a003[i] = trace_peripherals_0x4006a003[i];
    }

    uint64_t trace_peripherals_0x4006a010[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x4006a010[i] = trace_peripherals_0x4006a010[i];
    }

    uint64_t trace_peripherals_0x4006a004[] = {245, 0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x80};
    for (int i = 0; i < 247; i++) {
        sio->io_read_trace_peripherals_0x4006a004[i] = trace_peripherals_0x4006a004[i];
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
