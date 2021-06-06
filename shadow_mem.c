/*
  shadow_mem.c
  ==============================================
  Keeps a copy of the main process memory, at the
  bit granularity: each byte in shadow memory
  is mapped to a 64 bit value, the upper byte of
  which stores the tainted mask, and the lower
  56 bytes of which store the number of the
  symbolic variable which is referred to by
  that address.

  See .h file for some function descriptions
 */

#include "include/exec/shadow_mem.h"

inline symbolic_val mem_get_symbol(uint64_t addr) {
  symbolic_val ***layer1_entry, **layer2_entry;
  symbolic_val **layer2_tbl;
  symbolic_val *shadow_page;

  layer1_entry = &cur_sc->shadow_seg_tbl[LAYER1_IDX(addr)];
  layer2_tbl = *layer1_entry;
  // if table does not yet exist, assume untainted
  if (layer2_tbl == NULL)
    return 0;

  // lookup shadow page in table 2
  layer2_entry = &layer2_tbl[LAYER2_IDX(addr)];
  shadow_page = *layer2_entry;
  // if page does not yet exist, assume untainted
  if (shadow_page == NULL)
    return 0;
  // return shadow address
  return shadow_page[SHADOW_PAGE_OFFSET(addr)];
}

symbolic_reg mem_get_symbol_n(uint64_t addr, int n) {
  symbolic_val s; // tmp for storing the memory symbol
  symbolic_reg res = {.val = 0, .taint = 0};

  for (int i = 0; i < n; i++) {
    s = mem_get_symbol(addr + i);
    if (s != 0) {
      res.taint |= TAINT_MASK(s) << (i * 8);
      res.val = SYMBOL_MASK(s);
    }
  }

  return res;
}

symbolic_reg mem_get_symbol8(uint64_t addr) {
  return mem_get_symbol_n(addr, 1);
}

symbolic_reg mem_get_symbol16(uint64_t addr) {
  return mem_get_symbol_n(addr, 2);
}

symbolic_reg mem_get_symbol32(uint64_t addr) {
  return mem_get_symbol_n(addr, 4);
}

symbolic_reg mem_get_symbol64(uint64_t addr) {
  return mem_get_symbol_n(addr, 8);
}

inline void reg_set_symbol(uint32_t index, symbolic_reg taint_status) {
  if (index == UINT8_MAX) // constant
    return;
  cur_sc->shadow_regs[index] = taint_status;
}

inline void mem_set_symbol(uint64_t addr, symbolic_val taint_status) {
  symbolic_val ***layer1_entry, **layer2_entry;
  symbolic_val **layer2_tbl;
  symbolic_val *shadow_page;

  layer1_entry = &cur_sc->shadow_seg_tbl[LAYER1_IDX(addr)];
  layer2_tbl = *layer1_entry;
  // early exit
  if (layer2_tbl == NULL && taint_status == 0)
    return;

  // if table does not yet exist, allocate it
  if (layer2_tbl == NULL) {
    layer2_tbl = calloc(NB_SEG_TBL_ENTRIES, 8);
    *layer1_entry = layer2_tbl;
  }

  // lookup shadow page in table 2
  layer2_entry = &layer2_tbl[LAYER2_IDX(addr)];
  shadow_page = *layer2_entry;
  // early exit
  if (shadow_page == NULL && taint_status == 0)
    return;
  // if page does not yet exist, allocate
  if (shadow_page == NULL) {
    shadow_page = calloc(SHADOW_PAGE_SIZE, sizeof(symbolic_val));
    *layer2_entry = shadow_page;
  }
  // return shadow address
  shadow_page[SHADOW_PAGE_OFFSET(addr)] = taint_status;
}

void mem_set_symbol_n(uint64_t addr, symbolic_reg s, int n) {
  symbolic_val b; // tmp for byte we are writing

  for (int i = 0; i < n; i++) {
    b = ((s.taint & (0xFF << (8 * i))) != 0) ? TAINT_SET(s.val, s.taint, i) : 0;
    mem_set_symbol(addr + i, b);
  }
}

void mem_set_symbol8(uint64_t addr, symbolic_reg s) {
  mem_set_symbol_n(addr, s, 1);
}

void mem_set_symbol16(uint64_t addr, symbolic_reg s) {
  mem_set_symbol_n(addr, s, 2);
}

void mem_set_symbol32(uint64_t addr, symbolic_reg s) {
  mem_set_symbol_n(addr, s, 4);
}

void mem_set_symbol64(uint64_t addr, symbolic_reg s) {
  mem_set_symbol_n(addr, s, 8);
}
