#include "common.h"

extern void func_80053DA8();
extern void func_800AE4D4();
extern void func_800AF1B4();
extern void func_800B0424();
extern u8 D_80083160[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_800B0490(void *arg0)
{
    s32 direction;
    s32 mode;
    s32 value;
    s32 input;
    s32 new_input;
    s32 flags;
    u8 *state;

    direction = 0;
    mode = direction;
    state = D_80083160;
    input = FIELD(state, s32, 8);
    if (input == 0) {
        goto done;
    }

    flags = FIELD(state, s32, 0x10);
    if (flags & 0x20) {
        func_80053DA8(0x515, state);
        func_800AE4D4(FIELD(arg0, s32, 8));
        goto done;
    }

    if (flags & 0x40) {
        func_80053DA8(0x503, state);
        func_800B0424(arg0);
        goto done;
    }

    if (!(input & 0x5000)) {
        goto done;
    }

    if (flags & 0x4000) {
        FIELD(arg0, s32, 0x10) = 0;
        mode = 4;
        direction = 1;
        goto move;
    }

    if (flags & 0x1000) {
        FIELD(arg0, s32, 0x10) = 0;
        mode = 4;
        direction = -1;
        goto move;
    }

    value = FIELD(arg0, s32, 0x10);
    if (value >= 5) {
        FIELD(arg0, s32, 0x10) = value - 3;
        new_input = FIELD(state, volatile s32, 8);
        if (new_input & 0x4000) {
            direction = 1;
            mode = 4;
            goto move;
        }
        if (new_input & 0x1000) {
            direction = -1;
            mode = 4;
        }
    } else {
        FIELD(arg0, s32, 0x10) = value + 1;
    }

move:
    if (direction == 0) {
        goto done;
    }
    func_80053DA8(0x502, state);
    func_800AF1B4(FIELD(arg0, s32, 4), direction, mode);

done:
    return;
}

/* MECHANISM: A 32-byte frame holds s2=arg0, s0=direction, and s1=mode.
   One held D_80083160 base feeds the pre-call flag CFG; internal targets are
   gotos, not the false func_800B05A0/func_800B05C0 calls from the seed. */
