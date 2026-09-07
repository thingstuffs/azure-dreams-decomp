#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_800A7A7C(s32, s32, s32, void *, void *);
extern s32 D_8006E240;
extern s32 D_800814A0;

void func_800B80D8(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s32 velocity;
    u16 counter;
    u16 pos;

    state = FIELD(arg0, s16, 0xA2);
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto exit;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto exit;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto zero_continue;
    }
    FIELD(arg0, u16, 0xA2) = 2;
    goto exit;

zero_continue:
    FIELD(arg0, u16, 0xA4) = 12;
    FIELD(arg0, u16, 0xA2)++;
state_one:
    velocity = FIELD(arg1, s32, 0x14) + 0x30000;
    FIELD(arg1, s32, 0x14) = velocity;
    FIELD(arg1, s32, 8) += velocity;
    pos = FIELD(arg2, u16, 0x1C);
    if (pos < 0x1000) {
        FIELD(arg2, u16, 0x1C) = pos + 0x50;
        FIELD(arg2, u16, 0x1E) += 0x50;
    }
    counter = FIELD(arg0, u16, 0xA4) - 1;
    FIELD(arg0, u16, 0xA4) = counter;
    if ((counter << 16) != 0) {
        goto exit;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, u16, 0xA2)++;
    goto exit;

state_two:
    func_800A7A7C(FIELD(arg0, s16, 0xB0),
                  FIELD(arg0, s16, 0xB2),
                  (s16)(FIELD(arg1, u16, 0xA) - 0x20),
                  &D_8006E240,
                  (u8 *)arg0 + 0x98);
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

exit:
    return;
}

/* MECHANISM: true-space local jumps are C returns to one shared epilogue.
   A 0x20 frame holds only arg0 in s0 across the one real five-argument call;
   arg1 naturally occupies a3, and phase-one is a labeled fallthrough join. */
