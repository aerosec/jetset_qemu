/*
 * Tiny Code Interpreter for QEMU
 *
 * Copyright (c) 2009, 2011, 2016 Stefan Weil
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"

/* Enable TCI assertions only when debugging TCG (and without NDEBUG defined).
 * Without assertions, the interpreter runs much faster. */
#if defined(CONFIG_DEBUG_TCG)
# define tci_assert(cond) assert(cond)
#else
# define tci_assert(cond) ((void)0)
#endif

#include "qemu-common.h"
#include "tcg/tcg.h"           /* MAX_OPC_PARAM_IARGS */
#include "exec/cpu_ldst.h"
#include "tcg-op.h"
#include "exec/synth_controller.h"
#include "exec/taint.h"
#include "tcg/tci/tcg-target.h"

int mark_hit = 0;

/* Marker for missing code. */
#define TODO() \
    do { \
        fprintf(stderr, "TODO %s:%u: %s()\n", \
                __FILE__, __LINE__, __func__); \
        tcg_abort(); \
    } while (0)

#if MAX_OPC_PARAM_IARGS != 6
# error Fix needed, number of supported input arguments changed!
#endif
#if TCG_TARGET_REG_BITS == 32
typedef uint64_t (*helper_function)(tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong);
#else
typedef uint64_t (*helper_function)(tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong,
                                    tcg_target_ulong, tcg_target_ulong);
#endif

static tcg_target_ulong tci_read_reg(const tcg_target_ulong *regs, TCGReg index)
{
    tci_assert(index < TCG_TARGET_NB_REGS);
    return regs[index];
}

#if TCG_TARGET_HAS_ext8s_i32 || TCG_TARGET_HAS_ext8s_i64
static int8_t tci_read_reg8s(const tcg_target_ulong *regs, TCGReg index)
{
    return (int8_t)tci_read_reg(regs, index);
}
#endif

#if TCG_TARGET_HAS_ext16s_i32 || TCG_TARGET_HAS_ext16s_i64
static int16_t tci_read_reg16s(const tcg_target_ulong *regs, TCGReg index)
{
    return (int16_t)tci_read_reg(regs, index);
}
#endif

#if TCG_TARGET_REG_BITS == 64
static int32_t tci_read_reg32s(const tcg_target_ulong *regs, TCGReg index)
{
    return (int32_t)tci_read_reg(regs, index);
}
#endif

static uint8_t tci_read_reg8(const tcg_target_ulong *regs, TCGReg index)
{
    return (uint8_t)tci_read_reg(regs, index);
}

static uint16_t tci_read_reg16(const tcg_target_ulong *regs, TCGReg index)
{
    return (uint16_t)tci_read_reg(regs, index);
}

static uint32_t tci_read_reg32(const tcg_target_ulong *regs, TCGReg index)
{
    return (uint32_t)tci_read_reg(regs, index);
}

#if TCG_TARGET_REG_BITS == 64
static uint64_t tci_read_reg64(const tcg_target_ulong *regs, TCGReg index)
{
    return tci_read_reg(regs, index);
}
#endif

static void
tci_write_reg(tcg_target_ulong *regs, TCGReg index, tcg_target_ulong value)
{
    tci_assert(index < TCG_TARGET_NB_REGS);
    tci_assert(index != TCG_AREG0);
    tci_assert(index != TCG_REG_CALL_STACK);
    regs[index] = value;
}

#if TCG_TARGET_REG_BITS == 64
static void
tci_write_reg32s(tcg_target_ulong *regs, TCGReg index, int32_t value)
{
    tci_write_reg(regs, index, value);
}
#endif

static void tci_write_reg8(tcg_target_ulong *regs, TCGReg index, uint8_t value)
{
    tci_write_reg(regs, index, value);
}

static void
tci_write_reg32(tcg_target_ulong *regs, TCGReg index, uint32_t value)
{
    tci_write_reg(regs, index, value);
}

#if TCG_TARGET_REG_BITS == 32
static void tci_write_reg64(tcg_target_ulong *regs, uint32_t high_index,
                            uint32_t low_index, uint64_t value)
{
    tci_write_reg(regs, low_index, value);
    tci_write_reg(regs, high_index, value >> 32);
}
#elif TCG_TARGET_REG_BITS == 64
static void
tci_write_reg64(tcg_target_ulong *regs, TCGReg index, uint64_t value)
{
    tci_write_reg(regs, index, value);
}
#endif

#if TCG_TARGET_REG_BITS == 32
/* Create a 64 bit value from two 32 bit values. */
static uint64_t tci_uint64(uint32_t high, uint32_t low)
{
    return ((uint64_t)high << 32) + low;
}
#endif

/* Read constant (native size) from bytecode. */
static tcg_target_ulong tci_read_i(uint8_t **tb_ptr)
{
    tcg_target_ulong value = *(tcg_target_ulong *)(*tb_ptr);
    *tb_ptr += sizeof(value);
    return value;
}

/* Read unsigned constant (32 bit) from bytecode. */
static uint32_t tci_read_i32(uint8_t **tb_ptr)
{
    uint32_t value = *(uint32_t *)(*tb_ptr);
    *tb_ptr += sizeof(value);
    return value;
}

/* Read signed constant (32 bit) from bytecode. */
static int32_t tci_read_s32(uint8_t **tb_ptr)
{
    int32_t value = *(int32_t *)(*tb_ptr);
    *tb_ptr += sizeof(value);
    return value;
}

#if TCG_TARGET_REG_BITS == 64
/* Read constant (64 bit) from bytecode. */
static uint64_t tci_read_i64(uint8_t **tb_ptr)
{
    uint64_t value = *(uint64_t *)(*tb_ptr);
    *tb_ptr += sizeof(value);
    return value;
}
#endif

/* Read indexed register (native size) from bytecode. */
static tcg_target_ulong
tci_read_r(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    tcg_target_ulong value = tci_read_reg(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

/* Read indexed register (8 bit) from bytecode. */
static uint8_t tci_read_r8(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint8_t value = tci_read_reg8(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

#if TCG_TARGET_HAS_ext8s_i32 || TCG_TARGET_HAS_ext8s_i64
/* Read indexed register (8 bit signed) from bytecode. */
static int8_t tci_read_r8s(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    int8_t value = tci_read_reg8s(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}
#endif

/* Read indexed register (16 bit) from bytecode. */
static uint16_t tci_read_r16(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint16_t value = tci_read_reg16(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

#if TCG_TARGET_HAS_ext16s_i32 || TCG_TARGET_HAS_ext16s_i64
/* Read indexed register (16 bit signed) from bytecode. */
static int16_t tci_read_r16s(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    int16_t value = tci_read_reg16s(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}
#endif

/* Read indexed register (32 bit) from bytecode. */
static uint32_t tci_read_r32(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint32_t value = tci_read_reg32(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

#if TCG_TARGET_REG_BITS == 32
/* Read two indexed registers (2 * 32 bit) from bytecode. */
static uint64_t tci_read_r64(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint32_t low = tci_read_r32(regs, tb_ptr);
    return tci_uint64(tci_read_r32(regs, tb_ptr), low);
}
#elif TCG_TARGET_REG_BITS == 64
/* Read indexed register (32 bit signed) from bytecode. */
static int32_t tci_read_r32s(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    int32_t value = tci_read_reg32s(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}

/* Read indexed register (64 bit) from bytecode. */
static uint64_t tci_read_r64(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint64_t value = tci_read_reg64(regs, **tb_ptr);
    *tb_ptr += 1;
    return value;
}
#endif

/* Read indexed register(s) with target address from bytecode. */
static target_ulong
tci_read_ulong(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    target_ulong taddr = tci_read_r(regs, tb_ptr);
#if TARGET_LONG_BITS > TCG_TARGET_REG_BITS
    taddr += (uint64_t)tci_read_r(regs, tb_ptr) << 32;
#endif
    return taddr;
}

/* Read indexed register or constant (native size) from bytecode. */
static tcg_target_ulong
tci_read_ri(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    tcg_target_ulong value;
    TCGReg r = **tb_ptr;
    *tb_ptr += 1;
    if (r == TCG_CONST) {
        value = tci_read_i(tb_ptr);
    } else {
        value = tci_read_reg(regs, r);
    }
    return value;
}

/* Read indexed register or constant (32 bit) from bytecode. */
static uint32_t tci_read_ri32(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint32_t value;
    TCGReg r = **tb_ptr;
    *tb_ptr += 1;
    if (r == TCG_CONST) {
        value = tci_read_i32(tb_ptr);
    } else {
        value = tci_read_reg32(regs, r);
    }
    return value;
}

#if TCG_TARGET_REG_BITS == 32
/* Read two indexed registers or constants (2 * 32 bit) from bytecode. */
static uint64_t tci_read_ri64(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint32_t low = tci_read_ri32(regs, tb_ptr);
    return tci_uint64(tci_read_ri32(regs, tb_ptr), low);
}
#elif TCG_TARGET_REG_BITS == 64
/* Read indexed register or constant (64 bit) from bytecode. */
static uint64_t tci_read_ri64(const tcg_target_ulong *regs, uint8_t **tb_ptr)
{
    uint64_t value;
    TCGReg r = **tb_ptr;
    *tb_ptr += 1;
    if (r == TCG_CONST) {
        value = tci_read_i64(tb_ptr);
    } else {
        value = tci_read_reg64(regs, r);
    }
    return value;
}
#endif

static tcg_target_ulong tci_read_label(uint8_t **tb_ptr)
{
    tcg_target_ulong label = tci_read_i(tb_ptr);
    tci_assert(label != 0);
    return label;
}

static bool tci_compare32(uint32_t u0, uint32_t u1, TCGCond condition)
{
    bool result = false;
    int32_t i0 = u0;
    int32_t i1 = u1;
    switch (condition) {
    case TCG_COND_EQ:
        result = (u0 == u1);
        break;
    case TCG_COND_NE:
        result = (u0 != u1);
        break;
    case TCG_COND_LT:
        result = (i0 < i1);
        break;
    case TCG_COND_GE:
        result = (i0 >= i1);
        break;
    case TCG_COND_LE:
        result = (i0 <= i1);
        break;
    case TCG_COND_GT:
        result = (i0 > i1);
        break;
    case TCG_COND_LTU:
        result = (u0 < u1);
        break;
    case TCG_COND_GEU:
        result = (u0 >= u1);
        break;
    case TCG_COND_LEU:
        result = (u0 <= u1);
        break;
    case TCG_COND_GTU:
        result = (u0 > u1);
        break;
    default:
        TODO();
    }
    return result;
}

static bool tci_compare64(uint64_t u0, uint64_t u1, TCGCond condition)
{
    bool result = false;
    int64_t i0 = u0;
    int64_t i1 = u1;
    switch (condition) {
    case TCG_COND_EQ:
        result = (u0 == u1);
        break;
    case TCG_COND_NE:
        result = (u0 != u1);
        break;
    case TCG_COND_LT:
        result = (i0 < i1);
        break;
    case TCG_COND_GE:
        result = (i0 >= i1);
        break;
    case TCG_COND_LE:
        result = (i0 <= i1);
        break;
    case TCG_COND_GT:
        result = (i0 > i1);
        break;
    case TCG_COND_LTU:
        result = (u0 < u1);
        break;
    case TCG_COND_GEU:
        result = (u0 >= u1);
        break;
    case TCG_COND_LEU:
        result = (u0 <= u1);
        break;
    case TCG_COND_GTU:
        result = (u0 > u1);
        break;
    default:
        TODO();
    }
    return result;
}

#ifdef CONFIG_SOFTMMU
# define qemu_ld_ub \
    helper_ret_ldub_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_ld_leuw \
    helper_le_lduw_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_ld_leul \
    helper_le_ldul_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_ld_leq \
    helper_le_ldq_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_ld_beuw \
    helper_be_lduw_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_ld_beul \
    helper_be_ldul_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_ld_beq \
    helper_be_ldq_mmu(env, taddr, oi, (uintptr_t)tb_ptr)
# define qemu_st_b(X) \
    helper_ret_stb_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
# define qemu_st_lew(X) \
    helper_le_stw_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
# define qemu_st_lel(X) \
    helper_le_stl_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
# define qemu_st_leq(X) \
    helper_le_stq_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
# define qemu_st_bew(X) \
    helper_be_stw_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
# define qemu_st_bel(X) \
    helper_be_stl_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
# define qemu_st_beq(X) \
    helper_be_stq_mmu(env, taddr, X, oi, (uintptr_t)tb_ptr)
#else
# define qemu_ld_ub      ldub_p(g2h(taddr))
# define qemu_ld_leuw    lduw_le_p(g2h(taddr))
# define qemu_ld_leul    (uint32_t)ldl_le_p(g2h(taddr))
# define qemu_ld_leq     ldq_le_p(g2h(taddr))
# define qemu_ld_beuw    lduw_be_p(g2h(taddr))
# define qemu_ld_beul    (uint32_t)ldl_be_p(g2h(taddr))
# define qemu_ld_beq     ldq_be_p(g2h(taddr))
# define qemu_st_b(X)    stb_p(g2h(taddr), X)
# define qemu_st_lew(X)  stw_le_p(g2h(taddr), X)
# define qemu_st_lel(X)  stl_le_p(g2h(taddr), X)
# define qemu_st_leq(X)  stq_le_p(g2h(taddr), X)
# define qemu_st_bew(X)  stw_be_p(g2h(taddr), X)
# define qemu_st_bel(X)  stl_be_p(g2h(taddr), X)
# define qemu_st_beq(X)  stq_be_p(g2h(taddr), X)
#endif

/* Interpret pseudo code in tb. */
uintptr_t tcg_qemu_tb_exec(CPUArchState *env, uint8_t *tb_ptr)
{
    tcg_target_ulong regs[TCG_TARGET_NB_REGS];
    long tcg_temps[CPU_TEMP_BUF_NLONGS];
    uintptr_t sp_value = (uintptr_t)(tcg_temps + CPU_TEMP_BUF_NLONGS);
    uintptr_t ret = 0;

    regs[TCG_AREG0] = (tcg_target_ulong)env;
    regs[TCG_REG_CALL_STACK] = sp_value;
    tci_assert(tb_ptr);


    for (;;) {
        if(cur_sc->taint_ctr > 0) cur_sc->taint_ctr--;
        TCGOpcode opc = tb_ptr[0];
#if defined(CONFIG_DEBUG_TCG) && !defined(NDEBUG)
        uint8_t op_size = tb_ptr[1];
        uint8_t *old_code_ptr = tb_ptr;
#endif
        tcg_target_ulong t0;
        tcg_target_ulong t1;
        tcg_target_ulong t2;
        tcg_target_ulong label;
        tcg_target_ulong src_index;
        TCGCond condition;
        target_ulong taddr;
        uint8_t tmp8;
        uint16_t tmp16;
        uint32_t tmp32;
        uint64_t tmp64;
        uint8_t decision;
        symbolic_reg tainted;
#if TCG_TARGET_REG_BITS == 32
        uint64_t v64;
#endif
        TCGMemOpIdx oi;

#if defined(GETPC)
        tci_tb_ptr = (uintptr_t)tb_ptr;
#endif

        /* Skip opcode and size entry. */
        tb_ptr += 2;
        switch (opc) {
        case INDEX_op_call:
          if (mark_hit) fprintf(stderr, "op_call\n");
            // T0 stores the helper name
            t0 = tci_read_ri(regs, &tb_ptr);
            taint_ccall(tb_ptr, regs, TCG_REG_R0, TCG_REG_R0, TCG_REG_R1,
                        TCG_REG_R2, TCG_REG_R3, TCG_REG_R5, TCG_REG_R6);
#if TCG_TARGET_REG_BITS == 32
            tmp64 = ((helper_function)t0)(tci_read_reg(regs, TCG_REG_R0),
                                          tci_read_reg(regs, TCG_REG_R1),
                                          tci_read_reg(regs, TCG_REG_R2),
                                          tci_read_reg(regs, TCG_REG_R3),
                                          tci_read_reg(regs, TCG_REG_R5),
                                          tci_read_reg(regs, TCG_REG_R6),
                                          tci_read_reg(regs, TCG_REG_R7),
                                          tci_read_reg(regs, TCG_REG_R8),
                                          tci_read_reg(regs, TCG_REG_R9),
                                          tci_read_reg(regs, TCG_REG_R10),
                                          tci_read_reg(regs, TCG_REG_R11),
                                          tci_read_reg(regs, TCG_REG_R12));
            tci_write_reg(regs, TCG_REG_R0, tmp64);
            tci_write_reg(regs, TCG_REG_R1, tmp64 >> 32);
#else
            tmp64 = ((helper_function)t0)(tci_read_reg(regs, TCG_REG_R0),
                                          tci_read_reg(regs, TCG_REG_R1),
                                          tci_read_reg(regs, TCG_REG_R2),
                                          tci_read_reg(regs, TCG_REG_R3),
                                          tci_read_reg(regs, TCG_REG_R5),
                                          tci_read_reg(regs, TCG_REG_R6));
            tci_write_reg(regs, TCG_REG_R0, tmp64);
#endif
            break;
        case INDEX_op_br:
          if (mark_hit) fprintf(stderr, "op_br\n");
            label = tci_read_label(&tb_ptr);
            tci_assert(tb_ptr == old_code_ptr + op_size);
            tb_ptr = (uint8_t *)label;
            continue;
        case INDEX_op_setcond_i32:
            //tainted = taint_binop32(opc, tb_ptr);
            tainted = taint_setcond32(tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            condition = *tb_ptr++;
            tci_write_reg32(regs, t0, tci_compare32(t1, t2, condition));
            if(tainted.taint != 0){emit_setcond(t1,t2,condition);}
            if (mark_hit)
              fprintf(stderr, "op_setcond_i32, tainted: val 0x%lx taint 0x%lx,"
                      " dest_reg: 0x%lx, reg_val 1 0x%lx, reg_val 2 0x%lx, condition: 0x%x\n",
                      tainted.val, tainted.taint, t0, t1, t2, condition);
            break;
#if TCG_TARGET_REG_BITS == 32
        case INDEX_op_setcond2_i32:
          if (mark_hit) fprintf(stderr, "op_setcond2_i32\n");
            t0 = *tb_ptr++;
            tmp64 = tci_read_r64(regs, &tb_ptr);
            v64 = tci_read_ri64(regs, &tb_ptr);
            condition = *tb_ptr++;
            tci_write_reg32(regs, t0, tci_compare64(tmp64, v64, condition));
            break;
#elif TCG_TARGET_REG_BITS == 64
        case INDEX_op_setcond_i64:
          if (mark_hit) fprintf(stderr, "op_setcond_i64\n");
            tainted = taint_setcond64(tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            condition = *tb_ptr++;
            tci_write_reg64(regs, t0, tci_compare64(t1, t2, condition));
            if(tainted.taint != 0){emit_setcond(t1,t2,condition);}
            break;
#endif
        case INDEX_op_mov_i32:
          if (mark_hit) fprintf(stderr, "op_mov_i32\n");
            tainted = taint_unop32(0, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(0,t1);}
            break;
        case INDEX_op_movi_i32:
            t0 = *tb_ptr++;
            t1 = tci_read_i32(&tb_ptr);
            tci_write_reg32(regs, t0, t1);
            untaint_reg(t0);
            if (mark_hit) {
              fprintf(stderr, "op_movi_i32, Dest Register: 0x%lx, Immediate: 0x%lx\n", t0, t1);
            }
            break;

            /* Load/store operations (32 bit). */

        case INDEX_op_ld8u_i32:
          if (mark_hit) fprintf(stderr, "op_ld8u_i32\n");
            t0 = *tb_ptr++;
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_write_reg8(regs, t0, *(uint8_t *)(t1 + t2));
            taint_ld8_i32(t0, t1+t2);
            break;
        case INDEX_op_ld8s_i32:
          if (mark_hit) fprintf(stderr, "op_ld8s_i32\n");
        case INDEX_op_ld16u_i32:
          if (mark_hit) fprintf(stderr, "op_ld16u_i32\n");
            TODO();
            break;
        case INDEX_op_ld16s_i32:
          if (mark_hit) fprintf(stderr, "op_ld16s_i32\n");
            TODO();
            break;
        case INDEX_op_ld_i32:
            t0 = *tb_ptr++;
            // t1 points to the CPUStateStruct
            t1 = tci_read_r(regs, &tb_ptr);
            // t2 is an offset into that struct
            t2 = tci_read_s32(&tb_ptr);
            tci_write_reg32(regs, t0, *(uint32_t *)(t1 + t2));
            taint_ld_i32(t0, t1 + t2);
            if (mark_hit) {
              fprintf(stderr,
                      "op_ld_i32, Dest Reg: 0x%lx, "
                      "Dest Symb #: 0x%lx, Dest Taint: 0x%lx "
                      "Base Addr 0x%lx, Offset 0x%lx\n",
                      t0, cur_sc->shadow_regs[t0].val,
                      cur_sc->shadow_regs[t0].taint, t1, t2);
            }
            break;
        case INDEX_op_st8_i32:
            if (mark_hit) fprintf(stderr, "op_st8_i32\n");
            src_index = *tb_ptr;
            t0 = tci_read_r8(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            *(uint8_t *)(t1 + t2) = t0;
            taint_st8_i32(src_index, t1+t2);
            break;
        case INDEX_op_st16_i32:
          if (mark_hit) fprintf(stderr, "op_st16_i32\n");
            src_index = *tb_ptr;
            t0 = tci_read_r16(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            *(uint16_t *)(t1 + t2) = t0;
            taint_st16_i32(src_index, t1+t2);
            break;
        case INDEX_op_st_i32:
            src_index = *tb_ptr;
            t0 = tci_read_r32(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_assert(t1 != sp_value || (int32_t)t2 < 0);
            *(uint32_t *)(t1 + t2) = t0;
            taint_st_i32(src_index, t1+t2);
            if (mark_hit) {
              fprintf(stderr, "op_st_i32, ind: 0x%lx, Value: 0x%lx, Base Addr 0x%lx, Offset 0x%lx, "
                      "shadow[ind] val 0x%lx taint 0x%lx\n", src_index, t0, t1, t2,
                      cur_sc->shadow_regs[src_index].val, cur_sc->shadow_regs[src_index].taint);
            }
            break;

            /* Arithmetic operations (32 bit). */

        case INDEX_op_add_i32:
            tainted = taint_binop32_32(BINOP_ADD_I32, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 + t2);
            if(tainted.taint != 0){emit_binop(BINOP_ADD_I32,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_add_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_sub_i32:
            tainted = taint_binop32_32(BINOP_SUB_I32, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 - t2);
            if(tainted.taint != 0){emit_binop(BINOP_SUB_I32,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_sub_i32, tainted: val 0x%lx taint 0x%lx, Dest Reg: 0x%lx, left 0x%lx, right 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_mul_i32:
          if (mark_hit) fprintf(stderr, "op_mul_i32\n");
            tainted = taint_binop32_32(3, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 * t2);
            if(tainted.taint != 0){emit_binop(3,t1,t2);}
            break;
#if TCG_TARGET_HAS_div_i32
        case INDEX_op_div_i32:
          if (mark_hit) fprintf(stderr, "op_div_i32\n");
            tainted = taint_binop32_32(4, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, (int32_t)t1 / (int32_t)t2);
            if(tainted.taint != 0){emit_binop(4,t1,t2);}
            break;
        case INDEX_op_divu_i32:
          if (mark_hit) fprintf(stderr, "op_divu_i32\n");
            tainted = taint_binop32_32(5, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 / t2);
            if(tainted.taint != 0){emit_binop(5,t1,t2);}
            break;
        case INDEX_op_rem_i32:
          if (mark_hit) fprintf(stderr, "op_rem_i32\n");
            tainted = taint_binop32_32(6, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, (int32_t)t1 % (int32_t)t2);
            if(tainted.taint != 0){emit_binop(6,t1,t2);}
            break;
        case INDEX_op_remu_i32:
          if (mark_hit) fprintf(stderr, "op_remu_i32\n");
            tainted = taint_binop32_32(7, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 % t2);
            if(tainted.taint != 0){emit_binop(7,t1,t2);}
            break;
#elif TCG_TARGET_HAS_div2_i32
        case INDEX_op_div2_i32:
          if (mark_hit) fprintf(stderr, "op_div2_i32\n");
        case INDEX_op_divu2_i32:
          if (mark_hit) fprintf(stderr, "op_divu2_i32\n");
            TODO();
            break;
#endif
        case INDEX_op_and_i32:
          tainted = taint_binop32_32(BINOP_AND_I32, tb_ptr);
          t0 = *tb_ptr++;
          t1 = tci_read_ri32(regs, &tb_ptr);
          t2 = tci_read_ri32(regs, &tb_ptr);
          tci_write_reg32(regs, t0, t1 & t2);
          if (tainted.taint != 0) {
            emit_binop(BINOP_AND_I32, t1, t2);
          }
          if (mark_hit)
            fprintf(stderr,
                    "op_and_i32, tainted: val 0x%lx taint 0x%lx,"
                    " dst reg: 0x%lx, val1 0x%lx, val2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
          break;
        case INDEX_op_or_i32:
            tainted = taint_binop32_32(9, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 | t2);
            if(tainted.taint != 0){emit_binop(9,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_or_i32, tainted: val 0x%lx taint 0x%lx, dest reg: 0x%lx, val1 0x%lx, val2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_xor_i32:
          if (mark_hit) fprintf(stderr, "op_xor_i32\n");
            tainted = taint_binop32_32(BINOP_XOR_I32, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 ^ t2);
            if(tainted.taint != 0){emit_binop(BINOP_XOR_I32,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_xor_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;

            /* Shift/rotate operations (32 bit). */

        case INDEX_op_shl_i32:
          if (mark_hit) fprintf(stderr, "op_shl_i32\n");
            tainted = taint_shift_rot32(11, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 << (t2 & 31));
            if(tainted.taint != 0){emit_binop(11,t1,t2);}
            if (mark_hit)
              fprintf(stderr, "op_shl_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_shr_i32:
          if (mark_hit) fprintf(stderr, "op_shr_i32\n");
            tainted = taint_shift_rot32(12, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1 >> (t2 & 31));
            if(tainted.taint != 0){emit_binop(12,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_shr_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_sar_i32:
          if (mark_hit) fprintf(stderr, "op_sar_i32\n");
            tainted = taint_shift_rot32(13, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, ((int32_t)t1 >> (t2 & 31)));
            if(tainted.taint != 0){emit_binop(13,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_sar_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
#if TCG_TARGET_HAS_rot_i32
        case INDEX_op_rotl_i32:
          if (mark_hit) fprintf(stderr, "op_rotl_i32\n");
            tainted = taint_shift_rot32(14, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, rol32(t1, t2 & 31));
            if(tainted.taint != 0){emit_binop(14,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_rotl_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_rotr_i32:
          if (mark_hit) fprintf(stderr, "op_rotr_i32\n");
            tainted = taint_shift_rot32(15, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri32(regs, &tb_ptr);
            t2 = tci_read_ri32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, ror32(t1, t2 & 31));
            if(tainted.taint != 0){emit_binop(15,t1,t2);}
            if (mark_hit)
            fprintf(stderr, "op_rotr_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1, t2);
            break;
#endif
#if TCG_TARGET_HAS_deposit_i32
        case INDEX_op_deposit_i32:
          if (mark_hit) fprintf(stderr, "op_deposit_i32\n");
            tainted = taint_deposit32(tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            t2 = tci_read_r32(regs, &tb_ptr);
            tmp16 = *tb_ptr++;
            tmp8 = *tb_ptr++;
            tmp32 = (((1 << tmp8) - 1) << tmp16);
            tci_write_reg32(regs, t0, (t1 & ~tmp32) | ((t2 << tmp16) & tmp32));
            if(tainted.taint != 0){emit_deposit(t1,t2,tmp16,tmp32);}
            break;
#endif
        case INDEX_op_brcond_i32:
            decision = taint_brcond32(regs, tb_ptr);
            t0 = tci_read_r32(regs, &tb_ptr);
            t1 = tci_read_ri32(regs, &tb_ptr);
            condition = *tb_ptr++;
            label = tci_read_label(&tb_ptr);
            if(decision == UINT8_MAX){
                if (tci_compare32(t0, t1, condition)) {
                    tci_assert(tb_ptr == old_code_ptr + op_size);
                    tb_ptr = (uint8_t *)label;
                    if (mark_hit) {
                      fprintf(stderr, "op_brcond_i32, decision: 0x%x, Val 1: 0x%lx, Val 2: 0x%lx, cond 0x%x, "
                              "label %lx\n", decision, t0, t1, condition, label);
                    }
                    continue;
                }
            }
            else{
                if (decision) {
                    tci_assert(tb_ptr == old_code_ptr + op_size);
                    tb_ptr = (uint8_t *)label;
                    if (mark_hit) {
                      fprintf(stderr, "op_brcond_i32, decision: 0x%x, Val 1: 0x%lx, Val 2: 0x%lx, cond 0x%x, "
                              "label %lx\n", decision, t0, t1, condition, label);
                    }
                    continue;
                }
            }
            if (mark_hit) {
              fprintf(stderr, "op_brcond_i32, decision: 0x%x, Val 1: 0x%lx, Val 2: 0x%lx, cond 0x%x, "
                      "label %lx\n", decision, t0, t1, condition, label);
            }
            break;
#if TCG_TARGET_REG_BITS == 32
        case INDEX_op_add2_i32:
          if (mark_hit) fprintf(stderr, "op_add2_i32\n");
            t0 = *tb_ptr++;
            t1 = *tb_ptr++;
            tmp64 = tci_read_r64(regs, &tb_ptr);
            tmp64 += tci_read_r64(regs, &tb_ptr);
            tci_write_reg64(regs, t1, t0, tmp64);
            break;
        case INDEX_op_sub2_i32:
          if (mark_hit) fprintf(stderr, "op_sub2_i32\n");
            t0 = *tb_ptr++;
            t1 = *tb_ptr++;
            tmp64 = tci_read_r64(regs, &tb_ptr);
            tmp64 -= tci_read_r64(regs, &tb_ptr);
            tci_write_reg64(regs, t1, t0, tmp64);
            break;
        case INDEX_op_brcond2_i32:
          if (mark_hit) fprintf(stderr, "op_brcond2_i32\n");
            tmp64 = tci_read_r64(regs, &tb_ptr);
            v64 = tci_read_ri64(regs, &tb_ptr);
            condition = *tb_ptr++;
            label = tci_read_label(&tb_ptr);
            if (tci_compare64(tmp64, v64, condition)) {
                tci_assert(tb_ptr == old_code_ptr + op_size);
                tb_ptr = (uint8_t *)label;
                continue;
            }
            break;
        case INDEX_op_mulu2_i32:
          if (mark_hit) fprintf(stderr, "op_mulu2_i32\n");
            t0 = *tb_ptr++;
            t1 = *tb_ptr++;
            t2 = tci_read_r32(regs, &tb_ptr);
            tmp64 = tci_read_r32(regs, &tb_ptr);
            tci_write_reg64(regs, t1, t0, t2 * tmp64);
            break;
#endif /* TCG_TARGET_REG_BITS == 32 */
#if TCG_TARGET_HAS_ext8s_i32
        case INDEX_op_ext8s_i32:
          tainted = taint_unop32(UNOP_EXT8S_I32, tb_ptr);
          t0 = *tb_ptr++;
          t1 = tci_read_r8s(regs, &tb_ptr);
          tci_write_reg32(regs, t0, t1);
          if (tainted.taint != 0) {
            emit_unop(UNOP_EXT8S_I32, t1);
          }
          if (mark_hit) {
            fprintf(stderr,
                    "op_ext8s_i32, tainted: val 0x%lx taint 0x%lx, dest reg: 0x%lx, "
                    "source val 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1);
          }
          break;
#endif
#if TCG_TARGET_HAS_ext16s_i32
        case INDEX_op_ext16s_i32:
          if (mark_hit)
            fprintf(stderr, "op_ext16s_i32\n");
          tainted = taint_unop32(UNOP_EXT16S_I32, tb_ptr);
          t0 = *tb_ptr++;
          t1 = tci_read_r16s(regs, &tb_ptr);
          tci_write_reg32(regs, t0, t1);
          if (tainted.taint != 0) {
            emit_unop(UNOP_EXT16S_I32, t1);
          }
          break;
#endif
#if TCG_TARGET_HAS_ext8u_i32
        case INDEX_op_ext8u_i32:
          if (mark_hit) fprintf(stderr, "op_ext8u_i32\n");
            tainted = taint_unop32(18, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r8(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(18,t1);}
            if (mark_hit) {
              fprintf(stderr, "op_ext8u_i32, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1);
            }
            break;
#endif
#if TCG_TARGET_HAS_ext16u_i32
        case INDEX_op_ext16u_i32:
          if (mark_hit) fprintf(stderr, "op_ext16u_i32\n");
            tainted = taint_unop32(19, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r16(regs, &tb_ptr);
            tci_write_reg32(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(19,t1);}
            break;
#endif
#if TCG_TARGET_HAS_bswap16_i32
        case INDEX_op_bswap16_i32:
          if (mark_hit) fprintf(stderr, "op_bswap16_i32\n");
            tainted = taint_unop32(20, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r16(regs, &tb_ptr);
            tci_write_reg32(regs, t0, bswap16(t1));
            if(tainted.taint != 0){emit_unop(20,t1);}
            break;
#endif
#if TCG_TARGET_HAS_bswap32_i32
        case INDEX_op_bswap32_i32:
          if (mark_hit) fprintf(stderr, "op_bswap32_i32\n");
            tainted = taint_unop32(21, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, bswap32(t1));
            if(tainted.taint != 0){emit_unop(21,t1);}
            break;
#endif
#if TCG_TARGET_HAS_not_i32
        case INDEX_op_not_i32:
            tainted = taint_unop32(UNOP_NOT_I32, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, ~t1);
            if(tainted.taint != 0){emit_unop(UNOP_NOT_I32,t1);}
            if (mark_hit)
              fprintf(stderr, "op_not_i32, tainted: val 0x%lx taint 0x%lx,"
                      " dest reg: 0x%lx, notted val 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1);
            break;
#endif
#if TCG_TARGET_HAS_neg_i32
        case INDEX_op_neg_i32:
            tainted = taint_unop32(23, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            tci_write_reg32(regs, t0, -t1);
            if(tainted.taint != 0){emit_unop(23,t1);}
            if (mark_hit)
              fprintf(stderr, "op_neg_i32, tainted: val 0x%lx taint 0x%lx,"
                      " dest reg: 0x%lx, negated val 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1);
            break;
#endif
#if TCG_TARGET_REG_BITS == 64
        case INDEX_op_mov_i64:
          tainted = taint_unop64(24, tb_ptr);
          t0 = *tb_ptr++;
          t1 = tci_read_r64(regs, &tb_ptr);
          tci_write_reg64(regs, t0, t1);
          if (tainted.taint != 0) {
            emit_unop(24, t1);
          }
          if (mark_hit)
            fprintf(stderr,
                    "op_mov_i64, tainted: val 0x%lx taint 0x%lx,"
                    " dest reg: 0x%lx, val 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1);
          break;
        case INDEX_op_movi_i64:
          if (mark_hit) fprintf(stderr, "op_movi_i64\n");
            t0 = *tb_ptr++;
            t1 = tci_read_i64(&tb_ptr);
            tci_write_reg64(regs, t0, t1);
            untaint_reg(t0);
            break;

            /* Load/store operations (64 bit). */

        case INDEX_op_ld8u_i64:
          if (mark_hit) fprintf(stderr, "op_ld8u_i64\n");
            t0 = *tb_ptr++;
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_write_reg8(regs, t0, *(uint8_t *)(t1 + t2));
            taint_ld8_i32(t0, t1+t2);
            break;
        case INDEX_op_ld8s_i64:
          if (mark_hit) fprintf(stderr, "op_ld8s_i64\n");
        case INDEX_op_ld16u_i64:
          if (mark_hit) fprintf(stderr, "op_ld16u_i64\n");
        case INDEX_op_ld16s_i64:
          if (mark_hit) fprintf(stderr, "op_ld16s_i64\n");
            TODO();
            break;
        case INDEX_op_ld32u_i64:
          if (mark_hit) fprintf(stderr, "op_ld32u_i64\n");
            t0 = *tb_ptr++;
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_write_reg32(regs, t0, *(uint32_t *)(t1 + t2));
            taint_ld_i32(t0, t1+t2);
            break;
        case INDEX_op_ld32s_i64:
          if (mark_hit) fprintf(stderr, "op_ld32s_i64\n");
            t0 = *tb_ptr++;
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_write_reg32s(regs, t0, *(int32_t *)(t1 + t2));
            taint_ld_i32(t0, t1+t2);
            break;
        case INDEX_op_ld_i64:
          if (mark_hit) fprintf(stderr, "op_ld_i64\n");
            t0 = *tb_ptr++;
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_write_reg64(regs, t0, *(uint64_t *)(t1 + t2));
            taint_ld_i64(t0, t1+t2);
            break;
        case INDEX_op_st8_i64:
          if (mark_hit) fprintf(stderr, "op_st8_i64\n");
            src_index = *tb_ptr;
            t0 = tci_read_r8(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            *(uint8_t *)(t1 + t2) = t0;
            taint_st8_i32(src_index, t1+t2);
            break;
        case INDEX_op_st16_i64:
          if (mark_hit) fprintf(stderr, "op_st16_i64\n");
            src_index = *tb_ptr;
            t0 = tci_read_r16(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            *(uint16_t *)(t1 + t2) = t0;
            taint_st16_i32(src_index, t1+t2);
            break;
        case INDEX_op_st32_i64:
          if (mark_hit) fprintf(stderr, "op_st32_i64\n");
            src_index = *tb_ptr;
            t0 = tci_read_r32(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            *(uint32_t *)(t1 + t2) = t0;
            taint_st_i32(src_index, t1+t2);
            break;
        case INDEX_op_st_i64:
          if (mark_hit) fprintf(stderr, "op_st_i64\n");
            src_index = *tb_ptr;
            t0 = tci_read_r64(regs, &tb_ptr);
            t1 = tci_read_r(regs, &tb_ptr);
            t2 = tci_read_s32(&tb_ptr);
            tci_assert(t1 != sp_value || (int32_t)t2 < 0);
            *(uint64_t *)(t1 + t2) = t0;
            taint_st_i64(src_index, t1+t2);
            break;

            /* Arithmetic operations (64 bit). */

        case INDEX_op_add_i64:
          if (mark_hit) fprintf(stderr, "op_add_i64\n");
            tainted = taint_binop64_64(25, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 + t2);
            if(tainted.taint != 0){emit_binop(25,t1,t2);}
            break;
        case INDEX_op_sub_i64:
          if (mark_hit) fprintf(stderr, "op_sub_i64\n");
            tainted = taint_binop64_64(26, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 - t2);
            if(tainted.taint != 0){emit_binop(26,t1,t2);}
            break;
        case INDEX_op_mul_i64:
          if (mark_hit) fprintf(stderr, "op_mul_i64\n");
            tainted = taint_binop64_64(27, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 * t2);
            if(tainted.taint != 0){emit_binop(27,t1,t2);}
            break;
#if TCG_TARGET_HAS_div_i64
        case INDEX_op_div_i64:
          if (mark_hit) fprintf(stderr, "op_div_i64\n");
        case INDEX_op_divu_i64:
          if (mark_hit) fprintf(stderr, "op_divu_i64\n");
        case INDEX_op_rem_i64:
          if (mark_hit) fprintf(stderr, "op_rem_i64\n");
        case INDEX_op_remu_i64:
          if (mark_hit) fprintf(stderr, "op_remu_i64\n");
            TODO();
            break;
#elif TCG_TARGET_HAS_div2_i64
        case INDEX_op_div2_i64:
          if (mark_hit) fprintf(stderr, "op_div2_i64\n");
        case INDEX_op_divu2_i64:
          if (mark_hit) fprintf(stderr, "op_divu2_i64\n");
            TODO();
            break;
#endif
        case INDEX_op_and_i64:
          if (mark_hit) fprintf(stderr, "op_and_i64\n");
            tainted = taint_binop64_64(28, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 & t2);
            if(tainted.taint != 0){emit_binop(28,t1,t2);}
            break;
        case INDEX_op_or_i64:
          if (mark_hit) fprintf(stderr, "op_or_i64\n");
            tainted = taint_binop64_64(29, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 | t2);
            if(tainted.taint != 0){emit_binop(29,t1,t2);}
            break;
        case INDEX_op_xor_i64:
          if (mark_hit) fprintf(stderr, "op_xor_i64\n");
            tainted = taint_binop64_64(30, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 ^ t2);
            if(tainted.taint != 0){emit_binop(30,t1,t2);}
            if (mark_hit)
              fprintf(stderr, "op_xor_i64, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1, t2);
            break;

            /* Shift/rotate operations (64 bit). */

        case INDEX_op_shl_i64:
            tainted = taint_shift_rot64(31, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            // TCI should emit the mask but we want to be extra safe
            tci_write_reg64(regs, t0, t1 << (t2 & 0x3F)); 
            if(tainted.taint != 0){emit_binop(31,t1,t2);}
            if (mark_hit)
              fprintf(stderr, "op_shl_i64, tainted: val 0x%lx taint 0x%lx,"
                      " dst reg: 0x%lx, val 0x%lx, shift amt 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_shr_i64:
            tainted = taint_shift_rot64(32, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1 >> (t2 & 0x3F));
            if(tainted.taint != 0){emit_binop(32,t1,t2);}
            if (mark_hit)
              fprintf(stderr, "op_shr_i64, tainted: val 0x%lx taint 0x%lx,"
                      " dst reg: 0x%lx, val 0x%lx, shift amt 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1, t2);
            break;
        case INDEX_op_sar_i64:
          if (mark_hit) fprintf(stderr, "op_sar_i64\n");
            tainted = taint_shift_rot64(33, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, ((int64_t)t1 >> (t2 & 63)));
            if(tainted.taint != 0){emit_binop(33,t1,t2);}
            if (mark_hit)
              fprintf(stderr, "op_sar_i64, tainted: val 0x%lx taint 0x%lx, t0: 0x%lx, t1 0x%lx, t2 0x%lx\n",
                      tainted.val, tainted.taint, t0, t1, t2);
            break;
#if TCG_TARGET_HAS_rot_i64
        case INDEX_op_rotl_i64:
          if (mark_hit) fprintf(stderr, "op_rotl_i64\n");
            tainted = taint_shift_rot64(34, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, rol64(t1, t2 & 63));
            if(tainted.taint != 0){emit_binop(34,t1,t2);}
            break;
        case INDEX_op_rotr_i64:
          if (mark_hit) fprintf(stderr, "op_rotr_i64\n");
            tainted = taint_shift_rot64(35, tb_ptr, regs);
            t0 = *tb_ptr++;
            t1 = tci_read_ri64(regs, &tb_ptr);
            t2 = tci_read_ri64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, ror64(t1, t2 & 63));
            if(tainted.taint != 0){emit_binop(35,t1,t2);}
            break;
#endif
#if TCG_TARGET_HAS_deposit_i64
        case INDEX_op_deposit_i64:
          if (mark_hit) fprintf(stderr, "op_deposit_i64\n");
            tainted = taint_deposit64(tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r64(regs, &tb_ptr);
            t2 = tci_read_r64(regs, &tb_ptr);
            tmp16 = *tb_ptr++;
            tmp8 = *tb_ptr++;
            tmp64 = (((1ULL << tmp8) - 1) << tmp16);
            tci_write_reg64(regs, t0, (t1 & ~tmp64) | ((t2 << tmp16) & tmp64));
            if(tainted.taint != 0){emit_deposit(t1, t2, tmp16, tmp64);}
            break;
#endif
        case INDEX_op_brcond_i64:
          if (mark_hit) fprintf(stderr, "op_brcond_i64\n");
            decision = taint_brcond64(regs, tb_ptr);
            t0 = tci_read_r64(regs, &tb_ptr);
            t1 = tci_read_ri64(regs, &tb_ptr);
            condition = *tb_ptr++;
            label = tci_read_label(&tb_ptr);
            if(decision == UINT8_MAX){
                if (tci_compare64(t0, t1, condition)) {
                    tci_assert(tb_ptr == old_code_ptr + op_size);
                    tb_ptr = (uint8_t *)label;
                    if (mark_hit) {
                      fprintf(stderr, "op_brcond_i64, decision: 0x%x, t0: 0x%lx, t1 0x%lx, condition 0x%x,"
                              "label 0x%lx\n", decision, t0, t1, condition, label);
                    }
                    continue;
                }
            }
            else{
                if (decision) {
                    tci_assert(tb_ptr == old_code_ptr + op_size);
                    tb_ptr = (uint8_t *)label;
                    if (mark_hit) {
                      fprintf(stderr, "op_brcond_i64, decision: 0x%x, t0: 0x%lx, t1 0x%lx, condition 0x%x,"
                              "label 0x%lx\n", decision, t0, t1, condition, label);
                    }
                    continue;
                }
            }

            if (mark_hit) {
              fprintf(stderr, "op_brcond_i64, decision: 0x%x, t0: 0x%lx, t1 0x%lx, condition 0x%x,"
                      "label 0x%lx\n", decision, t0, t1, condition, label);
            }
            break;
#if TCG_TARGET_HAS_ext8u_i64
        case INDEX_op_ext8u_i64:
          if (mark_hit) fprintf(stderr, "op_ext8u_i64\n");
            tainted = taint_unop64(36, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r8(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(36,t1);}
            break;
#endif
#if TCG_TARGET_HAS_ext8s_i64
        case INDEX_op_ext8s_i64:
          if (mark_hit) fprintf(stderr, "op_ext8s_i64\n");
            tainted = taint_unop64(37, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r8s(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(37,t1);}
            break;
#endif
#if TCG_TARGET_HAS_ext16s_i64
        case INDEX_op_ext16s_i64:
          if (mark_hit) fprintf(stderr, "op_ext16s_i64\n");
            tainted = taint_unop64(38, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r16s(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(38,t1);}
            break;
#endif
#if TCG_TARGET_HAS_ext16u_i64
        case INDEX_op_ext16u_i64:
          if (mark_hit) fprintf(stderr, "op_ext16u_i64\n");
            tainted = taint_unop64(39, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r16(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(39,t1);}
            break;
#endif
#if TCG_TARGET_HAS_ext32s_i64
        case INDEX_op_ext32s_i64:
          if (mark_hit) fprintf(stderr, "op_ext32s_i64\n");
#endif
        case INDEX_op_ext_i32_i64:
          if (mark_hit) fprintf(stderr, "op_ext_i32_i64\n");
            tainted = taint_unop64(40, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32s(regs, &tb_ptr);
            tci_write_reg64(regs, t0, t1);
            if(tainted.taint != 0){emit_unop(40,t1);}
            break;
#if TCG_TARGET_HAS_ext32u_i64
        case INDEX_op_ext32u_i64:
          if (mark_hit) fprintf(stderr, "op_ext32u_i64\n");
#endif
        case INDEX_op_extu_i32_i64:
          tainted = taint_unop64(41, tb_ptr);
          t0 = *tb_ptr++;
          t1 = tci_read_r32(regs, &tb_ptr);
          tci_write_reg64(regs, t0, t1);
          if (tainted.taint != 0) {
            emit_unop(41, t1);
          }
          if (mark_hit)
            fprintf(stderr,
                    "op_extu_i32_i64, tainted: val 0x%lx taint 0x%lx,"
                    " dest reg: 0x%lx, val 0x%lx\n",
                    tainted.val, tainted.taint, t0, t1);
          break;
#if TCG_TARGET_HAS_bswap16_i64
        case INDEX_op_bswap16_i64:
          if (mark_hit) fprintf(stderr, "op_bswap16_i64\n");
            tainted = taint_unop64(42, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r16(regs, &tb_ptr);
            tci_write_reg64(regs, t0, bswap16(t1));
            if(tainted.taint != 0){emit_unop(42,t1);}
            break;
#endif
#if TCG_TARGET_HAS_bswap32_i64
        case INDEX_op_bswap32_i64:
          if (mark_hit) fprintf(stderr, "op_bswap32_i64\n");
            tainted = taint_unop64(43, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r32(regs, &tb_ptr);
            tci_write_reg64(regs, t0, bswap32(t1));
            if(tainted.taint != 0){emit_unop(43,t1);}
            break;
#endif
#if TCG_TARGET_HAS_bswap64_i64
        case INDEX_op_bswap64_i64:
          if (mark_hit) fprintf(stderr, "op_bswap64_i64\n");
            tainted = taint_unop64(44, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, bswap64(t1));
            if(tainted.taint != 0){emit_unop(44,t1);}
            break;
#endif
#if TCG_TARGET_HAS_not_i64
        case INDEX_op_not_i64:
          if (mark_hit) fprintf(stderr, "op_not_i64\n");
            tainted = taint_unop64(45, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, ~t1);
            if(tainted.taint != 0){emit_unop(45,t1);}
            break;
#endif
#if TCG_TARGET_HAS_neg_i64
        case INDEX_op_neg_i64:
          if (mark_hit) fprintf(stderr, "op_neg_i64\n");
            tainted = taint_unop64(46, tb_ptr);
            t0 = *tb_ptr++;
            t1 = tci_read_r64(regs, &tb_ptr);
            tci_write_reg64(regs, t0, -t1);
            if(tainted.taint != 0){emit_unop(46,t1);}
            break;
#endif
#endif /* TCG_TARGET_REG_BITS == 64 */

            /* QEMU specific operations. */

        case INDEX_op_exit_tb:
          if (mark_hit) fprintf(stderr, "op_exit_tb\n");
            ret = *(uint64_t *)tb_ptr;
            goto exit;
            break;
        case INDEX_op_goto_tb:
          if (mark_hit) fprintf(stderr, "op_goto_tb\n");
            /* Jump address is aligned */
            tb_ptr = QEMU_ALIGN_PTR_UP(tb_ptr, 4);
            t0 = atomic_read((int32_t *)tb_ptr);
            tb_ptr += sizeof(int32_t);
            tci_assert(tb_ptr == old_code_ptr + op_size);
            tb_ptr += (int32_t)t0;
            continue;
        case INDEX_op_qemu_ld_i32:
            t0 = *tb_ptr++;
            taddr = tci_read_ulong(regs, &tb_ptr);
            oi = tci_read_i(&tb_ptr);
            switch (get_memop(oi) & (MO_BSWAP | MO_SSIZE)) {
            case MO_UB:
                tmp32 = qemu_ld_ub;
                taint_ld8_i32(t0, taddr);
                break;
            case MO_SB:
                tmp32 = (int8_t)qemu_ld_ub;
                taint_ld8_i32(t0, taddr);
                break;
            case MO_LEUW:
                tmp32 = qemu_ld_leuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_LESW:
                tmp32 = (int16_t)qemu_ld_leuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_LEUL:
                tmp32 = qemu_ld_leul;
                taint_ld_i32(t0, taddr);
                break;
            case MO_BEUW:
                tmp32 = qemu_ld_beuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_BESW:
                tmp32 = (int16_t)qemu_ld_beuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_BEUL:
                tmp32 = qemu_ld_beul;
                taint_ld_i32(t0, taddr);
                break;
            default:
                tcg_abort();
            }
            tci_write_reg(regs, t0, tmp32);
            if (mark_hit)
              fprintf(stderr, "op_qemu_ld_i32, dst reg: 0x%lx, Val 0x%x\n", t0, tmp32);
            break;
        case INDEX_op_qemu_ld_i64:
          if (mark_hit) fprintf(stderr, "op_qemu_ld_i64\n");
            t0 = *tb_ptr++;
            if (TCG_TARGET_REG_BITS == 32) {
                t1 = *tb_ptr++;
            }
            taddr = tci_read_ulong(regs, &tb_ptr);
            oi = tci_read_i(&tb_ptr);
            switch (get_memop(oi) & (MO_BSWAP | MO_SSIZE)) {
            case MO_UB:
                tmp64 = qemu_ld_ub;
                taint_ld8_i32(t0, taddr);
                break;
            case MO_SB:
                tmp64 = (int8_t)qemu_ld_ub;
                taint_ld8_i32(t0, taddr);
                break;
            case MO_LEUW:
                tmp64 = qemu_ld_leuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_LESW:
                tmp64 = (int16_t)qemu_ld_leuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_LEUL:
                tmp64 = qemu_ld_leul;
                taint_ld_i32(t0, taddr);
                break;
            case MO_LESL:
                tmp64 = (int32_t)qemu_ld_leul;
                taint_ld_i32(t0, taddr);
                break;
            case MO_LEQ:
                tmp64 = qemu_ld_leq;
                taint_ld_i64(t0, taddr);
                break;
            case MO_BEUW:
                tmp64 = qemu_ld_beuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_BESW:
                tmp64 = (int16_t)qemu_ld_beuw;
                taint_ld16_i32(t0, taddr);
                break;
            case MO_BEUL:
                tmp64 = qemu_ld_beul;
                taint_ld_i32(t0, taddr);
                break;
            case MO_BESL:
                tmp64 = (int32_t)qemu_ld_beul;
                taint_ld_i32(t0, taddr);
                break;
            case MO_BEQ:
                tmp64 = qemu_ld_beq;
                taint_ld_i64(t0, taddr);
                break;
            default:
                tcg_abort();
            }
            tci_write_reg(regs, t0, tmp64);
            //taint_ld_i64(t0, taddr);
            if (TCG_TARGET_REG_BITS == 32) {
                tci_write_reg(regs, t1, tmp64 >> 32);
            }
            break;
        case INDEX_op_qemu_st_i32:
          if (mark_hit) fprintf(stderr, "op_qemu_st_i32\n");
            src_index = *tb_ptr;
            t0 = tci_read_r(regs, &tb_ptr);
            taddr = tci_read_ulong(regs, &tb_ptr);
            oi = tci_read_i(&tb_ptr);
            switch (get_memop(oi) & (MO_BSWAP | MO_SIZE)) {
            case MO_UB: // 1 byte
                qemu_st_b(t0);
                taint_st8_i32(src_index, taddr);
                break;
            case MO_LEUW: // little endian word (16 bit)
                qemu_st_lew(t0);
                taint_st16_i32(src_index, taddr);
                break;
            case MO_LEUL: // little endian long (32 bit)
                qemu_st_lel(t0);
                taint_st_i32(src_index, taddr);
                break;
            case MO_BEUW: // big endian word (16 but)
                qemu_st_bew(t0);
                taint_st16_i32(src_index, taddr);
                break;
            case MO_BEUL: // big endian long (32 bit)
                qemu_st_bel(t0);
                taint_st_i32(src_index, taddr);
                break;
            default:
                tcg_abort();
            }
            //taint_st_i32(src_index, taddr);
            break;
        case INDEX_op_qemu_st_i64:
          if (mark_hit) fprintf(stderr, "op_qemu_st_i64\n");
            src_index = *tb_ptr;
            tmp64 = tci_read_r64(regs, &tb_ptr);
            taddr = tci_read_ulong(regs, &tb_ptr);
            oi = tci_read_i(&tb_ptr);
            switch (get_memop(oi) & (MO_BSWAP | MO_SIZE)) {
            case MO_UB:
                qemu_st_b(tmp64);
                taint_st8_i32(src_index, taddr);
                break;
            case MO_LEUW:
                qemu_st_lew(tmp64);
                taint_st16_i32(src_index, taddr);
                break;
            case MO_LEUL:
                qemu_st_lel(tmp64);
                taint_st_i32(src_index, taddr);
                break;
            case MO_LEQ:
                qemu_st_leq(tmp64);
                taint_st_i64(src_index, taddr);
                break;
            case MO_BEUW:
                qemu_st_bew(tmp64);
                taint_st16_i32(src_index, taddr);
                break;
            case MO_BEUL:
                qemu_st_bel(tmp64);
                taint_st_i32(src_index, taddr);
                break;
            case MO_BEQ:
                qemu_st_beq(tmp64);
                taint_st_i64(src_index, taddr);
                break;
            default:
                tcg_abort();
            }
            break;
        case INDEX_op_mb:
          if (mark_hit) fprintf(stderr, "op_mb\n");
            /* Ensure ordering for all kinds */
            smp_mb();
            break;
        default:
            TODO();
            break;
        }
        tci_assert(tb_ptr == old_code_ptr + op_size);
    }
exit:
    return ret;
}
