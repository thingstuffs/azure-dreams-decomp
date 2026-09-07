#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80047784(void *, u8, s32);
extern void func_800478B8(void *);
extern s16 D_80083228;
extern u8 D_80176460[8];

void func_8017573C(void *arg0, s32 arg1, void *arg2) {
    s32 index;
    s16 state;
    u16 state_u;
    u16 value;

    FIELD(arg0, u16, 2) = FIELD(arg0, u16, 2) + 1;
    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        index = D_80083228;
        index += FIELD(arg0, s16, 4);
        index += 0x100;
        index >>= 9;
        index &= 7;
        func_80047784(arg2, D_80176460[index], 0);
    }

    state = FIELD(arg0, s16, 0);
    state_u = FIELD(arg0, u16, 0);
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto done;
    }
    if (state != 0) {
        goto done;
    }
    if (FIELD(arg0, s16, 2) < 8) {
        goto done;
    }
    FIELD(arg0, u16, 0) = state_u + 1;
    goto done;

state_one:
    value = FIELD(arg2, u16, 0x1E) + 0x100;
    FIELD(arg2, u16, 0x1E) = value;
    FIELD(arg2, u16, 0x1C) = value;
    if ((u16)value >= 0x1000U) {
        goto clamp;
    }
    if (FIELD(arg2, u16, 0x1E) < 0x1000U) {
        goto done;
    }

clamp:
    FIELD(arg2, u16, 0x1E) = 0x1000;
    FIELD(arg2, u16, 0x1C) = 0x1000;
    FIELD(arg0, u16, 0) = FIELD(arg0, u16, 0) + 1;

done:
    return;
}

/* MECHANISM: The true-space three-argument ABI holds arg0 in s1 and arg2 in s0,
   while the rowbase-local tail is represented by the shared C epilogue.
   A named s32 index with statement-wise RMW updates preserves retail's v1 live
   range; the established s16 scalar and u8[8] table reproduce the load widths. */
