#include "common.h"

typedef struct S_800C8ABC_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800C8ABC_0;   /* held_arg0 in func_800C8ABC */



extern s32 func_800A48F0();
extern s32 func_800A6D30();
extern s32 func_800C8408(void *record);

/* Roll a chance against the record's stride and, on a win, run the arg2 action. */
s32 func_800C8ABC(void *arg0, s16 arg1, s8 arg2)
{
    s16 held_arg1 = arg1;
    s8 held_arg2 = arg2;
    s32 temp_a0;
    s16 divisor;
    s32 remainder;

    if (func_800C8408(arg0) != 0) {
        return 0;
    }

    temp_a0 = func_800A6D30() & 0xFFFF;
    if (((u8)(((S_800C8ABC_0 *)(arg0))->unk_03)) != 0) {
        divisor = ((u8)(((S_800C8ABC_0 *)(arg0))->unk_03));
        remainder = temp_a0 % divisor;
    } else {
        remainder = 0;
    }
    temp_a0 = held_arg1;
    divisor = temp_a0 / 2;
    if ((remainder < divisor) || (temp_a0 == 0xFF)) {
        if ((s16)func_800A48F0(((S_800C8ABC_0 *)(arg0)), 1, held_arg2) >= 0) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: Pin the three live arguments to retail's s0/s1/s2 roles so the
   0x20 frame and save order match; defer their guarded keeps past the opening
   call for the s2 delay move, and reuse the v0 divisor carrier for arg1/2. */
