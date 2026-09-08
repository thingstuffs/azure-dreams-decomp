#include "common.h"

extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8017405C(void *, s32, s32, void *);
extern u16 D_80083462;

s32 func_80175C94(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 held_arg1 = arg1;
    s32 held_arg2 = arg2;
    register s32 held_arg3 ASM_REG("$19") = arg3;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *held_arg0 = arg0;
    s32 zero_case_value;
    s32 tail_return;
    s16 result;
    s32 shifted_arg3;

    result = func_800ADDA0(held_arg1, held_arg2, held_arg0, 3, 6,
                           (u8 *)held_arg0 + 0x9C);
    ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (result < 0) {
        goto return_zero;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    shifted_arg3 = held_arg3 << 16;
    ASM_KEEP(held_arg3);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (shifted_arg3 != 0) {
        goto call_block;
    }
    zero_case_value = 0xE;
    if (result == 0) {
        goto zero_block;
    }
    if (result == 2) {
        goto call_block;
    }
    goto tail_block;

zero_block:
    *((s8 *)held_arg0 + 0x9A) = zero_case_value;
    func_800A9A0C(held_arg0);
    goto return_zero;

call_block:
    func_8017405C(held_arg0, held_arg1, held_arg2, held_arg0);
    goto return_zero;

tail_block:
    *((u8 *)held_arg0 + 0x71) &= 0x7F;
    if (D_80083462 & 8) {
        tail_return = 0;
        goto clear_halfword;
    }
    return 1;

clear_halfword:
    *(u16 *)((u8 *)held_arg0 + 0x46) &= 0x7FFF;
    return tail_return;

return_zero:
    return 0;
}

/* MECHANISM: Guarded holds encode the s1/s2/s3/s0 captures and exact 0x30 frame.
   True-space labels restore the zero, call, tail, and shared-return block order.
   Schedule seams plus path-local v0 values place li 14 and tail zero in delay slots;
   keeping tail zero live makes the halfword RMW use v1 and closes at 2.7.2-G0. */
