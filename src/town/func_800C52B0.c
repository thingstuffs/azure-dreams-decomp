#include "common.h"

extern s16 D_800FE4A6;
extern s32 func_8008FE78(s16 arg0, s16 arg1);
extern s32 func_800C296C(s32 arg0);

void func_800C2A10(void *arg0) {
    s32 result;
    s32 var_a0;

    result = func_8008FE78(D_800FE4A6, *(s16 *)((s8 *)arg0 + 0x16));
    var_a0 = 1;
    if (result != 0) {
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        var_a0 = 0;
    }
    *(s32 *)((s8 *)arg0 + 0xC) = func_800C296C(var_a0);
}

/* MECHANISM: The object pointer stays live in s0, yielding the retail 0x18 frame and save order.
   Split the first call result from the pinned a0 argument-selection live range.
   ASM_KEEP(result) only in the nonzero arm blocks sltiu folding while li a0,1 fills the beqz slot. */
