#ifndef SYNTH_SAM3X8E_H
#define SYNTH_SAM3X8E_H

#include "hw/sysbus.h"
#define TYPE_SYNTH "synth_sam3x8e"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)

typedef struct {
    SysBusDevice parent_obj;
    MemoryRegion io_block1;
} SynthState;

#endif

 