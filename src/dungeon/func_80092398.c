#include "common.h"

typedef struct S_80097AF8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_80097AF8_0;   /* arg0 in func_80097AF8 */

typedef struct S_80097AF8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80097AF8_1;   /* arg1 in func_80097AF8 */

typedef struct S_80097AF8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80097AF8_2;   /* arg2 in func_80097AF8 */

typedef struct S_80097AF8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_80097AF8_3;   /* global_base in func_80097AF8 */

typedef struct S_80097AF8_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_80097AF8_4;   /* arg3 in func_80097AF8 */



extern s32 D_80083460;
extern u8 D_80096384[];

extern void func_80099F04(void *);
extern void func_80099F70(void *);

void func_80097AF8(S_80097AF8_0 *arg0, S_80097AF8_1 *arg1, S_80097AF8_2 *arg2, S_80097AF8_4 *arg3)
{
    s32 state;
    s32 flags;
    u16 counter;
    u8 next_state;
    u8 *global_base;

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
    counter = arg0->unk_96 - 1;
    arg0->unk_96 = counter;
    if ((counter << 16) > 0) {
        goto done;
    }
    arg1->unk_14 = 0xFFEA0000;
    next_state = arg0->unk_9B;
    arg0->unk_96 = 0;
    goto increment_state;

state_one:
    counter = arg0->unk_96 + 1;
    arg0->unk_96 = counter;
    if ((arg0->unk_A2 & 0x10) == 0) {
        goto done;
    }
    if ((s16)counter < 4) {
        goto done;
    }
    arg1->unk_14 = 0;
    next_state = arg0->unk_9B;

increment_state:
    next_state++;
    arg0->unk_9B = next_state;
    goto done;

state_two:
    if ((arg2->unk_14 & 0x6000) == 0) {
        goto done;
    }
    global_base = (u8 *)&D_80083460;
    if (((S_80097AF8_3 *)global_base)->unk_0A != 0) {
        goto done;
    }
    flags = arg3->unk_1C;
    if (flags & 0x200000) {
        arg3->unk_1C = flags & 0xFFDFFFFF;
        ((S_80097AF8_3 *)global_base)->unk_02 |= 0x412;
        func_80099F70(arg3->unk_5C);
        func_80099F04(arg3->unk_5C);
    }
    arg0->unk_8C = D_80096384;

done:
    return;
}

/* MECHANISM: True-space CFG labels preserve the state-0/state-1/state-2 layout and
   naturally produce the 0x20 frame with arg0/arg3 held in s0/s1. A fresh u8
   next_state live range selects v0; a held D_80083460 base emits addiu a0 plus
   the retail +0xA/+2 fields, closing the one-word displacement cascade. */
