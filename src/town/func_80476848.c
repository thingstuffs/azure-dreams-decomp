#include "common.h"

extern s32 func_800175B0();
extern s32 func_80019A8C();
extern s32 D_80019BB0;

s32 func_80017848(void) {
    register s32 below_limit ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    D_80019BB0 = 1;
    if (func_800175B0() == 0) {
        goto return_zero;
    }
    below_limit = func_80019A8C() < 0x14;
    if (below_limit != 0) {
return_zero:
        ASM_SCHED_BARRIER();   /* MATCH pin: retail branch polarity depends on it */
        return 0;
    }
    return 1;
}

/* MECHANISM: A $v1-pinned predicate plus conditional ASM_KEEP preserves the retail slti/beq tail.
   Both failures share return_zero; a zero-word ASM_SCHED_BARRIER at that seam blocks the zeroing
   move from hoisting into the first branch delay slot, retaining the 24-byte, $ra-only frame. */
