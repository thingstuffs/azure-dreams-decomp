#include "common.h"

s32 func_8001ADE0();

s32 func_80019CD8(s16 *arg0) {
    s16 *var_s0;
    s32 temp_v0;
    u16 var_a0;

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s0 = arg0;
    temp_v0 = *(u16 *)var_s0;
    
    var_a0 = temp_v0;
    if (temp_v0 != 0) {
loop_1:
        if (func_8001ADE0((s16)var_a0) != 0) {
            var_s0++;
            var_a0 = *(u16 *)var_s0;
            ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            if (*var_s0 != 0) {
                goto loop_1;
            }
        }
    }
    return *var_s0 == 0;
}

/* MECHANISM: The 24-byte frame holds only s0 as the cursor; a guarded s32 v0 pin
   preserves the initial lhu/beq delay-slot copy without a narrowing andi.
   A memory-clobber fence forces the post-increment s16 test to reload with lh. */
