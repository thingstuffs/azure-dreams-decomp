#include "common.h"

typedef struct S_80096AE0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_80096AE0_0;   /* arg0 in func_80096AE0 */

typedef struct S_80096AE0_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80096AE0_1;   /* arg1 in func_80096AE0 */

typedef struct S_80096AE0_2 {
    u8 pad_00[0x88];
    s16 unk_88;
    s16 unk_8A;
} S_80096AE0_2;   /* arg3 in func_80096AE0 */

typedef struct S_80096AE0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80096AE0_3;   /* arg2 in func_80096AE0 */



extern void func_800419EC(s32, s32);
extern s32 func_80094EA4(void);
extern u8 D_80096384[];

void func_80096AE0(S_80096AE0_0 *arg0, S_80096AE0_1 *arg1, S_80096AE0_3 *arg2, S_80096AE0_2 *arg3)
{
    s32 state;
    u16 countdown;
    u16 value;

    state = arg0->unk_9B;

    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if ((arg0->unk_A2 & 0x10) == 0) {
        goto done;
    }
    arg1->unk_14 = 0;
    if ((arg3->unk_88 - arg3->unk_8A) >= 0x41) {
        func_800419EC(8, 0x10);
        arg0->unk_96 = 0xC;
        goto increment_state;
    }
    arg0->unk_96 = 1;

increment_state:
    arg0->unk_9B = arg0->unk_9B + 1;

state_one:
    arg2->unk_14 = arg2->unk_14 | 0x800;
    arg0->unk_9B = arg0->unk_9B + 1;
    goto done;

state_two:
    countdown = arg0->unk_96 - 1;
    arg0->unk_96 = countdown;
    if (((s32)(countdown << 16) <= 0) &&
        ((value = arg2->unk_14,
          arg2->unk_14 = value & 0xF7FF,
          (value & 0xE000) != 0) ||
         ((func_80094EA4() << 16) != 0))) {
        arg0->unk_8C = D_80096384;
    }

done:
    return;
}

/* MECHANISM: Local joins keep arg0/arg2 live in s0/s1 across the real call,
   producing the 0x20 frame and exact s0/s1/ra save contract. Separate
   countdown/flag live ranges plus short-circuit RMW select retail v0/v1. */
