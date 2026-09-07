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

void func_800A7548(FuncState *arg0, FuncArg1 *arg1, FuncArg2 *arg2) {
    s16 state;
    u16 value;
    u16 one;

    state = arg0->state.signed_value;
    one = 1;
    switch (state) {
    case 0:
        arg0->remaining = 4;
        arg0->counter = 0;
        arg0->state.unsigned_value = arg0->state.unsigned_value + 1;
    case 1:
    value = arg0->counter + 1;
    arg0->counter = value;
    arg2->value_1c = arg2->value_1c + func_800644B8((s32)(value << 16) >> 11);
    arg2->value_1e = arg2->value_1e - func_800644B8(((s16)arg0->counter) << 5);
    value = arg0->remaining - 1;
    arg0->remaining = value;
    if ((s16)value > 0) {
        goto done;
    }
    arg0->state.unsigned_value = arg0->state.unsigned_value + 1;
    goto done;

    case 2:
        goto state_two;
    default:
        goto done;
    }

state_two:
    value = arg0->counter - 1;
    arg0->counter = value;
    if ((s16)value <= 0) {
        arg0->counter = one;
    }
    arg2->value_1c = arg2->value_1c - (func_800644B8(((s16)arg0->counter) << 5) * 2);
    arg2->value_1e = arg2->value_1e + (func_800644B8(((s16)arg0->counter) << 5) * 4);
    arg1->value_14 = arg1->value_14 - 0x20000;
    value = arg2->value_e - 4;
    arg2->value_e = value;
    arg2->value_d = value;
    arg2->value_c = value;
    if ((s16)arg2->value_1c <= 0) {
        ((u16 *)arg0)[-1] = ((u16 *)arg0)[-1] | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }

done:
    arg1->value_8 = arg1->value_8 + arg1->value_14;
}
