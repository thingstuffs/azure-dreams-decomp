#include "common.h"

typedef struct {
    u16 pad0;
    u16 count;
} Obj0;

typedef struct {
    u8 pad0[0x14];
    u16 flags14;
    u8 pad16[0x1C - 0x16];
    u16 value1C;
    u16 value1E;
} Obj2;

extern s32 D_800814A0[3];

/* Decrement the countdown, adjust both state values, and flag completion or cancellation. */
void func_80171030(Obj0 *countdown, s32 unused, Obj2 *state)
{
    u16 next_value;

    next_value = countdown->count - 1;
    countdown->count = next_value;
    if ((s16)next_value >= 5) {
        next_value = state->value1E + 0x200;
    } else {
        next_value = state->value1E - 0x200;
    }

    state->value1E = next_value;
    state->value1C = next_value;

    if ((s16)countdown->count <= 0) {
        ((u16 *)countdown)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (state->flags14 & 0x8000) {
        ((u16 *)countdown)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
