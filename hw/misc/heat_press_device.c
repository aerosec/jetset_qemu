
#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/i386/pc.h"
#include <unistd.h>

#define TYPE_SYNTH "heat_press_device"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)
//#define ARM_IRQS 8
//#define BCM2835_IC_ARM_IRQ "arm-irq"


typedef struct {
    SysBusDevice parent_obj;
    qemu_irq* irq_set;
    int global_idx;


    MemoryRegion io_peripherals;

    uint64_t io_read_trace_peripherals_0x400e0620[3];

    uint64_t io_read_trace_peripherals_0x400e0668[32];

    uint64_t io_read_trace_peripherals_0x400e0630[3];

    uint64_t io_read_trace_peripherals_0x400e0e08[33];

    uint64_t io_read_trace_peripherals_0x400e1008[16];

    uint64_t io_read_trace_peripherals_0x400e1208[29];

    uint64_t io_read_trace_peripherals_0x400e1218[10];

    uint64_t io_read_trace_peripherals_0x400e1408[13];

    uint64_t io_read_trace_peripherals_0x400e1418[4];

    uint64_t io_read_trace_peripherals_0x400e0e18[11];

    uint64_t io_read_trace_peripherals_0x400e1018[3];

    uint64_t io_read_trace_peripherals_0x400e0e70[10];

    uint64_t io_read_trace_peripherals_0x400e1470[3];

    uint64_t io_read_trace_peripherals_0x400e1070[6];

    uint64_t io_read_trace_peripherals_0x400e0708[3];

    uint64_t io_read_trace_peripherals_0x400c0004[5];

    uint64_t io_read_trace_peripherals_0x400e0618[4];

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
        
        case 0x400e0620 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0620[1] < sio->io_read_trace_peripherals_0x400e0620[0]) {
                sio->io_read_trace_peripherals_0x400e0620[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0620[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0620[sio->io_read_trace_peripherals_0x400e0620[1] + 1];
            break;


        case 0x400e0668 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0668[1] < sio->io_read_trace_peripherals_0x400e0668[0]) {
                sio->io_read_trace_peripherals_0x400e0668[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0668[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0668[sio->io_read_trace_peripherals_0x400e0668[1] + 1];
            break;


        case 0x400e0630 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0630[1] < sio->io_read_trace_peripherals_0x400e0630[0]) {
                sio->io_read_trace_peripherals_0x400e0630[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0630[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0630[sio->io_read_trace_peripherals_0x400e0630[1] + 1];
            break;


        case 0x400e0e08 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0e08[1] < sio->io_read_trace_peripherals_0x400e0e08[0]) {
                sio->io_read_trace_peripherals_0x400e0e08[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0e08[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0e08[sio->io_read_trace_peripherals_0x400e0e08[1] + 1];
            break;


        case 0x400e1008 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1008[1] < sio->io_read_trace_peripherals_0x400e1008[0]) {
                sio->io_read_trace_peripherals_0x400e1008[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1008[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1008[sio->io_read_trace_peripherals_0x400e1008[1] + 1];
            break;


        case 0x400e1208 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1208[1] < sio->io_read_trace_peripherals_0x400e1208[0]) {
                sio->io_read_trace_peripherals_0x400e1208[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1208[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1208[sio->io_read_trace_peripherals_0x400e1208[1] + 1];
            break;


        case 0x400e1218 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1218[1] < sio->io_read_trace_peripherals_0x400e1218[0]) {
                sio->io_read_trace_peripherals_0x400e1218[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1218[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1218[sio->io_read_trace_peripherals_0x400e1218[1] + 1];
            break;


        case 0x400e1408 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1408[1] < sio->io_read_trace_peripherals_0x400e1408[0]) {
                sio->io_read_trace_peripherals_0x400e1408[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1408[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1408[sio->io_read_trace_peripherals_0x400e1408[1] + 1];
            break;


        case 0x400e1418 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1418[1] < sio->io_read_trace_peripherals_0x400e1418[0]) {
                sio->io_read_trace_peripherals_0x400e1418[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1418[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1418[sio->io_read_trace_peripherals_0x400e1418[1] + 1];
            break;


        case 0x400e0e18 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0e18[1] < sio->io_read_trace_peripherals_0x400e0e18[0]) {
                sio->io_read_trace_peripherals_0x400e0e18[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0e18[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0e18[sio->io_read_trace_peripherals_0x400e0e18[1] + 1];
            break;


        case 0x400e1018 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1018[1] < sio->io_read_trace_peripherals_0x400e1018[0]) {
                sio->io_read_trace_peripherals_0x400e1018[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1018[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1018[sio->io_read_trace_peripherals_0x400e1018[1] + 1];
            break;


        case 0x400e0e70 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0e70[1] < sio->io_read_trace_peripherals_0x400e0e70[0]) {
                sio->io_read_trace_peripherals_0x400e0e70[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0e70[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0e70[sio->io_read_trace_peripherals_0x400e0e70[1] + 1];
            break;


        case 0x400e1470 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1470[1] < sio->io_read_trace_peripherals_0x400e1470[0]) {
                sio->io_read_trace_peripherals_0x400e1470[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1470[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1470[sio->io_read_trace_peripherals_0x400e1470[1] + 1];
            break;


        case 0x400e1070 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e1070[1] < sio->io_read_trace_peripherals_0x400e1070[0]) {
                sio->io_read_trace_peripherals_0x400e1070[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e1070[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e1070[sio->io_read_trace_peripherals_0x400e1070[1] + 1];
            break;


        case 0x400e0708 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0708[1] < sio->io_read_trace_peripherals_0x400e0708[0]) {
                sio->io_read_trace_peripherals_0x400e0708[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0708[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0708[sio->io_read_trace_peripherals_0x400e0708[1] + 1];
            break;


        case 0x400c0004 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400c0004[1] < sio->io_read_trace_peripherals_0x400c0004[0]) {
                sio->io_read_trace_peripherals_0x400c0004[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400c0004[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400c0004[sio->io_read_trace_peripherals_0x400c0004[1] + 1];
            break;


        case 0x400e0618 - 0x40000000:
            if (sio->io_read_trace_peripherals_0x400e0618[1] < sio->io_read_trace_peripherals_0x400e0618[0]) {
                sio->io_read_trace_peripherals_0x400e0618[1]++;
            } else {
                sio->io_read_trace_peripherals_0x400e0618[1] -= 0;
            }
            res = sio->io_read_trace_peripherals_0x400e0618[sio->io_read_trace_peripherals_0x400e0618[1] + 1];
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
        &sio->io_peripherals, obj, &synth_io_ops_peripherals, sio, TYPE_SYNTH, 0x20000000
    );
    sysbus_init_mmio(dev, &sio->io_peripherals);
    memory_region_add_subregion(sysbus, 0x40000000, &sio->io_peripherals);

}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;

    uint64_t trace_peripherals_0x400e0620[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x400e0620[i] = trace_peripherals_0x400e0620[i];
    }

    uint64_t trace_peripherals_0x400e0668[] = {30, 0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x10000, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x8};
    for (int i = 0; i < 32; i++) {
        sio->io_read_trace_peripherals_0x400e0668[i] = trace_peripherals_0x400e0668[i];
    }

    uint64_t trace_peripherals_0x400e0630[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x400e0630[i] = trace_peripherals_0x400e0630[i];
    }

    uint64_t trace_peripherals_0x400e0e08[] = {31, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x400, 0x0, 0x8000, 0x0, 0x0, 0x0, 0x10000, 0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x2000000, 0x0, 0x0, 0x0, 0x100, 0x0, 0x0};
    for (int i = 0; i < 33; i++) {
        sio->io_read_trace_peripherals_0x400e0e08[i] = trace_peripherals_0x400e0e08[i];
    }

    uint64_t trace_peripherals_0x400e1008[] = {14, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80000, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 16; i++) {
        sio->io_read_trace_peripherals_0x400e1008[i] = trace_peripherals_0x400e1008[i];
    }

    uint64_t trace_peripherals_0x400e1208[] = {27, 0, 0x0, 0x4000000, 0x0, 0x0, 0x0, 0x0, 0x200000, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x80000, 0x0, 0x0, 0x0, 0x0, 0x4000, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 29; i++) {
        sio->io_read_trace_peripherals_0x400e1208[i] = trace_peripherals_0x400e1208[i];
    }

    uint64_t trace_peripherals_0x400e1218[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x4000, 0xfffffffe, 0xfffffffe};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_peripherals_0x400e1218[i] = trace_peripherals_0x400e1218[i];
    }

    uint64_t trace_peripherals_0x400e1408[] = {11, 0, 0x0, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x0, 0x0};
    for (int i = 0; i < 13; i++) {
        sio->io_read_trace_peripherals_0x400e1408[i] = trace_peripherals_0x400e1408[i];
    }

    uint64_t trace_peripherals_0x400e1418[] = {2, 0, 0x0, 0x0};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x400e1418[i] = trace_peripherals_0x400e1418[i];
    }

    uint64_t trace_peripherals_0x400e0e18[] = {9, 0, 0x0, 0x8000, 0x0, 0x0, 0x0, 0x2000000, 0x0, 0xfffffffe, 0xfffffffe};
    for (int i = 0; i < 11; i++) {
        sio->io_read_trace_peripherals_0x400e0e18[i] = trace_peripherals_0x400e0e18[i];
    }

    uint64_t trace_peripherals_0x400e1018[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x400e1018[i] = trace_peripherals_0x400e1018[i];
    }

    uint64_t trace_peripherals_0x400e0e70[] = {8, 0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 10; i++) {
        sio->io_read_trace_peripherals_0x400e0e70[i] = trace_peripherals_0x400e0e70[i];
    }

    uint64_t trace_peripherals_0x400e1470[] = {1, 0, 0x0};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x400e1470[i] = trace_peripherals_0x400e1470[i];
    }

    uint64_t trace_peripherals_0x400e1070[] = {4, 0, 0x0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 6; i++) {
        sio->io_read_trace_peripherals_0x400e1070[i] = trace_peripherals_0x400e1070[i];
    }

    uint64_t trace_peripherals_0x400e0708[] = {1, 0, 0x20};
    for (int i = 0; i < 3; i++) {
        sio->io_read_trace_peripherals_0x400e0708[i] = trace_peripherals_0x400e0708[i];
    }

    uint64_t trace_peripherals_0x400c0004[] = {3, 0, 0x0, 0x0, 0x0};
    for (int i = 0; i < 5; i++) {
        sio->io_read_trace_peripherals_0x400c0004[i] = trace_peripherals_0x400c0004[i];
    }

    uint64_t trace_peripherals_0x400e0618[] = {2, 0, 0x800, 0x100};
    for (int i = 0; i < 4; i++) {
        sio->io_read_trace_peripherals_0x400e0618[i] = trace_peripherals_0x400e0618[i];
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
