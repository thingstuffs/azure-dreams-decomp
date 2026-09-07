#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

s32 func_800352FC(void);
s32 func_800C2AB4(void *);

void func_800BDE7C(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    s32 *source;

    state = FIELD(arg0, s16, 0x68);
    source = FIELD(arg0, s32 *, 0xA0);

    if (state == 1) {
        goto state_1_or_3;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_1_or_3;
    }
    goto done;

state_0:
    if (func_800352FC() == 0) {
        goto done;
    }
    if (func_800C2AB4(arg0) == 0) {
        goto done;
    }
    FIELD(arg2, s32, 8) = source[1];
    goto increment;

state_1_or_3:
    if ((func_800352FC() == 0) || (func_800C2AB4(arg0) == 0)) {
        FIELD(arg0, u16, 0x68) = (FIELD(arg0, u16, 0x68) + 1) & 3;
    }
    goto done;

state_2:
    if (func_800352FC() == 0) {
        goto done;
    }
    if (func_800C2AB4(arg0) == 0) {
        goto done;
    }
    FIELD(arg2, s32, 8) = source[0];

increment:
    FIELD(arg0, u16, 0x68) = FIELD(arg0, u16, 0x68) + 1;

done:
    return;
}

/* MECHANISM: The third ABI argument is kept live in s2, with arg0/source held in s0/s1,
   producing the retail 0x20 frame and save order. Explicit state labels preserve the
   retail dispatch and shared increment blocks; state 1/3 alone applies the modulo mask. */
