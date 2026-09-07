#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_801710B8(void *, void *, s32);
extern s32 D_800814A0;

void func_801712C4(void *arg0, void *arg1, s32 arg2)
{
    s32 state;

    state = FIELD(arg0, u8, 0x17);
    FIELD(arg0, u16, 0x32) = FIELD(arg0, u16, 0x32) - 1;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_801710B8(arg0, arg1, arg2);
    func_801710B8(arg0, arg1, arg2);
    if (FIELD(arg0, s16, 0x32) == 0) {
        FIELD(arg0, u16, 0x32) = 0x10;
        FIELD(arg0, s16, 0x34) = 0x10;
        FIELD(arg0, u8, 0x17)++;
    }
    FIELD(arg0, s32, 8) = FIELD(arg0, s32, 0);
    goto done;

state_one:
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x40);
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x44);
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x48);
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x40);
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x44);
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x48);

    FIELD(arg0, s8, 4) =
        (FIELD(arg0, u8, 0) * FIELD(arg0, s16, 0x32)) /
        FIELD(arg0, s16, 0x34);
    FIELD(arg0, s8, 5) =
        (FIELD(arg0, u8, 1) * FIELD(arg0, s16, 0x32)) /
        FIELD(arg0, s16, 0x34);
    FIELD(arg0, s8, 6) =
        (FIELD(arg0, u8, 2) * FIELD(arg0, s16, 0x32)) /
        FIELD(arg0, s16, 0x34);
    FIELD(arg0, s32, 8) = FIELD(arg0, s32, 4);

    if (FIELD(arg0, s16, 0x32) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: The true-space function uses two local epilogue edges, not calls.
   Three arguments stay live in s0/s1/s2 across the zero-state calls; direct
   scalar RMW preserves D_800814A0's retail hi/lo access shape. */
