#include "common.h"

typedef struct {
    u8 pad0[0x10];
    u32 value;
    u8 pad14[0x2C];
    s32 remainder;
} S_80059814;

extern u32 D_800869A8[4];

/* Scales the value according to D_800869A8[0], carrying remainders for power-of-two divisors. */
void func_80059814(S_80059814 *state) {
    switch (D_800869A8[0]) {
    case 0x30: {
        state->value *= 10;
        state->value += state->remainder;
        state->remainder = state->value & 3;
        state->value /= 4;
        break;
    }
    case 0x60: {
        state->value *= 5;
        state->value += state->remainder;
        state->remainder = state->value & 3;
        state->value /= 4;
        break;
    }
    case 0xC0:
    case 0xF0: {
        state->value += state->remainder;
        state->remainder = state->value & 1;
        state->value /= 2;
        break;
    }
    case 0x120:
    case 0x168: {
        state->value /= 3;
        return;
    }
    case 0x1E0:
    case 0x180: {
        state->value += state->remainder;
        state->remainder = state->value & 3;
        state->value /= 4;
        break;
    }
    case 0x300:
    case 0x3C0: {
        state->value += state->remainder;
        state->remainder = state->value & 7;
        state->value /= 8;
        break;
    }
    }
}
