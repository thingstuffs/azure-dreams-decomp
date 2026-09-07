#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_800814A0;

void func_80020488(void *arg0) {
    s16 state;
    void *entity;

    state = FIELD(arg0, s16, 0);
    entity = FIELD(arg0, void *, 0xC);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    if (FIELD(entity, s16, 0x36) == 0xFF) {
        FIELD(arg0, u16, 0x1C) &= 0xFFFD;
        FIELD(arg0, u16, 0)++;
    }
    goto done;

state_one:
    if (FIELD(entity, u16, 0x2A) & 1) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    ASM_SCHED_BARRIER();
}

/* MECHANISM: Frameless leaf with an explicit dispatch, state 0 before state 1, and a shared return.
   A zero-word scheduling barrier preserves the common epilogue; width-accurate fields keep RMW order. */
