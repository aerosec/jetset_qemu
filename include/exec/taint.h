#ifndef TAINT_H
#define TAINT_H
#include "qapi/qapi-events-misc.h" 
#include "exec/shadow_mem.h"
#include "exec/synth_controller.h"


#define TCG_MOV32 0
#define TCG_ADD32 1
#define TCG_SUB32 2
#define TCG_MUL32 3
#define TCG_DIV32 4
#define TCG_DIVU32 5
#define TCG_REM32 6
#define TCG_REMU32 7
#define TCG_AND32 8
#define TCG_OR32 9
#define TCG_XOR32 10
#define TCG_SHL32 11
#define TCG_SHR32 12
#define TCG_SAR32 13
#define TCG_ROTL32 14
#define TCG_ROTR32 15
#define TCG_EXT8S_32 16
#define TCG_EXT16S_32 17
#define TCG_EXT8U_32 18
#define TCG_EXT16U_32 19
#define TCG_BSWAP16_32 20
#define TCG_BSWAP32_32 21
#define TCG_NOT32 22
#define TCG_NEG32 23
#define TCG_MOV64 24
#define TCG_ADD64 25
#define TCG_SUB64 26
#define TCG_MUL64 27
#define TCG_AND64 28
#define TCG_OR64 29
#define TCG_XOR64 30
#define TCG_SHL64 31
#define TCG_SHR64 32
#define TCG_SAR64 33
#define TCG_ROTL64 34
#define TCG_ROTR64 35
#define TCG_EXT8U_64 36
#define TCG_EXT8S_64 37
#define TCG_EXT16S_64 38
#define TCG_EXT16U_64 39
#define TCG_EXT32S_64 40
#define TCG_EXT32U_64 41
#define TCG_BSWAP16_64 42
#define TCG_BSWAP32_64 43
#define TCG_BSWAP64_64 44
#define TCG_NOT64 45
#define TCG_NEG64 46

#define MASK64  0xffffffffffffffff
#define MASK32  0x0ffffffff
#define MASK16  0x0000ffff
#define MASK8   0x000000ff





symbolic_reg taint_ri32(uint8_t **tb_ptr);
symbolic_reg taint_ri64(uint8_t **tb_ptr);
symbolic_reg taint_r(uint8_t **tb_ptr);
symbolic_reg taint_s32(uint8_t **tb_ptr);

symbolic_reg taint_binopr_r(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_binop32(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_binop32_32(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_binop64(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_binop64_64(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_unop32(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_unop64(uint8_t opc, uint8_t *tb_ptr);
symbolic_reg taint_deposit32(uint8_t *tb_ptr);
symbolic_reg taint_deposit64(uint8_t *tb_ptr);
symbolic_reg taint_shift_rot32(uint8_t opc, uint8_t *tb_ptr, const uint64_t *regs);
symbolic_reg taint_shift_rot64(uint8_t opc, uint8_t *tb_ptr, const uint64_t *regs);
symbolic_reg taint_setcond32(uint8_t *tb_ptr);
symbolic_reg taint_setcond64(uint8_t *tb_ptr);

//TODO: check if symbolic_valic address is used
void taint_ld8_i32(uint8_t dst_index, uint64_t addr);
void taint_ld16_i32(uint8_t dst_index, uint64_t addr);
void taint_ld_i32(uint8_t dst_index, uint64_t addr);
void taint_ld_i64(uint8_t dst_index, uint64_t addr);

void taint_st8_i32(uint8_t src_index, uint64_t addr);
void taint_st16_i32(uint8_t src_index, uint64_t addr);
void taint_st_i32(uint8_t src_index, uint64_t addr);
void taint_st_i64(uint8_t src_index, uint64_t addr);

decision_choice taint_brcond32(const uint64_t *regs, uint8_t *tb_ptr);
decision_choice taint_brcond64(const uint64_t *regs, uint8_t *tb_ptr);

void taint_ioport_read(uint64_t addr, uint64_t size);
void taint_ioport_write(uint64_t addr, uint64_t val);
uint64_t taint_mmio_read(uint64_t addr, uint64_t size);
void taint_mmio_write(uint64_t addr, uint64_t val);
void taint_intc_read(uint64_t addr, uint64_t val_returned);


void emit_unop(uint8_t opc, uint64_t v);
void emit_unop_symbolic(uint8_t opc, symbolic_reg dst, symbolic_reg src);
void emit_binop(uint8_t opc, uint64_t v0, uint64_t v1);
void emit_binop_symbolic(uint8_t opc, symbolic_reg dst, symbolic_reg left,
                         symbolic_reg right);
void emit_deposit(uint64_t v0, uint64_t v1, uint64_t c0, uint64_t c1);
void emit_setcond(uint64_t v0, uint64_t v1, uint8_t condition);
void emit_setcond_symbolic(symbolic_reg dst, symbolic_reg left, symbolic_reg right,
                           uint8_t condition);
void emit_brcond(uint64_t v0, uint64_t v1, uint8_t condition, uint64_t a0, uint64_t a1);

symbolic_reg fresh_symbolic_reg(symbolic_val v, uint64_t size);

decision_choice get_decision(uint64_t v0, uint64_t v1, uint8_t condition, uint64_t a0, uint64_t a1);
void untaint_reg(uint8_t dst_index);
void taint_ccall(uint8_t* tb_ptr,
	             const uint64_t *regs,
	             uint8_t dst_index, 
	             uint8_t src_index0, 
	             uint8_t src_index1, 
	             uint8_t src_index2, 
	             uint8_t src_index3, 
	             uint8_t src_index5,
	             uint8_t src_index6);

uint64_t* decision_finalized(uint64_t pc);
uint64_t* io_finalized(uint64_t addr);

symbolic_reg extsign_taint(int op, symbolic_reg res, symbolic_reg src,
                           uint32_t index);
void taint_ccr_m68k(void * state_ptr, uint32_t cc_op);
void taint_set_ccr_m68k(void * state_ptr);

#endif /* TAINT_H */
 
