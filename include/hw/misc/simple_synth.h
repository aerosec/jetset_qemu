#ifndef SIMPLE_SYNTH_H
#define SYNTH_SYNTH_H

#include "hw/sysbus.h"
#define TYPE_SIMPLE_SYNTH "simple_synth"
#define SIMPLE_SYNTH(obj) OBJECT_CHECK(SimpleSynthState, (obj), TYPE_SIMPLE_SYNTH)

typedef struct {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint size;
    uint base_addr;
} SimpleSynthState;
#endif
