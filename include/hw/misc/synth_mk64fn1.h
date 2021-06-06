#ifndef SYNTH_MK64FN1_H
#define SYNTH_MK64FN1_H

#include "hw/sysbus.h"
#define TYPE_SYNTH "synth_mk64fn1"
#define SYNTH(obj) OBJECT_CHECK(SynthState, (obj), TYPE_SYNTH)

typedef struct {
    SysBusDevice parent_obj;
    MemoryRegion io_block1;
    MemoryRegion io_block2;
} SynthState;

#endif

 