/**************************************************************************
 * Synth Controller API                                                   *
 **************************************************************************/

#ifndef SYNTH_CONTROLLER_H
#define SYNTH_CONTROLLER_H
#include "qapi/qapi-events-misc.h" 

#define NB_SEG_TBL_ENTRIES (0x01 << 20)
#define MAX_NB_TCG_REGS 16

#define UNTAINTED_DECISION UINT8_MAX
#define TCG_REG_SIZE sizeof(symbolic_reg)
#define taint_val uint64_t

#define ARCHNAME_ARM  1
#define ARCHNAME_M68K 2
#define ARCHNAME_X86  3



typedef uint8_t decision_choice; // 0 = no take branch, 1 = take branch, UINT8_MAX = non tainted

enum sc_bp_type{TARGET=0, AVOID};

typedef struct ScBreakpoint
{
    uint64_t addr;
    uint8_t type;   
}ScBreakpoint;


typedef uint64_t symbolic_val;

typedef struct symbolic_reg
{
    symbolic_val val;
    taint_val taint;   
} symbolic_reg;


typedef struct finalized_decision
{
    uint64_t pc;
    uint64_t val;   
} finalized_decision;


typedef struct finalized_io
{
    uint64_t addr;
    uint64_t val;   
} finalized_io;

typedef struct SynthController
{
	uint8_t id;
	volatile bool decision_ready;
	volatile uint64_t cur_decision;
	symbolic_val*** shadow_seg_tbl;  	
    symbolic_reg* shadow_regs;
    symbolic_val symbol_idx;
    symbolic_reg dst;
    symbolic_reg arg0; 
    symbolic_reg arg1;
    FILE* logfile;
    uint64_t taint_ctr;
    symbolic_reg pending_mmio_read;
    uint8_t active_bp_count;
    ScBreakpoint breakpoints[16];
    bool should_fork;
    uint64_t last_tb;
    int32_t pending_intr;
    uint64_t taint1;
    uint64_t taint2;
    finalized_decision finalized_decisions[32];
    int32_t fdec_idx;
    finalized_io finalized_io[32];
    int32_t fio_idx;
    uint8_t archname;


} SynthController;

extern SynthController* cur_sc;

void synth_controller_init(void);
void synth_controller_cleanup(void);

// all of these use symbolic_reg

void wait_for_decision(void);

symbolic_val fresh_symbol(void);

void handle_sc_breakpoint(uint64_t bp_pc);

uint64_t sc_get_pc(void);

uint64_t sc_get_reg(uint32_t regnum);

void do_fork(void);

//uint32_t get_archname(void);
CallStackFrameList* get_callstack(uint64_t num_frames);



#endif /* SYNTH_CONTROLLER_H */
