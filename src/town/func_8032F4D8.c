#include "common.h"

s32 func_8001ADE0();

s32 func_80019CD8(s16 *arg0) {
    s16 *var_s0;
    s32 temp_v0;
    u16 var_a0;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_s0 = arg0;
    temp_v0 = *(u16 *)var_s0;
    
    var_a0 = temp_v0;
    if (temp_v0 != 0) {
loop_1:
        if (func_8001ADE0((s16)var_a0) != 0) {
            var_s0++;
            var_a0 = *(u16 *)var_s0;
            ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
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
