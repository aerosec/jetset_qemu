/*
 * synth controller stuff
 */

#include "qemu/osdep.h"
#include "qemu-common.h"
#include "exec/synth_controller.h"
#include "qapi/qapi-events-misc.h" 
#include "hw/boards.h"


void synth_controller_init(void)
{
  SynthController* sc;
  sc = malloc(sizeof(SynthController));
  sc->shadow_seg_tbl = calloc(NB_SEG_TBL_ENTRIES, 8);
  sc->shadow_regs = calloc(MAX_NB_TCG_REGS, TCG_REG_SIZE);
  sc->id = 0;
  sc->decision_ready = false;
  sc->symbol_idx = 1;
  symbolic_reg dst = {.val = 0, .taint = 0};
  sc->dst = dst;
  symbolic_reg arg0 = {.val = 0, .taint = 0};
  symbolic_reg arg1 = {.val = 0, .taint = 0};
  sc->arg0 = arg0;
  sc->arg1 = arg1;
  sc->taint_ctr = 0;
  symbolic_reg s = {.val = 0, .taint = 0};
  sc->pending_mmio_read = s;
  sc->active_bp_count = 0;
  sc->should_fork = false;
  sc->last_tb = 0;
  sc->pending_intr = 0;
  sc->fdec_idx = 0;
  sc->fio_idx = 0;
  cur_sc = sc;
}

void synth_controller_cleanup(void)
{
	uint64_t idx0, idx1;
    for(idx0=0; idx0 < NB_SEG_TBL_ENTRIES; idx0++)
    {
        if (cur_sc->shadow_seg_tbl[idx0] != NULL){
        	for(idx1=0; idx1 < NB_SEG_TBL_ENTRIES; idx1++){
        		if (cur_sc->shadow_seg_tbl[idx0][idx1] != NULL){
        			free(cur_sc->shadow_seg_tbl[idx0][idx1]);
        		}
        	}
        }
    }
    free(cur_sc->shadow_seg_tbl);
    free(cur_sc->shadow_regs);
    free(cur_sc);
}

void do_fork(void)
{   
    pid_t child_pid = fork();
    volatile bool suspended = true;
    if (!child_pid) {
        /* Child Process */
        qapi_event_send_sc_forked(getpid());
        while(suspended){}
        return;
    }
    /* Parent */
    qapi_event_send_sc_forked(getpid());
    
}


void wait_for_decision(void)
{
    while(cur_sc->decision_ready == false){}
}

inline symbolic_val fresh_symbol(void)
{
    return cur_sc->symbol_idx++;
}

// #ifdef PAPER_EVAL
extern uint64_t tbs_execed;
// #endif
inline void handle_sc_breakpoint(uint64_t bp_pc) {
  ScBreakpoint bp;
  for (uint64_t idx = 0; idx < cur_sc->active_bp_count; idx++) {
    bp = cur_sc->breakpoints[idx];
    if (bp_pc == bp.addr) {
// #ifdef PAPER_EVAL
    //FILE* fptr = fopen("./tbs_execed.txt","a+");
    //fprintf(fptr, "TBS EXECED 0x%lx\n", tbs_execed);
    //fprintf(stderr, "TBS EXECED 0x%lx\n", tbs_execed);
    //fclose(fptr);
// #endif
      // send this many frames of callstack
      CallStackFrameList *callstack = get_callstack(10);
      qapi_event_send_bp_triggered(bp.addr, bp.type, callstack);
    }
  }
}

uint64_t sc_get_pc(void) {
  CPUState *cpu;
  bool cpu_chosen;
  uint64_t pc = 0x41414141; // dummy value

  cpu_chosen = false;
  CPU_FOREACH(cpu) {
    if (cpu_chosen == false) {
      pc = cpu_get_pc(cpu);
      cpu_chosen = true;
    }
  }
  return pc;
}


uint64_t sc_get_reg(uint32_t regnum) {
  CPUState *cpu;
  bool cpu_chosen;
  uint64_t reg = 0x41414141; // dummy value

  cpu_chosen = false;
  CPU_FOREACH(cpu) {
    if (cpu_chosen == false) {
      reg = cpu_get_reg(cpu, regnum);
      cpu_chosen = true;
    }
  }
  return reg;
}

CallStackFrameList* get_callstack(uint64_t num_frames)
{
    int i;
    CallStackFrameList *head = NULL;
    CPUState *cpu, *chosen_cpu;
    chosen_cpu = NULL;
    bool cpu_chosen = false;
    uint64_t fp;
    uint8_t mem_buf[4];

    CPU_FOREACH(cpu) {
        if(cpu_chosen == false){
            chosen_cpu = cpu;
            cpu_chosen = true;
        }
    }
    
    fp = cpu_get_fp(chosen_cpu);
    for (i = 0; i < num_frames && fp != 0; i++) {
        CallStackFrameList *list_item = g_new0(typeof(*list_item), 1);
        CallStackFrame *frame = g_new0(typeof(*frame), 1);

        //1. get ret_addr
        if (cur_sc->archname == ARCHNAME_ARM) {
          cpu_read_stack(chosen_cpu, fp - 4, mem_buf, 4);
        } else {
          cpu_read_stack(chosen_cpu, fp + 4, mem_buf, 4);
        }
        frame->ret_addr = *(uint32_t*)mem_buf;
        frame->ret_addr = cpu_maybe_adjust_addr(chosen_cpu, frame->ret_addr);
        //2. update frame pointer
        if (cur_sc->archname == ARCHNAME_ARM) {
          cpu_read_stack(chosen_cpu, fp - 12, mem_buf, 4);
        } else {
          cpu_read_stack(chosen_cpu, fp, mem_buf, 4);
        }
        fp = *(uint32_t*)mem_buf;

        //3. add to list
        list_item->value = frame;
        list_item->next = head;
        head = list_item;
    }
    return head;
}
