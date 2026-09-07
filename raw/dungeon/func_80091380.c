#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_800419EC(s32, s32);
extern s32 func_80094EA4(void);
extern u8 D_80096384[];

void func_80096AE0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    u16 countdown;
    u16 value;

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
    if ((FIELD(arg0, u16, 0xA2) & 0x10) == 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    if ((FIELD(arg3, s16, 0x88) - FIELD(arg3, s16, 0x8A)) >= 0x41) {
        func_800419EC(8, 0x10);
        FIELD(arg0, u16, 0x96) = 0xC;
        goto increment_state;
    }
    FIELD(arg0, u16, 0x96) = 1;

increment_state:
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;

state_one:
    FIELD(arg2, u16, 0x14) = FIELD(arg2, u16, 0x14) | 0x800;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    goto done;

state_two:
    countdown = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = countdown;
    if (((s32)(countdown << 16) <= 0) &&
        ((value = FIELD(arg2, u16, 0x14),
          FIELD(arg2, u16, 0x14) = value & 0xF7FF,
          (value & 0xE000) != 0) ||
         ((func_80094EA4() << 16) != 0))) {
        FIELD(arg0, u8 *, 0x8C) = D_80096384;
    }

done:
    return;
}

/* MECHANISM: Local joins keep arg0/arg2 live in s0/s1 across the real call,
   producing the 0x20 frame and exact s0/s1/ra save contract. Separate
   countdown/flag live ranges plus short-circuit RMW select retail v0/v1. */
