/*
  See .c file for general description
*/
#ifndef SHADOW_MEM_H
#define SHADOW_MEM_H

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "exec/synth_controller.h"

//#define NB_SEG_TBL_ENTRIES (0x01 << 20)
#define SHADOW_PAGE_SIZE (0x01 << 24)
#define SHADOW_PAGE_MASK 0x0000000000ffffff
#define SHADOW_PAGE_OFFSET(x) (x & SHADOW_PAGE_MASK)
#define LAYER1_MASK 0x00000000000fffff
#define LAYER1_IDX(x) ((x >> 44) & LAYER1_MASK)
#define LAYER2_MASK 0x00000000000fffff
#define LAYER2_IDX(x) ((x >> 24) & LAYER2_MASK)

#define TAINT_MASK(x) ((uint64_t)(x & 0xFF00000000000000)) >> 0x38
#define SYMBOL_MASK(x) ((uint64_t)(x & 0x00FFFFFFFFFFFFFF))
// v = value, t = taint, b = byte of taint with LSB at 0
#define TAINT_SET(v, t, b)                                                     \
  (v | (((((uint64_t)t) & (0xFF << (b * 8))) >> (b * 8)) << 0x38))

/**
 * Private function for grabbing a symbol from an address
 */
symbolic_val mem_get_symbol(uint64_t addr);

/**
 * Grabs an n bit symbol from shadow memory, starting
 * from the LSB.
 */
symbolic_reg mem_get_symbol_n(uint64_t addr, int n);
symbolic_reg mem_get_symbol8(uint64_t addr);
symbolic_reg mem_get_symbol16(uint64_t addr);
symbolic_reg mem_get_symbol32(uint64_t addr);
symbolic_reg mem_get_symbol64(uint64_t addr);

void reg_set_symbol(uint32_t index, symbolic_reg taint_status);
void mem_set_symbol(uint64_t addr, symbolic_val taint_status);

/**
 * Sets n bytes of shadow memory starting with the LSB.
 * so a single byte set would be N = 1, and would set
 * taint for the LSB. N = 4 is 32 bit, etc.
 */
void mem_set_symbol_n(uint64_t addr, symbolic_reg taint_status, int n);
void mem_set_symbol8(uint64_t addr, symbolic_reg taint_status);
void mem_set_symbol16(uint64_t addr, symbolic_reg taint_status);
void mem_set_symbol32(uint64_t addr, symbolic_reg taint_status);
void mem_set_symbol64(uint64_t addr, symbolic_reg taint_status);

#endif /* SHADOW_MEM_H */
