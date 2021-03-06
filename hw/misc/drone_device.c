
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "drone_device"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_block1;

    uint64_t io_read_trace_block1_0x40021000[16];

    uint64_t io_read_trace_block1_0x40021004[20];

    uint64_t io_read_trace_block1_0x40022000[9];

    uint64_t io_read_trace_block1_0x40021018[14];

    uint64_t io_read_trace_block1_0x40011004[5];

    uint64_t io_read_trace_block1_0x40010800[4];

    uint64_t io_read_trace_block1_0x40010c00[6];

    uint64_t io_read_trace_block1_0x4002101c[10];

    uint64_t io_read_trace_block1_0x40005400[178];

    uint64_t io_read_trace_block1_0x40010804[5];

    uint64_t io_read_trace_block1_0x4001380c[7];

    uint64_t io_read_trace_block1_0x40013810[4];

    uint64_t io_read_trace_block1_0x40013814[5];

    uint64_t io_read_trace_block1_0x40012c00[3];

    uint64_t io_read_trace_block1_0x40012c04[5];

    uint64_t io_read_trace_block1_0x40012c08[4];

    uint64_t io_read_trace_block1_0x40012c20[4];

    uint64_t io_read_trace_block1_0x40012c1c[6];

    uint64_t io_read_trace_block1_0x40000000[4];

    uint64_t io_read_trace_block1_0x40000004[5];

    uint64_t io_read_trace_block1_0x40000008[4];

    uint64_t io_read_trace_block1_0x40000020[6];

    uint64_t io_read_trace_block1_0x40000018[6];

    uint64_t io_read_trace_block1_0x40000400[4];

    uint64_t io_read_trace_block1_0x40000404[6];

    uint64_t io_read_trace_block1_0x40000408[4];

    uint64_t io_read_trace_block1_0x40000420[8];

    uint64_t io_read_trace_block1_0x4000041c[10];

    uint64_t io_read_trace_block1_0x40000800[5];

    uint64_t io_read_trace_block1_0x40000804[6];

    uint64_t io_read_trace_block1_0x40000808[4];

    uint64_t io_read_trace_block1_0x40000820[10];

    uint64_t io_read_trace_block1_0x4000081c[10];

    uint64_t io_read_trace_block1_0x40010c04[4];

    uint64_t io_read_trace_block1_0x40005418[245];

    uint64_t io_read_trace_block1_0x40005414[1423];

    uint64_t io_read_trace_block1_0x40005410[23];

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


        case 0x40021018 - 0x40000000:
            if (sio->io_read_trace_block1_0x40021018[1] < sio->io_read_trace_block1_0x40021018[0]) {
                sio->io_read_trace_block1_0x40021018[1]++;
            } else {
                sio->io_read_trace_block1_0x40021018[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40021018[sio->io_read_trace_block1_0x40021018[1] + 1];
            break;


        case 0x40011004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40011004[1] < sio->io_read_trace_block1_0x40011004[0]) {
                sio->io_read_trace_block1_0x40011004[1]++;
            } else {
                sio->io_read_trace_block1_0x40011004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40011004[sio->io_read_trace_block1_0x40011004[1] + 1];
            break;


        case 0x40010800 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010800[1] < sio->io_read_trace_block1_0x40010800[0]) {
                sio->io_read_trace_block1_0x40010800[1]++;
            } else {
                sio->io_read_trace_block1_0x40010800[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010800[sio->io_read_trace_block1_0x40010800[1] + 1];
            break;


        case 0x40010c00 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010c00[1] < sio->io_read_trace_block1_0x40010c00[0]) {
                sio->io_read_trace_block1_0x40010c00[1]++;
            } else {
                sio->io_read_trace_block1_0x40010c00[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010c00[sio->io_read_trace_block1_0x40010c00[1] + 1];
            break;


        case 0x4002101c - 0x40000000:
            if (sio->io_read_trace_block1_0x4002101c[1] < sio->io_read_trace_block1_0x4002101c[0]) {
                sio->io_read_trace_block1_0x4002101c[1]++;
            } else {
                sio->io_read_trace_block1_0x4002101c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4002101c[sio->io_read_trace_block1_0x4002101c[1] + 1];
            break;


        case 0x40005400 - 0x40000000:
            if (sio->io_read_trace_block1_0x40005400[1] < sio->io_read_trace_block1_0x40005400[0]) {
                sio->io_read_trace_block1_0x40005400[1]++;
            } else {
                sio->io_read_trace_block1_0x40005400[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40005400[sio->io_read_trace_block1_0x40005400[1] + 1];
            break;


        case 0x40010804 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010804[1] < sio->io_read_trace_block1_0x40010804[0]) {
                sio->io_read_trace_block1_0x40010804[1]++;
            } else {
                sio->io_read_trace_block1_0x40010804[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010804[sio->io_read_trace_block1_0x40010804[1] + 1];
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


        case 0x40012c00 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c00[1] < sio->io_read_trace_block1_0x40012c00[0]) {
                sio->io_read_trace_block1_0x40012c00[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c00[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c00[sio->io_read_trace_block1_0x40012c00[1] + 1];
            break;


        case 0x40012c04 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c04[1] < sio->io_read_trace_block1_0x40012c04[0]) {
                sio->io_read_trace_block1_0x40012c04[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c04[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c04[sio->io_read_trace_block1_0x40012c04[1] + 1];
            break;


        case 0x40012c08 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c08[1] < sio->io_read_trace_block1_0x40012c08[0]) {
                sio->io_read_trace_block1_0x40012c08[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c08[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c08[sio->io_read_trace_block1_0x40012c08[1] + 1];
            break;


        case 0x40012c20 - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c20[1] < sio->io_read_trace_block1_0x40012c20[0]) {
                sio->io_read_trace_block1_0x40012c20[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c20[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c20[sio->io_read_trace_block1_0x40012c20[1] + 1];
            break;


        case 0x40012c1c - 0x40000000:
            if (sio->io_read_trace_block1_0x40012c1c[1] < sio->io_read_trace_block1_0x40012c1c[0]) {
                sio->io_read_trace_block1_0x40012c1c[1]++;
            } else {
                sio->io_read_trace_block1_0x40012c1c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40012c1c[sio->io_read_trace_block1_0x40012c1c[1] + 1];
            break;


        case 0x40000000 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000000[1] < sio->io_read_trace_block1_0x40000000[0]) {
                sio->io_read_trace_block1_0x40000000[1]++;
            } else {
                sio->io_read_trace_block1_0x40000000[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000000[sio->io_read_trace_block1_0x40000000[1] + 1];
            break;


        case 0x40000004 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000004[1] < sio->io_read_trace_block1_0x40000004[0]) {
                sio->io_read_trace_block1_0x40000004[1]++;
            } else {
                sio->io_read_trace_block1_0x40000004[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000004[sio->io_read_trace_block1_0x40000004[1] + 1];
            break;


        case 0x40000008 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000008[1] < sio->io_read_trace_block1_0x40000008[0]) {
                sio->io_read_trace_block1_0x40000008[1]++;
            } else {
                sio->io_read_trace_block1_0x40000008[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000008[sio->io_read_trace_block1_0x40000008[1] + 1];
            break;


        case 0x40000020 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000020[1] < sio->io_read_trace_block1_0x40000020[0]) {
                sio->io_read_trace_block1_0x40000020[1]++;
            } else {
                sio->io_read_trace_block1_0x40000020[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000020[sio->io_read_trace_block1_0x40000020[1] + 1];
            break;


        case 0x40000018 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000018[1] < sio->io_read_trace_block1_0x40000018[0]) {
                sio->io_read_trace_block1_0x40000018[1]++;
            } else {
                sio->io_read_trace_block1_0x40000018[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000018[sio->io_read_trace_block1_0x40000018[1] + 1];
            break;


        case 0x40000400 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000400[1] < sio->io_read_trace_block1_0x40000400[0]) {
                sio->io_read_trace_block1_0x40000400[1]++;
            } else {
                sio->io_read_trace_block1_0x40000400[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000400[sio->io_read_trace_block1_0x40000400[1] + 1];
            break;


        case 0x40000404 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000404[1] < sio->io_read_trace_block1_0x40000404[0]) {
                sio->io_read_trace_block1_0x40000404[1]++;
            } else {
                sio->io_read_trace_block1_0x40000404[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000404[sio->io_read_trace_block1_0x40000404[1] + 1];
            break;


        case 0x40000408 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000408[1] < sio->io_read_trace_block1_0x40000408[0]) {
                sio->io_read_trace_block1_0x40000408[1]++;
            } else {
                sio->io_read_trace_block1_0x40000408[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000408[sio->io_read_trace_block1_0x40000408[1] + 1];
            break;


        case 0x40000420 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000420[1] < sio->io_read_trace_block1_0x40000420[0]) {
                sio->io_read_trace_block1_0x40000420[1]++;
            } else {
                sio->io_read_trace_block1_0x40000420[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000420[sio->io_read_trace_block1_0x40000420[1] + 1];
            break;


        case 0x4000041c - 0x40000000:
            if (sio->io_read_trace_block1_0x4000041c[1] < sio->io_read_trace_block1_0x4000041c[0]) {
                sio->io_read_trace_block1_0x4000041c[1]++;
            } else {
                sio->io_read_trace_block1_0x4000041c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4000041c[sio->io_read_trace_block1_0x4000041c[1] + 1];
            break;


        case 0x40000800 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000800[1] < sio->io_read_trace_block1_0x40000800[0]) {
                sio->io_read_trace_block1_0x40000800[1]++;
            } else {
                sio->io_read_trace_block1_0x40000800[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000800[sio->io_read_trace_block1_0x40000800[1] + 1];
            break;


        case 0x40000804 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000804[1] < sio->io_read_trace_block1_0x40000804[0]) {
                sio->io_read_trace_block1_0x40000804[1]++;
            } else {
                sio->io_read_trace_block1_0x40000804[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000804[sio->io_read_trace_block1_0x40000804[1] + 1];
            break;


        case 0x40000808 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000808[1] < sio->io_read_trace_block1_0x40000808[0]) {
                sio->io_read_trace_block1_0x40000808[1]++;
            } else {
                sio->io_read_trace_block1_0x40000808[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000808[sio->io_read_trace_block1_0x40000808[1] + 1];
            break;


        case 0x40000820 - 0x40000000:
            if (sio->io_read_trace_block1_0x40000820[1] < sio->io_read_trace_block1_0x40000820[0]) {
                sio->io_read_trace_block1_0x40000820[1]++;
            } else {
                sio->io_read_trace_block1_0x40000820[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40000820[sio->io_read_trace_block1_0x40000820[1] + 1];
            break;


        case 0x4000081c - 0x40000000:
            if (sio->io_read_trace_block1_0x4000081c[1] < sio->io_read_trace_block1_0x4000081c[0]) {
                sio->io_read_trace_block1_0x4000081c[1]++;
            } else {
                sio->io_read_trace_block1_0x4000081c[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x4000081c[sio->io_read_trace_block1_0x4000081c[1] + 1];
            break;


        case 0x40010c04 - 0x40000000:
            if (sio->io_read_trace_block1_0x40010c04[1] < sio->io_read_trace_block1_0x40010c04[0]) {
                sio->io_read_trace_block1_0x40010c04[1]++;
            } else {
                sio->io_read_trace_block1_0x40010c04[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40010c04[sio->io_read_trace_block1_0x40010c04[1] + 1];
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


        case 0x40005410 - 0x40000000:
            if (sio->io_read_trace_block1_0x40005410[1] < sio->io_read_trace_block1_0x40005410[0]) {
                sio->io_read_trace_block1_0x40005410[1]++;
            } else {
                sio->io_read_trace_block1_0x40005410[1] -= 0;
            }
            res = sio->io_read_trace_block1_0x40005410[sio->io_read_trace_block1_0x40005410[1] + 1];
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

    uint64_t trace_block1_0x40021000[] = {14, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2000000, 0x2000000, 0x2000000, 0x2000000, 0x0, 0x0, 0x2000000, 0x0};
    for (int i = 0; i < 16; i++) {
        sio->io_read_trace_block1_0x40021000[i] = trace_block1_0x40021000[i];
    }

    uint64_t trace_block1_0x40021004[] = {18, 0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 20; i++) {
        sio->io_read_trace_block1_0x40021004[i] = trace_block1_0x40021004[i];
    }

    uint64_t trace_block1_0x40022000[] = {7, 0, 0x0, 0x0, 0x0, 0x2, 0x3, 0x0, 0x2};
    for (int i = 0; i < 9; i++) {
        sio->io_read_trace_block1_0x40022000[i] = trace_block1_0x40022000[i];
    }

    uint64_t trace_block1_0x40021018[] = {12, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 14; i++) {
        sio->io_read_trace_block1_0x40021018[i] = trace_block1_0x40021018[i];
    }

    uint64_t trace_block1_0x40011004[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40011004[i] = trace_block1_0x40011004[i];
    }

    uint64_t trace_block1_0x40010800[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40010800[i] = trace_block1_0x40010800[i];
    }

    uint64_t trace_block1_0x40010c00[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40010c00[i] = trace_block1_0x40010c00[i];
    }

    uint64_t trace_block1_0x4002101c[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x4002101c[i] = trace_block1_0x4002101c[i];
    }

    uint64_t trace_block1_0x40005400[] = {176, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 178; i++) {
        sio->io_read_trace_block1_0x40005400[i] = trace_block1_0x40005400[i];
    }

    uint64_t trace_block1_0x40010804[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40010804[i] = trace_block1_0x40010804[i];
    }

    uint64_t trace_block1_0x4001380c[] = {5, 0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 7; i++) {
        sio->io_read_trace_block1_0x4001380c[i] = trace_block1_0x4001380c[i];
    }

    uint64_t trace_block1_0x40013810[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40013810[i] = trace_block1_0x40013810[i];
    }

    uint64_t trace_block1_0x40013814[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40013814[i] = trace_block1_0x40013814[i];
    }

    uint64_t trace_block1_0x40012c00[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_block1_0x40012c00[i] = trace_block1_0x40012c00[i];
    }

    uint64_t trace_block1_0x40012c04[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40012c04[i] = trace_block1_0x40012c04[i];
    }

    uint64_t trace_block1_0x40012c08[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40012c08[i] = trace_block1_0x40012c08[i];
    }

    uint64_t trace_block1_0x40012c20[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40012c20[i] = trace_block1_0x40012c20[i];
    }

    uint64_t trace_block1_0x40012c1c[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40012c1c[i] = trace_block1_0x40012c1c[i];
    }

    uint64_t trace_block1_0x40000000[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000000[i] = trace_block1_0x40000000[i];
    }

    uint64_t trace_block1_0x40000004[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40000004[i] = trace_block1_0x40000004[i];
    }

    uint64_t trace_block1_0x40000008[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000008[i] = trace_block1_0x40000008[i];
    }

    uint64_t trace_block1_0x40000020[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40000020[i] = trace_block1_0x40000020[i];
    }

    uint64_t trace_block1_0x40000018[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40000018[i] = trace_block1_0x40000018[i];
    }

    uint64_t trace_block1_0x40000400[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000400[i] = trace_block1_0x40000400[i];
    }

    uint64_t trace_block1_0x40000404[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40000404[i] = trace_block1_0x40000404[i];
    }

    uint64_t trace_block1_0x40000408[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000408[i] = trace_block1_0x40000408[i];
    }

    uint64_t trace_block1_0x40000420[] = {6, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 8; i++) {
        sio->io_read_trace_block1_0x40000420[i] = trace_block1_0x40000420[i];
    }

    uint64_t trace_block1_0x4000041c[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x4000041c[i] = trace_block1_0x4000041c[i];
    }

    uint64_t trace_block1_0x40000800[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_block1_0x40000800[i] = trace_block1_0x40000800[i];
    }

    uint64_t trace_block1_0x40000804[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_block1_0x40000804[i] = trace_block1_0x40000804[i];
    }

    uint64_t trace_block1_0x40000808[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40000808[i] = trace_block1_0x40000808[i];
    }

    uint64_t trace_block1_0x40000820[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x40000820[i] = trace_block1_0x40000820[i];
    }

    uint64_t trace_block1_0x4000081c[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_block1_0x4000081c[i] = trace_block1_0x4000081c[i];
    }

    uint64_t trace_block1_0x40010c04[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_block1_0x40010c04[i] = trace_block1_0x40010c04[i];
    }

    uint64_t trace_block1_0x40005418[] = {243, 0, 0x8000002, 0x10820002, 0x2, 0x1002, 0x0, 0x0, 0x0, 0x21000002, 0x90817aa, 0x7a565077, 0xfc3de63a, 0x6208027c, 0x0, 0x20047fb, 0x2000302, 0x78001e7, 0x7c00182a, 0x1004, 0x0, 0x23c00002, 0x46200aba, 0x3e1803, 0x18048786, 0x68000078, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x2, 0x2, 0x800002, 0x80002, 0x0, 0x0, 0x2, 0x10002, 0x8010002, 0xe0008012, 0x7c300904, 0x0, 0x2, 0x3d0002, 0x500e0c02, 0x7a, 0x3ffb008, 0x0, 0x220001ff, 0x2, 0x62, 0x2, 0xb0001, 0x0, 0x800813, 0x2, 0xf8000002, 0xaf80003e, 0x1ffffffd, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2ee02, 0x2, 0x1b9a, 0x2, 0x7000, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x3ad12002, 0xff78fb82, 0x77fff2, 0x2, 0x8, 0x0, 0x508cf2, 0xfef00036, 0xdfbffe1a, 0x3001002, 0x27fe057d, 0x0, 0x0, 0x2, 0x2, 0x802, 0x60000002, 0x0, 0x0, 0x0, 0xe001f, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0};
    for (int i = 0; i < 245; i++) {
        sio->io_read_trace_block1_0x40005418[i] = trace_block1_0x40005418[i];
    }

    uint64_t trace_block1_0x40005414[] = {1421, 0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x4001002, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x8100c202, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x6413, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x85000002, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x18002, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0xefbe03, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x80000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0xc5c78c3a, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x180006ea, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x802, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x6002, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40};
    for (int i = 0; i < 1423; i++) {
        sio->io_read_trace_block1_0x40005414[i] = trace_block1_0x40005414[i];
    }

    uint64_t trace_block1_0x40005410[] = {21, 0, 0x0, 0x0, 0x80000080, 0x80000080, 0x80000080, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 23; i++) {
        sio->io_read_trace_block1_0x40005410[i] = trace_block1_0x40005410[i];
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
