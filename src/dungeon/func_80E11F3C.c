#include "common.h"

typedef struct S_8017573C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
} S_8017573C_0;   /* arg0 in func_8017573C */

typedef struct S_8017573C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8017573C_1;   /* arg2 in func_8017573C */



extern void func_80047784(void *, u8, s32);
extern void func_800478B8(void *);
extern s16 D_80083228;
extern u8 D_80176460[8];

void func_8017573C(S_8017573C_0 *arg0, s32 arg1, S_8017573C_1 *arg2) {
    s32 index;
    s16 state;
    u16 state_u;
    u16 value;

    arg0->unk_02.s = arg0->unk_02.s + 1;
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        index = D_80083228;
        index += arg0->unk_04;
        index += 0x100;
        index >>= 9;
        index &= 7;
        func_80047784(arg2, D_80176460[index], 0);
    }

    state = arg0->unk_00.s;
    state_u = arg0->unk_00.u;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto done;
    }
    if (state != 0) {
        goto done;
    }
    if (arg0->unk_02.u < 8) {
        goto done;
    }
    arg0->unk_00.u = state_u + 1;
    goto done;

state_one:
    value = arg2->unk_1E + 0x100;
    arg2->unk_1E = value;
    arg2->unk_1C = value;
    if ((u16)value >= 0x1000U) {
        goto clamp;
    }
    if (arg2->unk_1E < 0x1000U) {
        goto done;
    }

clamp:
    arg2->unk_1E = 0x1000;
    arg2->unk_1C = 0x1000;
    arg0->unk_00.u = arg0->unk_00.u + 1;

done:
    return;
}

/* MECHANISM: The true-space three-argument ABI holds arg0 in s1 and arg2 in s0,
   while the rowbase-local tail is represented by the shared C epilogue.
   A named s32 index with statement-wise RMW updates preserves retail's v1 live
   range; the established s16 scalar and u8[8] table reproduce the load widths. */
