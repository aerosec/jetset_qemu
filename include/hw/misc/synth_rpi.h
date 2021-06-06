#ifndef SYNTH_RPI_H
#define SYNTH_RPI_H

#include "hw/sysbus.h"
#define TYPE_SYNTH "synth_rpi"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)

typedef struct {
    SysBusDevice parent_obj;
    int global_idx;


    MemoryRegion io_dma;

    MemoryRegion io_ic;

    MemoryRegion io_mbox;

    MemoryRegion io_rng;

    MemoryRegion io_gpio;

    MemoryRegion io_pl011;

    MemoryRegion io_mmc;

    MemoryRegion io_i2c;

    MemoryRegion io_aux;

    MemoryRegion io_sdhci;

    MemoryRegion io_dma_chan15;

    MemoryRegion io_soc_control;

    qemu_irq gpu_irq;
    uint32_t irq_reg;
    qemu_irq gpu_fiq;
    qemu_irq irq_out[1];
    uint32_t irq_reg2;
    uint32_t gpu_triggered;
    uint32_t timer_triggered;
} SynthState;

#endif

 
