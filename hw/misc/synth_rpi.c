#include "qemu/osdep.h"
#include "hw/qdev.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include <unistd.h>
#include "hw/misc/synth_rpi.h"
#include "monitor/monitor.h"
#include "qapi/qapi-events-misc.h" 
#include "exec/synth_controller.h"
#include "exec/taint.h"

#define NUM_IRQS 64
#define ARM_IRQS 8
#define BCM2835_IC_ARM_IRQ "arm-irq"



static void synth_write_dma(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    return taint_mmio_write(sio->io_dma.addr + addr, size);
}

static uint64_t synth_read_dma(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_dma.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_dma =
{
    .write = synth_write_dma,
    .read = synth_read_dma,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};


static int global_idx = 0;

static void gpu_ic_test_arm_irq(void *opaque, int irq, int level)
{

    SynthState* s = opaque;
    s->irq_reg = 0;
    qapi_event_send_gpio_set(irq, level);
    qemu_set_irq(s->gpu_irq, level);
}


static void synth_write_ic(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_ic.addr + addr, val);
}

static uint8_t curr_intr = 0;
static int next_irq_reg(void)
{
  curr_intr++;
  if(curr_intr > 7) {
    curr_intr = 0;
    return 0;
  }
  return 1 << curr_intr;
}

static uint64_t synth_read_ic(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    uint32_t v = next_irq_reg();
    taint_intc_read(sio->io_ic.addr + addr, v);
    return v;
}

static const MemoryRegionOps synth_io_ops_ic =
{
    .write = synth_write_ic,
    .read = synth_read_ic,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_mbox(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_mbox.addr + addr, val);


}

static uint64_t synth_read_mbox(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_mbox.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_mbox =
{
    .write = synth_write_mbox,
    .read = synth_read_mbox,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_rng(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_mmio_write(sio->io_rng.addr + addr, val);
}

static uint64_t synth_read_rng(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    global_idx++;
    return taint_mmio_read(sio->io_rng.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_rng =
{
    .write = synth_write_rng,
    .read = synth_read_rng,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_gpio(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState* sio = opaque;
    taint_mmio_write(sio->io_gpio.addr + addr, val);
}

static uint64_t synth_read_gpio(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_gpio.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_gpio =
{
    .write = synth_write_gpio,
    .read = synth_read_gpio,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_pl011(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
        SynthState *sio = opaque;
    taint_mmio_write(sio->io_pl011.addr + addr, val);
}

static uint64_t synth_read_pl011(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_pl011.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_pl011 =
{
    .write = synth_write_pl011,
    .read = synth_read_pl011,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_mmc(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
        SynthState *sio = opaque;
    taint_mmio_write(sio->io_mmc.addr + addr, val);

}

static uint64_t synth_read_mmc(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_mmc.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_mmc =
{
    .write = synth_write_mmc,
    .read = synth_read_mmc,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_i2c(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
        SynthState *sio = opaque;
    taint_mmio_write(sio->io_i2c.addr + addr, val);

}

static uint64_t synth_read_i2c(void *opaque, hwaddr addr, unsigned size) {
    printf("I2C Read %lx\n", addr);
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_i2c.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_i2c =
{
    .write = synth_write_i2c,
    .read = synth_read_i2c,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_aux(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
        SynthState *sio = opaque;
    taint_mmio_write(sio->io_aux.addr + addr, val);
}

static uint64_t synth_read_aux(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_aux.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_aux =
{
    .write = synth_write_aux,
    .read = synth_read_aux,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_sdhci(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
        SynthState *sio = opaque;
    taint_mmio_write(sio->io_sdhci.addr + addr, val);

}

static uint64_t synth_read_sdhci(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_sdhci.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_sdhci =
{
    .write = synth_write_sdhci,
    .read = synth_read_sdhci,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void synth_write_dma_chan15(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
        SynthState *sio = opaque;

    taint_mmio_write(sio->io_dma_chan15.addr + addr, val);
}

static uint64_t synth_read_dma_chan15(void *opaque, hwaddr addr, unsigned size) {
    SynthState* sio = opaque;
    return taint_mmio_read(sio->io_dma_chan15.addr + addr, size);
}

static const MemoryRegionOps synth_io_ops_dma_chan15 =
{
    .write = synth_write_dma_chan15,
    .read = synth_read_dma_chan15,
    .valid.min_access_size = 1,
    .valid.max_access_size = 4,
    .endianness = DEVICE_NATIVE_ENDIAN,
};


static int pending_intr = 0;

static int next_pending_irq_reg(void)
{ 
  if (pending_intr == 0)
    return 0;
  pending_intr += 1;
  if(pending_intr > 12) {
    pending_intr = 0;
    return 0;
  }
  return 1 << pending_intr;
}

/* Update interrupts.  */
static void synth_control_update(SynthState *s)
{
    s->irq_reg2 = 0;

    /* gpu => 0x100 */
    if (s->gpu_triggered && pending_intr == 0) {
        pending_intr = 1;
    }

    // timer => 0x8
    if(s->timer_triggered != 0){
        s->irq_reg2 |= (uint32_t)1 << 3;
    }

    qemu_set_irq(s->irq_out[0], s->irq_reg2 != 0 || pending_intr != 0);
}

static void synth_control_set_local_irq3(void *opaque, int core, int level)
{
    SynthState *s = opaque;
    s->timer_triggered = level;
    synth_control_update(s);
}

static void synth_control_set_gpu_irq(void *opaque, int irq, int level)
{
    SynthState *s = opaque;
    s->gpu_triggered = level;
    qapi_event_send_gpio_set(irq, level);
    synth_control_update(s);
}

static uint64_t synth_read_soc_control(void *opaque, hwaddr addr, unsigned size)
{
    SynthState *s = opaque;
    uint32_t v = s->irq_reg2;
    if(pending_intr)
        v = next_pending_irq_reg();

    if(v != 8)    
        taint_intc_read(s->io_soc_control.addr + addr, v);
    return v;
}


static void synth_write_soc_control(
    void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    SynthState *sio = opaque;
    taint_mmio_write(sio->io_soc_control.addr + addr, val);
}

static const MemoryRegionOps synth_io_ops_soc_control =
{
    .write = synth_write_soc_control,
    .read = synth_read_soc_control,
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
    sio->irq_reg = 0;
    
    memory_region_init_io(
        &sio->io_dma, obj, &synth_io_ops_dma, sio, TYPE_SYNTH, 0xb200
    );
    sysbus_init_mmio(dev, &sio->io_dma);
    memory_region_add_subregion(sysbus, 0x3f000000, &sio->io_dma);
    

    memory_region_init_io(
        &sio->io_ic, obj, &synth_io_ops_ic, sio, TYPE_SYNTH, 0x200
    );
    sysbus_init_mmio(dev, &sio->io_ic);
    memory_region_add_subregion(sysbus, 0x3f00b200, &sio->io_ic);


    memory_region_init_io(
        &sio->io_mbox, obj, &synth_io_ops_mbox, sio, TYPE_SYNTH, 0xf5c00
    );
    sysbus_init_mmio(dev, &sio->io_mbox);
    memory_region_add_subregion(sysbus, 0x3f00b400, &sio->io_mbox);

    
    memory_region_init_io(
        &sio->io_rng, obj, &synth_io_ops_rng, sio, TYPE_SYNTH, 0xFD000
    );
    sysbus_init_mmio(dev, &sio->io_rng);
    memory_region_add_subregion(sysbus, 0x3f103000, &sio->io_rng);

    
    memory_region_init_io(
        &sio->io_gpio, obj, &synth_io_ops_gpio, sio, TYPE_SYNTH, 0x1000
    );
    
    sysbus_init_mmio(dev, &sio->io_gpio);
    memory_region_add_subregion(sysbus, 0x3f101000, &sio->io_gpio);

    memory_region_init_io(
        &sio->io_sdhci, obj, &synth_io_ops_sdhci, sio, TYPE_SYNTH, 0xE00000
    );
    sysbus_init_mmio(dev, &sio->io_sdhci);
    memory_region_add_subregion(sysbus, 0x3f200000, &sio->io_sdhci);

    memory_region_init_io(
        &sio->io_soc_control, obj, &synth_io_ops_soc_control, sio, TYPE_SYNTH, 0x100
    );


    sysbus_init_mmio(dev, &sio->io_soc_control);
    memory_region_add_subregion(sysbus, 0x40000000, &sio->io_soc_control);
    
    
    
    qdev_init_gpio_in_named(DEVICE(dev), gpu_ic_test_arm_irq, BCM2835_IC_ARM_IRQ, ARM_IRQS);
    sysbus_init_irq(SYS_BUS_DEVICE(dev), &sio->gpu_irq);

    qdev_init_gpio_out_named(DEVICE(dev), sio->irq_out, "irq", 1);
    qdev_init_gpio_in_named(DEVICE(dev), synth_control_set_gpu_irq, "gpu-irq", 1);
    qdev_init_gpio_in_named(DEVICE(dev), synth_control_set_local_irq3, "cntvirq", 1);
}


static void synth_reset(DeviceState *d)
{
    SynthState *sio = SYNTH(d);

    sio->global_idx = 0;
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
