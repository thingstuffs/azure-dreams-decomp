#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_80083460;
extern u8 D_80096384[];

extern void func_80099F04(void *);
extern void func_80099F70(void *);

void func_80097AF8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 flags;
    u16 counter;
    u8 next_state;
    u8 *global_base;

    state = FIELD(arg0, u8, 0x9B);
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
    counter = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = counter;
    if ((counter << 16) > 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0xFFEA0000;
    next_state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = 0;
    goto increment_state;

state_one:
    counter = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = counter;
    if ((FIELD(arg0, u16, 0xA2) & 0x10) == 0) {
        goto done;
    }
    if ((s16)counter < 4) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    next_state = FIELD(arg0, u8, 0x9B);

increment_state:
    next_state++;
    FIELD(arg0, u8, 0x9B) = next_state;
    goto done;

state_two:
    if ((FIELD(arg2, u16, 0x14) & 0x6000) == 0) {
        goto done;
    }
    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, s16, 0xA) != 0) {
        goto done;
    }
    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x200000) {
        FIELD(arg3, s32, 0x1C) = flags & 0xFFDFFFFF;
        FIELD(global_base, u16, 2) |= 0x412;
        func_80099F70(FIELD(arg3, void *, 0x5C));
        func_80099F04(FIELD(arg3, void *, 0x5C));
    }
    FIELD(arg0, void *, 0x8C) = D_80096384;

done:
    return;
}

/* MECHANISM: True-space CFG labels preserve the state-0/state-1/state-2 layout and
   naturally produce the 0x20 frame with arg0/arg3 held in s0/s1. A fresh u8
   next_state live range selects v0; a held D_80083460 base emits addiu a0 plus
   the retail +0xA/+2 fields, closing the one-word displacement cascade. */
