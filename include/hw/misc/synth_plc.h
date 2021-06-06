#ifndef SYNTH_PLC_H
#define SYNTH_PLC_H

#include "hw/sysbus.h"
extern int use_robot_dma;
#define TYPE_SYNTH "synth_plc"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)

typedef struct {
    SysBusDevice parent_obj;
    MemoryRegion io_block1;
    MemoryRegion io_block2;
    MemoryRegion io_fsmc_control_register;
    MemoryRegion io_block3;

} SynthState;

#endif

 