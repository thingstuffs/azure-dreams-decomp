#include "common.h"

typedef struct {
    u8 pad_a0[0xA0];
    union {
        s16 signed_value;
        u16 unsigned_value;
    } state;
    u16 pad_a2;
    u16 counter;
    u16 remaining;
} FuncState;

typedef struct {
    u8 pad_8[8];
    s32 value_8;
    u8 pad_14[8];
    s32 value_14;
} FuncArg1;

typedef struct {
    u8 pad_c[0xC];
    u8 value_c;
    u8 value_d;
    u8 value_e;
    u8 pad_f[0xD];
    u16 value_1c;
    u16 value_1e;
} FuncArg2;

extern s32 D_800814A0[3];
extern s32 func_800644B8(s32);

/* Updates a two-phase visual effect's size, brightness, and motion. */
void func_800A7548(FuncState *effect, FuncArg1 *motion, FuncArg2 *visual) {
    s16 phase;
    u16 updated_value;
    u16 min_counter;

    phase = effect->state.signed_value;
    min_counter = 1;
    switch (phase) {
    case 0:
        effect->remaining = 4;
        effect->counter = 0;
        effect->state.unsigned_value = effect->state.unsigned_value + 1;
    case 1:
        updated_value = effect->counter + 1;
        effect->counter = updated_value;
        visual->value_1c = visual->value_1c + func_800644B8((s32)(updated_value << 16) >> 11);
        visual->value_1e = visual->value_1e - func_800644B8(((s16)effect->counter) << 5);
        updated_value = effect->remaining - 1;
        effect->remaining = updated_value;
        if ((s16)updated_value > 0) {
            goto done;
        }
        effect->state.unsigned_value = effect->state.unsigned_value + 1;
        goto done;

    case 2:
        goto state_two;
    default:
        goto done;
    }

state_two:
    updated_value = effect->counter - 1;
    effect->counter = updated_value;
    if ((s16)updated_value <= 0) {
        effect->counter = min_counter;
    }
    visual->value_1c = visual->value_1c - (func_800644B8(((s16)effect->counter) << 5) * 2);
    visual->value_1e = visual->value_1e + (func_800644B8(((s16)effect->counter) << 5) * 4);
    motion->value_14 = motion->value_14 - 0x20000;
    updated_value = visual->value_e - 4;
    visual->value_e = updated_value;
    visual->value_d = updated_value;
    visual->value_c = updated_value;
    if ((s16)visual->value_1c <= 0) {
        ((u16 *)effect)[-1] = ((u16 *)effect)[-1] | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

done:
    motion->value_8 = motion->value_8 + motion->value_14;
}
