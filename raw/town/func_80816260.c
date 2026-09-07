#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_800814A0;

void func_80020260(void *arg0) {
    s16 state;
    s32 value_1;
    s32 value_2;
    void *object;

    state = FIELD(arg0, s16, 0);
    object = FIELD(arg0, void *, 4);

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto done;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    goto done;

state_0:
    if (FIELD(object, s16, 0x36) != 0xFF) {
        goto done;
    }
    FIELD(arg0, u16, 0x16) &= 0xFFFD;
    FIELD(arg0, u16, 0)++;
    goto done;

state_1:
    value_1 = FIELD(arg0, s32, 8);
    if (value_1 <= 0x40403F) {
        FIELD(arg0, s32, 8) = value_1 + 0x80808;
    }
    if ((FIELD(object, u16, 0x2A) & 1) == 0) {
        goto done;
    }
    FIELD(arg0, u16, 0)++;
    goto done;

state_2:
    value_2 = FIELD(arg0, s32, 8) + (s32)0xFFF7F7F8;
    FIELD(arg0, s32, 8) = value_2;
    if (value_2 <= 0x80808) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}

/* MECHANISM: Retail is a frameless leaf; 0x80020358 is its local epilogue.
   State labels preserve block order and the jump delay-slot stores.
   Split state-1/state-2 values free $a0 for the object and yield $v1/$v0 roles. */
