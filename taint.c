/**
 * Taint is stored in a shadow memory implemented in shadow_mem.c;
 * inside that memory is a pointer to the CPU State struct
 * that holds the taint of the registers.
 *
 * We index into that memory and during the various tci operations
 * propagate the taint from those addresses to the other registers
 * in the CPU state struct and to temporary registers.
 *
 * (an additional shadow_regs var in the cur_sc for tracking TCG
 * intermediate variables.)
 *
 * NOTE: Emitted new symbols should all increment in value! Otherwise
 * constraint solving can be significantly slowed down (or incorrect).
 */
#include "qemu/osdep.h"
#include "qemu-common.h"
#include "exec/taint.h"
#include "tcg/tcg.h"

#define REG_CHECK(r) assert((r == UINT8_MAX) || (r < MAX_NB_TCG_REGS))
#define DECISION_CHECK(d) assert((d == 0) || (d == 1));

inline static uint64_t tci_read_reg(const uint64_t *regs, uint64_t index)
{
    return regs[index];
}

inline static uint32_t tci_read_reg32(const uint64_t *regs, uint64_t index)
{
    return (uint32_t)tci_read_reg(regs, index);
}

inline static uint32_t tci_read_i32(uint8_t **tb_ptr)
{
    uint32_t value = *(uint32_t *)(*tb_ptr);
    *tb_ptr += sizeof(value);
    return value;
}

inline static uint64_t tci_read_i64(uint8_t **tb_ptr)
{
    uint64_t value = *(uint64_t *)(*tb_ptr);
    *tb_ptr += sizeof(value);
    return value;
}

inline static uint64_t tci_read_reg64(const uint64_t *regs, uint64_t index)
{
    return tci_read_reg(regs, index);
}

inline static uint64_t extract_r64(const uint64_t *regs, uint8_t **tb_ptr)
{
    uint64_t value = tci_read_reg64(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

inline static uint64_t extract_ri64(const uint64_t *regs, uint8_t **tb_ptr)
{
    uint64_t value;
    uint64_t r = **tb_ptr;
    *tb_ptr += 1;
    if (r == UINT8_MAX) {
        value = tci_read_i64(tb_ptr);
    } else {
        value = tci_read_reg64(regs, r);
    }
    return value;
}




inline static uint64_t tci_read_i64_static(uint8_t *tb_ptr)
{
    uint64_t value = *(uint64_t *)(tb_ptr);
    return value;
}

inline static uint64_t extract_ri64_static(const uint64_t *regs, uint8_t *tb_ptr)
{
    uint64_t value;
    uint64_t r = *tb_ptr;
    tb_ptr += 1;
    if (r == UINT8_MAX) {
        value = tci_read_i64_static(tb_ptr);
    } else {
        value = tci_read_reg64(regs, r);
    }
    return value;
}

inline static uint32_t tci_read_i32_static(uint8_t *tb_ptr)
{
    uint32_t value = *(uint32_t *)(tb_ptr);
    return value;
}

inline static uint32_t extract_ri32_static(const uint64_t *regs, uint8_t *tb_ptr)
{
    uint32_t value;
    uint64_t r = *tb_ptr;
    tb_ptr += 1;
    if (r == UINT8_MAX) {
        value = tci_read_i32_static(tb_ptr);
    } else {
        value = tci_read_reg32(regs, r);
    }
    return value;
}





inline static uint32_t extract_ri32(const uint64_t *regs, uint8_t **tb_ptr)
{
    uint32_t value;
    uint64_t r = **tb_ptr;
    *tb_ptr += 1;
    if (r == UINT8_MAX) {
        value = tci_read_i32(tb_ptr);
    } else {
        value = tci_read_reg32(regs, r);
    }
    return value;
}

inline static uint32_t extract_r32(const uint64_t *regs, uint8_t **tb_ptr)
{
    uint32_t value = tci_read_reg32(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

inline symbolic_reg taint_ri32(uint8_t **tb_ptr)
{
    uint8_t index = **tb_ptr;
    *tb_ptr += 1;
    if(index == UINT8_MAX)//constant
    {
        *tb_ptr += 4;
        symbolic_reg s = { .val = 0, .taint = 0};
        return s;
    }
    return cur_sc->shadow_regs[index];
}

inline symbolic_reg taint_ri64(uint8_t **tb_ptr)
{
    uint8_t index = **tb_ptr;
    *tb_ptr += 1;
    if(index == UINT8_MAX)//constant
    {
        *tb_ptr += 8;
        symbolic_reg s = { .val = 0, .taint = 0};
        return s;
    }
    return cur_sc->shadow_regs[index];
}

inline symbolic_reg taint_r(uint8_t **tb_ptr)
{
    uint8_t index = **tb_ptr;
    *tb_ptr += 1;
    return  cur_sc->shadow_regs[index];
}

inline symbolic_reg taint_s32(uint8_t **tb_ptr)
{
    uint8_t index = **tb_ptr;
    *tb_ptr += 1;
    if(index == UINT8_MAX)//constant
    {
        *tb_ptr += 4;
        symbolic_reg s = { .val = 0, .taint = 0};
        return s;
    }
    return  cur_sc->shadow_regs[index];
}


inline void untaint_reg(uint8_t dst_index)
{
  symbolic_reg untainted = { .val = 0, .taint = 0};
  reg_set_symbol(dst_index, untainted);
}

inline static symbolic_reg untainted_reg(void)
{
  symbolic_reg untainted = { .val = 0, .taint = 0};
  return untainted;
}

static inline symbolic_reg maybe_prepare_constraint_binop(symbolic_reg s0,
                                                          symbolic_reg s1,
                                                          uint8_t dst_index,
                                                          taint_val taint) {
  if (taint) {
    symbolic_reg new_reg = {.val = fresh_symbol(), .taint = taint};
    cur_sc->dst = new_reg;
    reg_set_symbol(dst_index, new_reg);
    cur_sc->arg0 = s0;
    cur_sc->arg1 = s1;
    return new_reg;
  } else {
    symbolic_reg new_reg = {.val = 0, .taint = 0};
    reg_set_symbol(dst_index, new_reg);
    return new_reg;
  }
}

static inline symbolic_reg maybe_prepare_constraint_unop(symbolic_reg s,
                                                         uint8_t dst_index,
                                                         taint_val taint) {
  if ((taint != 0)) {
    symbolic_reg new_reg = {.val = fresh_symbol(), .taint = taint};
    cur_sc->dst = new_reg;
    reg_set_symbol(dst_index, new_reg);
    cur_sc->arg0 = s;
    return new_reg;
  } else {
    symbolic_reg new_reg = {.val = 0, .taint = 0};
    reg_set_symbol(dst_index, new_reg);
    return new_reg;
  }
}

// c0 = tmp16
// c1 = tmp32
inline symbolic_reg taint_deposit32(uint8_t *tb_ptr)
{
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_r(&tb_ptr);

    uint16_t tmp16 = *tb_ptr++;
    uint8_t tmp8 = *tb_ptr++;
    uint32_t tmp32 = (((1 << tmp8) - 1) << tmp16);

    uint32_t masked_v0_taint = s0.taint & ~tmp32;
    uint32_t masked_v1_taint = (s1.taint << tmp16) & tmp32;
    uint32_t taint = masked_v0_taint | masked_v1_taint;

    if (taint != 0)
    {
        //cur_sc->dst = fresh_symbol();
        symbolic_reg new_reg = { .val = fresh_symbol(), .taint = taint};
        cur_sc->dst = new_reg;
        reg_set_symbol(dst_index, new_reg);

        cur_sc->arg0 = (masked_v0_taint != 0) ? s0 : untainted_reg();
        cur_sc->arg1 = (masked_v1_taint != 0) ? s1 : untainted_reg();
        return new_reg;
    }
    else
    {
        symbolic_reg new_reg = { .val = 0, .taint = 0};
        reg_set_symbol(dst_index, new_reg);
        return new_reg;
    }
}

// c0 = tmp16
// c1 = tmp64
inline symbolic_reg taint_deposit64(uint8_t *tb_ptr)
{
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_r(&tb_ptr);

    uint16_t tmp16 = *tb_ptr++;
    uint8_t tmp8 = *tb_ptr++;
    uint64_t tmp64 = (((1ULL << tmp8) - 1) << tmp16);

    uint64_t masked_v0_taint = s0.taint & ~tmp64;
    uint64_t masked_v1_taint = (s1.taint << tmp16) & tmp64;
    uint64_t taint = masked_v0_taint | masked_v1_taint;

    if ( taint != 0 )
    {
        //cur_sc->dst = fresh_symbol();
        symbolic_reg new_reg = { .val = fresh_symbol(), .taint = taint};
        cur_sc->dst = new_reg;
        reg_set_symbol(dst_index, new_reg);

        cur_sc->arg0 = (masked_v0_taint != 0) ? s0 : untainted_reg();
        cur_sc->arg1 = (masked_v1_taint != 0) ? s1 : untainted_reg();
        return new_reg;
    }
    else
    {
        symbolic_reg new_reg = { .val = 0, .taint = 0};
        reg_set_symbol(dst_index, new_reg);
        return new_reg;
    }
}



static inline taint_val taint_binop(uint8_t opc, taint_val t0, taint_val t1)
{
    switch (opc) {
        case TCG_ADD32:
            return (t0 | t1) & MASK32;
            break;
        case TCG_SUB32:
            return (t0 | t1) & MASK32;
            break;
        case TCG_MUL32:
            return MASK32;
            break;
        case TCG_DIV32:
            return MASK32;
            break;
        case TCG_DIVU32:
            return MASK32;
            break;
        case TCG_REM32:
            return MASK32;
            break;
        case TCG_REMU32:
            return MASK32;
            break;
        case TCG_AND32:
            return (t0 | t1) & MASK32;
            break;
        case TCG_OR32:
            return (t0 | t1) & MASK32;
            break;
        case TCG_XOR32:
            return (t0 | t1) & MASK32;
            break;
        case TCG_ADD64:
            return (t0 | t1);
            break;
        case TCG_SUB64:
            return (t0 | t1);
            break;
        case TCG_MUL64:
            return MASK32;
            break;
        case TCG_AND64:
            return (t0 | t1);
            break;
        case TCG_OR64:
            return (t0 | t1);
            break;
        case TCG_XOR64:
            return (t0 | t1);
            break;
        default:
            assert(false);
        }
}


static inline taint_val taint_shift_rot(uint8_t opc, taint_val t, uint32_t c)
{
    switch (opc) {
        case TCG_SHL32:
            return (t << c) & MASK32;
        case TCG_SHR32:
            return (t >> c) & MASK32;
        case TCG_SAR32:
            return (t >> c) & MASK32;
        case TCG_ROTL32:
            return ((t << c) | (t >> ((32 - c) & 31))) & MASK32;
        case TCG_ROTR32:
            return ((t >> c) | (t << ((32 - c) & 31))) & MASK32;
        case TCG_SHL64:
            return (t << c);
        case TCG_SHR64:
            return (t >> c);
        case TCG_SAR64:
            return (t >> c);
        case TCG_ROTL64:
            return (t << c) | (t >> ((64 - c) & 63));
        case TCG_ROTR64:
            return (t >> c) | (t << ((64 - c) & 63));
        default:
            assert(false);
        }
}

static inline taint_val taint_unop(uint8_t opc, taint_val t)
{
    switch (opc) {
        case TCG_MOV32:
            return (t & MASK32);
        case TCG_EXT8S_32:
          return (t & MASK8) | ((int32_t) (uint8_t) (t & 0x080));
        case TCG_EXT16S_32:
          return (t & MASK16) | ((int32_t) (uint16_t) (t & 0x08000));
        case TCG_EXT8U_32:
            return t & MASK8;
        case TCG_EXT16U_32:
            return t & MASK16;
        case TCG_BSWAP16_32:
            return (((t & 0x00ff) << 8) | ((t & 0xff00) >> 8)) & MASK32;
        case TCG_BSWAP32_32:
            return (((t & 0x000000ffU) << 24)
               | ((t & 0x0000ff00U) <<  8)
               | ((t & 0x00ff0000U) >>  8)
               | ((t & 0xff000000U) >> 24)) & MASK32;
        case TCG_NOT32:
            return t & MASK32;
        case TCG_NEG32:
            return t & MASK32;
        case TCG_MOV64:
            return t;
        case TCG_EXT8S_64:
            return (t & MASK8) | ((int64_t) (uint8_t) (t & 0x080));
        case TCG_EXT16S_64:
            return (t & MASK16) | ((int64_t) (uint16_t) (t & 0x08000));
        case TCG_EXT32S_64:
            return (t & MASK32) | ((int64_t) (uint32_t) (t & 0x080000000));
        case TCG_EXT8U_64:
            return t & MASK8;
        case TCG_EXT16U_64:
            return t & MASK16;
        case TCG_EXT32U_64:
            return t & MASK32;
        case TCG_BSWAP16_64:
            return (((t & 0x00ff) << 8) | ((t & 0xff00) >> 8));
        case TCG_BSWAP32_64:
            return (((t & 0x000000ffU) << 24)
               | ((t & 0x0000ff00U) <<  8)
               | ((t & 0x00ff0000U) >>  8)
               | ((t & 0xff000000U) >> 24));
        case TCG_BSWAP64_64:
            return (((t & 0x00000000000000ffULL) << 56) |
                   ((t & 0x000000000000ff00ULL) << 40) |
                   ((t & 0x0000000000ff0000ULL) << 24) |
                   ((t & 0x00000000ff000000ULL) <<  8) |
                   ((t & 0x000000ff00000000ULL) >>  8) |
                   ((t & 0x0000ff0000000000ULL) >> 24) |
                   ((t & 0x00ff000000000000ULL) >> 40) |
                   ((t & 0xff00000000000000ULL) >> 56));
         case TCG_NOT64:
            return t;
        case TCG_NEG64:
            return t;
        default:
            assert(false);
        }
}


inline symbolic_reg taint_setcond32(uint8_t *tb_ptr)
{
    taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_ri32(&tb_ptr);
    if ( s0.taint || s1.taint )
        taint = 1;
    else
        taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}


inline symbolic_reg taint_setcond64(uint8_t *tb_ptr)
{
    taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_ri64(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = 1;
    else
        taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}

inline symbolic_reg taint_binopr_r(uint8_t opc, uint8_t *tb_ptr)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_r(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = taint_binop(opc, s0.taint, s1.taint);
    else
      taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}

inline symbolic_reg taint_binop32(uint8_t opc, uint8_t *tb_ptr)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_ri32(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = taint_binop(opc, s0.taint, s1.taint);
    else
      taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}

inline symbolic_reg taint_binop32_32(uint8_t opc, uint8_t *tb_ptr)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_ri32(&tb_ptr);
    symbolic_reg s1 = taint_ri32(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = taint_binop(opc, s0.taint, s1.taint);
    else
      taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}


inline symbolic_reg taint_shift_rot32(uint8_t opc, uint8_t *tb_ptr, const uint64_t *regs)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_ri32(&tb_ptr);
    uint64_t c = extract_ri32_static(regs, tb_ptr);
    symbolic_reg s1 = taint_ri32(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) ) {
      taint = (s1.taint != 0) ? MASK32 : taint_shift_rot(opc, s0.taint, c);
    }
    else {
      taint = 0;
    }
    return maybe_prepare_constraint_binop(s0,s1,dst_index,taint);
}


inline symbolic_reg taint_binop64(uint8_t opc, uint8_t *tb_ptr)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_ri64(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = taint_binop(opc, s0.taint, s1.taint);
    else
      taint = 0;
    return maybe_prepare_constraint_binop(s0,s1,dst_index,taint);
}


inline symbolic_reg taint_binop64_64(uint8_t opc, uint8_t *tb_ptr)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_ri64(&tb_ptr);
    symbolic_reg s1 = taint_ri64(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = taint_binop(opc, s0.taint, s1.taint);
    else
      taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}


inline symbolic_reg taint_shift_rot64(uint8_t opc, uint8_t *tb_ptr, const uint64_t *regs)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s0 = taint_ri64(&tb_ptr);
    uint64_t c = extract_ri64_static(regs, tb_ptr);
    symbolic_reg s1 = taint_ri64(&tb_ptr);
    if ( (s0.taint != 0) || (s1.taint != 0) )
        taint = (s1.taint != 0) ? MASK64 : taint_shift_rot(opc, s0.taint, c);
    else
      taint = 0;
    return maybe_prepare_constraint_binop(s0, s1, dst_index, taint);
}

inline symbolic_reg taint_unop32(uint8_t opc, uint8_t *tb_ptr)
{
    taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s = taint_r(&tb_ptr);
    taint = taint_unop(opc, s.taint);
    return maybe_prepare_constraint_unop(s, dst_index, taint);
}

inline symbolic_reg taint_unop64(uint8_t opc, uint8_t *tb_ptr)
{
  taint_val taint;
    uint8_t dst_index = *tb_ptr++;
    symbolic_reg s = taint_r(&tb_ptr);
    taint = taint_unop(opc, s.taint);
    return maybe_prepare_constraint_unop(s, dst_index, taint);
}

inline void taint_ld8_i32(uint8_t dst_index, uint64_t addr)
{
    symbolic_reg mem_symbol = (cur_sc->pending_mmio_read.taint == 0) ? mem_get_symbol8(addr) : cur_sc->pending_mmio_read;
    reg_set_symbol(dst_index, mem_symbol);
    symbolic_reg s = {.val = 0, .taint = 0};
    cur_sc->pending_mmio_read = s;
}

inline void taint_ld16_i32(uint8_t dst_index, uint64_t addr)
{
    symbolic_reg mem_symbol = (cur_sc->pending_mmio_read.taint == 0) ? mem_get_symbol16(addr) : cur_sc->pending_mmio_read;
    reg_set_symbol(dst_index, mem_symbol);
    symbolic_reg s = {.val = 0, .taint = 0};
    cur_sc->pending_mmio_read = s;
}

inline void taint_ld_i32(uint8_t dst_index, uint64_t addr)
{
    symbolic_reg mem_symbol = (cur_sc->pending_mmio_read.taint == 0) ? mem_get_symbol32(addr) : cur_sc->pending_mmio_read;
    reg_set_symbol(dst_index, mem_symbol);
    symbolic_reg s = {.val = 0, .taint = 0};
    cur_sc->pending_mmio_read = s;
}

inline void taint_ld_i64(uint8_t dst_index, uint64_t addr)
{
    symbolic_reg mem_symbol = (cur_sc->pending_mmio_read.taint == 0) ? mem_get_symbol64(addr) : cur_sc->pending_mmio_read;
    reg_set_symbol(dst_index, mem_symbol);
    symbolic_reg s = {.val = 0, .taint = 0};
    cur_sc->pending_mmio_read = s;
}

inline void taint_st8_i32(uint8_t src_index, uint64_t addr)
{
    symbolic_reg reg_symbol = cur_sc->shadow_regs[src_index];
    mem_set_symbol8(addr, reg_symbol);
}

inline void taint_st16_i32(uint8_t src_index, uint64_t addr)
{
    symbolic_reg reg_symbol = cur_sc->shadow_regs[src_index];
    mem_set_symbol16(addr, reg_symbol);
}

inline void taint_st_i32(uint8_t src_index, uint64_t addr)
{
    symbolic_reg reg_symbol = cur_sc->shadow_regs[src_index];
    mem_set_symbol32(addr, reg_symbol);
}

inline void taint_st_i64(uint8_t src_index, uint64_t addr)
{
    symbolic_reg reg_symbol = cur_sc->shadow_regs[src_index];
    mem_set_symbol64(addr, reg_symbol);
}

uint64_t* decision_finalized(uint64_t pc)
{
  finalized_decision prev_decision;
  for(int idx = 0; idx < cur_sc->fdec_idx; idx++)
  {
        prev_decision = cur_sc->finalized_decisions[idx];
        if (prev_decision.pc == pc)
        {
          return &(cur_sc->finalized_decisions[idx].val);
        }
  }

  return NULL;
}

decision_choice taint_brcond32(const uint64_t *regs, uint8_t *tb_ptr)
{
    uint64_t a0 = (uint64_t)tb_ptr;
    uint8_t *tb_ptr_alias = tb_ptr;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_ri32(&tb_ptr);
    uint32_t v0 = extract_r32(regs, &tb_ptr_alias);
    uint32_t v1 = extract_ri32(regs, &tb_ptr_alias);
    uint8_t cond = *tb_ptr_alias++;
    uint64_t a1 = *(uint64_t *)(tb_ptr);
    tb_ptr += 8;

    if( (s0.taint != 0) || (s1.taint != 0) ){
        uint64_t* maybe_val = decision_finalized(sc_get_pc());
        if (maybe_val != NULL)
        {
          uint64_t dv = *maybe_val;
          *maybe_val = (dv == 0) ? 1 : 0;
          return dv;
        }
        cur_sc->arg0 = s0;
        cur_sc->arg1 = s1;
        return get_decision(v0, v1, cond, a0, a1);
    } else {
      return UNTAINTED_DECISION;
    }
}

decision_choice taint_brcond64(const uint64_t *regs, uint8_t *tb_ptr)
{
    uint64_t a0 = (uint64_t)tb_ptr;
    uint8_t *tb_ptr_alias = tb_ptr;
    symbolic_reg s0 = taint_r(&tb_ptr);
    symbolic_reg s1 = taint_ri64(&tb_ptr);
    uint64_t v0 = extract_r64(regs, &tb_ptr_alias);
    uint64_t v1 = extract_ri64(regs, &tb_ptr_alias);
    uint8_t cond = *tb_ptr_alias++;
    uint64_t a1 = *(uint64_t *)(tb_ptr);
    tb_ptr += 8;

    if( (s0.taint != 0) || (s1.taint != 0) ){
      uint64_t* maybe_val = decision_finalized(sc_get_pc());
      if (maybe_val != NULL)
      {
         uint64_t dv = *maybe_val;
         *maybe_val = (dv == 0) ? 1 : 0;
         return dv;
      }

      cur_sc->arg0 = s0;
      cur_sc->arg1 = s1;
      return get_decision(v0, v1, cond, a0, a1);
    }
    else
        return UNTAINTED_DECISION;
}

/**
 * Helper for tainting ccr; conditionally sign extends
 * depending on the particular condition code operation,
 * and emits the correct unary operation.
 */
symbolic_reg extsign_taint(int op, symbolic_reg res, symbolic_reg src,
                                  uint32_t index) {
  // New symbolic variable which will be sign extended
  symbolic_reg dst = {.val = fresh_symbol(), .taint = res.taint | src.taint};
  emit_binop_symbolic(op, dst, res, src);

  if (index == 0 || index == 1) {
    // New symbol needed to satisfy claripy's need for equal length BVs
    symbolic_reg upcast_dst = {.val = fresh_symbol(), .taint = 0x0ffffffff};
    op = (index == 0) ? UNOP_EXT8S_I32 : UNOP_EXT16S_I32;
    emit_unop_symbolic(op, upcast_dst, dst);
    return upcast_dst;
  }

  return dst;
}

#ifdef M68K_CPU_H
/**
 * NOTE: May need to propagate taint from what ccr is set from
 *
 * @param state_ptr CPUM68KState to clear ccr taint for
 */
void taint_set_ccr_m68k(void *state_ptr) {
  CPUM68KState *cpu_addr = state_ptr;
  symbolic_reg taint_cc_x = {.val = cpu_addr->cc_x, .taint = 0};
  symbolic_reg taint_cc_n = {.val = cpu_addr->cc_n, .taint = 0};
  symbolic_reg taint_cc_z = {.val = cpu_addr->cc_z, .taint = 0};
  symbolic_reg taint_cc_v = {.val = cpu_addr->cc_v, .taint = 0};
  symbolic_reg taint_cc_c = {.val = cpu_addr->cc_c, .taint = 0};

  mem_set_symbol32((uint64_t) & (cpu_addr->cc_x), taint_cc_x);
  mem_set_symbol32((uint64_t) & (cpu_addr->cc_n), taint_cc_n);
  mem_set_symbol32((uint64_t) & (cpu_addr->cc_z), taint_cc_z);
  mem_set_symbol32((uint64_t) & (cpu_addr->cc_v), taint_cc_v);
  mem_set_symbol32((uint64_t) & (cpu_addr->cc_c), taint_cc_c);
}

/**
 * During M68K execution (and others), a ccall is made to compute
 * ccr.
 *
 * We need to propagate taint across cc_x, cc_n, ... registers
 * from the cc_op register that defines the comparison to do.
 *
 * In this function, we propagate the taint for this operation
 * so that later branch conditions that operate upon condition
 * code registers know to emit some instruction to angr for
 * getting a decision about the branch.
 */
void taint_ccr_m68k(void * state_ptr, uint32_t cc_op) {
  CPUM68KState * cpu_addr = state_ptr;
  // Temporary operators for computing CCR
  symbolic_reg res, src1, src2;

  // We get the current taint status of the other registers
  symbolic_reg taint_cc_x = mem_get_symbol32((uint64_t) &(cpu_addr->cc_x));
  symbolic_reg taint_cc_n = mem_get_symbol32((uint64_t) &(cpu_addr->cc_n));
  symbolic_reg taint_cc_z = mem_get_symbol32((uint64_t) &(cpu_addr->cc_z));
  symbolic_reg taint_cc_v = mem_get_symbol32((uint64_t) &(cpu_addr->cc_v));
  symbolic_reg taint_cc_c = mem_get_symbol32((uint64_t) &(cpu_addr->cc_c));

  // Compute CCOP taint tracking, ripped from helper.c and
  // adapted
  switch (cc_op) {
  case CC_OP_FLAGS:
    /* Everything is in its right place.  */
    break;
  case CC_OP_ADDB:
  case CC_OP_ADDW:
  case CC_OP_ADDL:
    if (!taint_cc_n.taint)
      taint_cc_n.val = cpu_addr->cc_n;
    if (!taint_cc_v.taint)
      taint_cc_v.val = cpu_addr->cc_v;
    taint_cc_c = taint_cc_x;
    taint_cc_z = taint_cc_n;
    res = taint_cc_n;
    src2 = taint_cc_v;
    if (res.taint || src2.taint) {
      // src1 = EXTSIGN(res - src2, op - CC_OP_ADDB);
      src1 = extsign_taint(BINOP_SUB_I32, res, src2, cc_op - CC_OP_ADDB);
      // v = (res ^ src1) & ~(src1 ^ src2);
      symbolic_reg tmp = (symbolic_reg){.val = fresh_symbol(),
                                        .taint = res.taint | src1.taint};
      emit_binop_symbolic(BINOP_XOR_I32, tmp, res, src1);
      symbolic_reg tmp2 = (symbolic_reg){.val = fresh_symbol(),
                                        .taint = src1.taint | src2.taint};
      emit_binop_symbolic(BINOP_XOR_I32, tmp2, src1, src2);
      symbolic_reg tmp3 = (symbolic_reg){.val = fresh_symbol(),
                                         .taint = src1.taint};
      emit_unop_symbolic(UNOP_NOT_I32, tmp3, src1);
      taint_cc_v = (symbolic_reg){.val = fresh_symbol(),
                                  .taint = tmp.taint | tmp3.taint};
      emit_binop_symbolic(BINOP_AND_I32, taint_cc_v, tmp, tmp3);
    } else {
      /*
        cc_v is overwritten. Technically the val inside of the tainted symbol is
        overwritten. NOTE This shoud be fine to ignore since we assume
        everywhere the val is used for computations without taint it is reset
        based upon the concrete values. The same applies for the other cases
      */
      taint_cc_v.taint = 0;
    }
    break;
  case CC_OP_SUBB:
  case CC_OP_SUBW:
  case CC_OP_SUBL:
    if (!taint_cc_n.taint)
      taint_cc_n.val = cpu_addr->cc_n;
    if (!taint_cc_v.taint)
      taint_cc_v.val = cpu_addr->cc_v;
    res = taint_cc_n;
    src2 = taint_cc_v;
    taint_cc_c = taint_cc_x;
    taint_cc_z = taint_cc_n;
    if (res.taint || src2.taint) {
      src1 = extsign_taint(BINOP_ADD_I32, res, src2, cc_op - CC_OP_SUBB);
      // v = (res ^ src1) & (src1 ^ src2);
      symbolic_reg tmp = (symbolic_reg){.val = fresh_symbol(),
                                        .taint = res.taint | src1.taint};
      emit_binop_symbolic(BINOP_XOR_I32, tmp, res, src1);
      symbolic_reg tmp2 = (symbolic_reg){.val = fresh_symbol(),
                                        .taint = src1.taint | src2.taint};
      emit_binop_symbolic(BINOP_XOR_I32, tmp2, src1, src2);
      taint_cc_v = (symbolic_reg){.val = fresh_symbol(),
                                  .taint = tmp.taint | tmp2.taint};
      emit_binop_symbolic(BINOP_AND_I32, taint_cc_v, tmp, tmp2);
    } else {
      taint_cc_v.taint = 0;
    }
    break;
  case CC_OP_CMPB:
  case CC_OP_CMPW:
  case CC_OP_CMPL:
    if (!taint_cc_n.taint)
      taint_cc_n.val = cpu_addr->cc_n;
    if (!taint_cc_v.taint)
      taint_cc_v.val = cpu_addr->cc_v;
    src1 = taint_cc_n;
    src2 = taint_cc_v;
    if (src1.taint || src2.taint) {
      res = extsign_taint(BINOP_SUB_I32, src1, src2, cc_op - CC_OP_CMPB);
      taint_cc_n = res;
      taint_cc_z = res;
      // c = src1 < src2;
      taint_cc_c = (symbolic_reg){.val = fresh_symbol(),
                                  .taint = src1.taint | src2.taint};
      emit_setcond_symbolic(taint_cc_c, src1, src2, TCG_COND_LT);
      // v = (res ^ src1) & (src1 ^ src2);
      symbolic_reg tmp = (symbolic_reg){.val = fresh_symbol(),
                                         .taint = res.taint | src1.taint};
      emit_binop_symbolic(BINOP_XOR_I32, tmp, res, src1);
      symbolic_reg tmp2 = (symbolic_reg){.val = fresh_symbol(),
                                        .taint = src1.taint | src2.taint};
      emit_binop_symbolic(BINOP_XOR_I32, tmp2, src1, src2);
      taint_cc_v = (symbolic_reg){.val = fresh_symbol(),
                                  .taint = res.taint | tmp.taint | tmp2.taint};
      emit_binop_symbolic(BINOP_AND_I32, taint_cc_v, tmp, tmp2);
    } else {
      taint_cc_z.taint = 0;
      taint_cc_c.taint = 0;
    }
    break;
  case CC_OP_LOGIC:
    taint_cc_c = (symbolic_reg){.val = 0, .taint = 0};
    taint_cc_v = (symbolic_reg){.val = 0, .taint = 0};
    taint_cc_z = taint_cc_n;
    break;
  default:
    break;
  }

  mem_set_symbol32((uint64_t) &(cpu_addr->cc_x), taint_cc_x);
  mem_set_symbol32((uint64_t) &(cpu_addr->cc_n), taint_cc_n);
  mem_set_symbol32((uint64_t) &(cpu_addr->cc_z), taint_cc_z);
  mem_set_symbol32((uint64_t) &(cpu_addr->cc_v), taint_cc_v);
  mem_set_symbol32((uint64_t) &(cpu_addr->cc_c), taint_cc_c);
}

#endif

static void taint_ccall_x86(uint8_t *tb_ptr, const uint64_t *regs,
                            uint8_t dst_index, uint8_t src_index0,
                            uint8_t src_index1, uint8_t src_index2,
                            uint8_t src_index3, uint8_t src_index5,
                            uint8_t src_index6) {
  taint_val taint;

  symbolic_reg s0 = cur_sc->shadow_regs[src_index0]; // dst
  symbolic_reg s1 = cur_sc->shadow_regs[src_index1]; // src1
  symbolic_reg s2 = cur_sc->shadow_regs[src_index2]; // src2
  symbolic_reg s3 = cur_sc->shadow_regs[src_index3]; // op

  uint64_t v0 = tci_read_reg(regs, src_index0);
  uint64_t v1 = tci_read_reg(regs, src_index1);
  uint64_t v2 = tci_read_reg(regs, src_index2);
  uint64_t v3 = tci_read_reg(regs, src_index3);

  uint64_t arg0 = (s0.taint != 0) ? s0.val : v0;
  uint64_t arg1 = (s1.taint != 0) ? s1.val : v1;
  uint64_t arg2 = (s2.taint != 0) ? s2.val : v2;
  uint64_t arg3 = (s3.taint != 0) ? s3.val : v3;

  if ((s0.taint != 0)) {
    taint = 0x40;
    symbolic_reg new_reg = {.val = fresh_symbol(), .taint = taint};
    reg_set_symbol(dst_index, new_reg);
    qapi_event_send_symbolic_ccall(sc_get_pc(), new_reg.taint, s0.taint,
                                   s1.taint, s2.taint, s3.taint, new_reg.val,
                                   arg0, arg1, arg2, arg3);
  } else {
    untaint_reg(dst_index);
  }
}

void taint_ccall(uint8_t *tb_ptr,
               const uint64_t *regs,
               uint8_t dst_index,
               uint8_t src_index0,
               uint8_t src_index1,
               uint8_t src_index2,
               uint8_t src_index3,
               uint8_t src_index5,
               uint8_t src_index6)
{
  if (cur_sc->archname == ARCHNAME_X86) {
    taint_ccall_x86(tb_ptr, regs, dst_index, src_index0, src_index1, src_index2,
                    src_index3, src_index5, src_index6);
  }
}

// taints the eax register
void taint_ioport_read(uint64_t addr, uint64_t size)
{
    symbolic_val v = fresh_symbol();
    symbolic_reg new_reg = fresh_symbolic_reg(v,size);
    cur_sc->shadow_regs[0] = new_reg; //shadow reg eax
    uint64_t pc = sc_get_pc();
    cur_sc->taint_ctr = 10;
    qapi_event_send_ioport_read( addr, v, pc );
}

void taint_ioport_write(uint64_t addr, uint64_t val)
{
    uint64_t pc = sc_get_pc();
    qapi_event_send_ioport_write(addr, val, pc);
    printf("\%c" ,(char)val);
    fflush(stdout);

}

inline symbolic_reg fresh_symbolic_reg(symbolic_val v, uint64_t size)
{
    if(size == 4){ symbolic_reg s = {.val = v, .taint = 0x0ffffffff}; return s;}
    else if (size == 1) {symbolic_reg s =  {.val = v, .taint = 0x000000ff}; return s;}
    else if (size == 2) {symbolic_reg s = {.val = v, .taint = 0x0000ffff}; return s;}
    else if (size == 8) {symbolic_reg s = {.val = v, .taint = 0xffffffffffffffff}; return s;}
    else{
        printf("size = %lu\n", size);
        assert(false);
    }
}



uint64_t* io_finalized(uint64_t addr)
{
  finalized_io prev_io;
  for(int idx = 0; idx < cur_sc->fio_idx; idx++)
  {
        prev_io = cur_sc->finalized_io[idx];
        if (prev_io.addr == addr)
        {
          return &(cur_sc->finalized_io[idx].val);
        }
  }
  return NULL;
}

uint64_t taint_mmio_read(uint64_t addr, uint64_t size) {
  uint64_t pc = sc_get_pc();

  uint64_t *maybe_val = io_finalized(addr);
  if (maybe_val != NULL)
    return *maybe_val;

  symbolic_val v = fresh_symbol();
  symbolic_reg new_reg = fresh_symbolic_reg(v, size);
  cur_sc->pending_mmio_read = new_reg;
  qapi_event_send_mmio_read(addr, v, size, pc);
  cur_sc->taint_ctr = 10;
  return 0xffffffffffffffff;
}

void taint_mmio_write(uint64_t addr, uint64_t val)
{
    uint64_t pc = sc_get_pc();
    qapi_event_send_mmio_write(addr, val, pc);
    printf("\%c" ,(char)val);
    fflush(stdout);
}

void taint_intc_read(uint64_t addr, uint64_t val_returned)
{
    uint64_t pc = sc_get_pc();
    qapi_event_send_intc_read(addr, val_returned, pc);
}

void emit_unop_symbolic(uint8_t opc, symbolic_reg dst, symbolic_reg src) {
  uint64_t pc = sc_get_pc();
  qapi_event_send_symbolic_unop(opc, src.taint, src.val, dst.val, dst.taint,
                                pc);
}

void emit_unop(uint8_t opc, uint64_t v) {
  taint_val taint = cur_sc->arg0.taint;
  uint64_t val = (taint != 0) ? cur_sc->arg0.val : v;
  uint64_t pc = sc_get_pc();
  qapi_event_send_symbolic_unop(opc, taint, val, cur_sc->dst.val,
                                cur_sc->dst.taint, pc);
}

/**
 * Emits a symbolic binary operation. NOTE: If the symbolic registers
 * given do not have taint, their values are expected to be equivalent
 * to the concrete value of the register.
 */
void emit_binop_symbolic(uint8_t opc, symbolic_reg dst, symbolic_reg left,
                symbolic_reg right) {
  uint64_t pc = sc_get_pc();
  qapi_event_send_symbolic_binop(opc, left.taint, right.taint, left.val,
                                 right.val, dst.val, dst.taint, pc);
}

void emit_binop(uint8_t opc, uint64_t v0, uint64_t v1) {
  taint_val taint0 = cur_sc->arg0.taint;
  taint_val taint1 = cur_sc->arg1.taint;
  uint64_t val0 = (taint0 != 0) ? cur_sc->arg0.val : v0;
  uint64_t val1 = (taint1 != 0) ? cur_sc->arg1.val : v1;
  uint64_t pc = sc_get_pc();
  qapi_event_send_symbolic_binop(opc, taint0, taint1, val0, val1,
                                 cur_sc->dst.val, cur_sc->dst.taint, pc);
}

void emit_deposit(uint64_t v0, uint64_t v1, uint64_t c0, uint64_t c1)
{
    taint_val taint0 = cur_sc->arg0.taint;
    taint_val taint1 = cur_sc->arg1.taint;
    uint64_t val0 = (taint0 != 0) ? cur_sc->arg0.val : v0;
    uint64_t val1 = (taint1 != 0) ? cur_sc->arg1.val : v1;
    uint64_t pc = sc_get_pc();
    qapi_event_send_symbolic_deposit(taint0, taint1, val0, val1, cur_sc->dst.val, cur_sc->dst.taint, c0, c1, pc);
}

void emit_setcond_symbolic(symbolic_reg dst, symbolic_reg left, symbolic_reg right,
                  uint8_t condition) {
  uint64_t pc = sc_get_pc();
  qapi_event_send_symbolic_setcond(left.taint, right.taint, left.val, right.val,
                                   dst.val, dst.taint, condition, pc);
}

void emit_setcond(uint64_t v0, uint64_t v1, uint8_t condition)
{
    taint_val taint0 = cur_sc->arg0.taint;
    taint_val taint1 = cur_sc->arg1.taint;
    uint64_t val0 = (taint0) ? cur_sc->arg0.val : v0;
    uint64_t val1 = (taint1) ? cur_sc->arg1.val : v1;
    uint64_t pc = sc_get_pc();
    qapi_event_send_symbolic_setcond(taint0, taint1, val0, val1, cur_sc->dst.val, cur_sc->dst.taint, condition, pc);
}

void emit_brcond(uint64_t v0, uint64_t v1, uint8_t condition, uint64_t a0, uint64_t a1)
{
    taint_val taint0 = cur_sc->arg0.taint;
    taint_val taint1 = cur_sc->arg1.taint;
    uint64_t val0 = (taint0 != 0) ? cur_sc->arg0.val : v0;
    uint64_t val1 = (taint1 != 0) ? cur_sc->arg1.val : v1;
    uint64_t pc = sc_get_pc();
    qapi_event_send_tainted_decision(val0, val1, taint0, taint1, condition, pc);
}

decision_choice get_decision(uint64_t v0, uint64_t v1, uint8_t condition, uint64_t a0, uint64_t a1)
{
    decision_choice decision;
    emit_brcond(v0,v1,condition, a0, a1);
    wait_for_decision();
    if (cur_sc->should_fork) {
        do_fork();
    }

    if(cur_sc->cur_decision != 0 && cur_sc->cur_decision != 1) printf("Invalid Decision = %lu\n", cur_sc->cur_decision);
    
    decision = cur_sc->cur_decision;
    cur_sc->decision_ready = false;
    cur_sc->cur_decision = UINT64_MAX;
    cur_sc->should_fork = false;
    return decision;
}

