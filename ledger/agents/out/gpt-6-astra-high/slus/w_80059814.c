#include "common.h"

#include "common.h"

#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

typedef struct {
    u8 pad0[0x10];
    u32 value;
    u8 pad14[0x2C];
    s32 remainder;
} S_80059814;

extern u32 D_800869A8[4];

/* Scales the value according to D_800869A8[0], carrying remainders for power-of-two divisors. */
void func_80059814(S_80059814 *state) {
    register u32 scaled_value ASM_REG("$2");   /* MATCH pin: slus-diff */
    register u32 quotient ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    switch (D_800869A8[0]) {
    case 0x30:
        quotient = state->value;
        scaled_value = quotient * 10;
        state->value = scaled_value;
        scaled_value += state->remainder;
        state->value = scaled_value;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient = scaled_value;
        scaled_value &= 3;
        quotient >>= 2;
        break;
    case 0x60:
        quotient = state->value;
        scaled_value = quotient * 5;
        state->value = scaled_value;
        scaled_value += state->remainder;
        state->value = scaled_value;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient = scaled_value;
        scaled_value &= 3;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient >>= 2;
        break;
    case 0xC0:
    case 0xF0:
        scaled_value = state->value;
        scaled_value += state->remainder;
        state->value = scaled_value;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient = scaled_value;
        scaled_value &= 1;
        quotient >>= 1;
        break;
    case 0x120:
    case 0x168:
        state->value = state->value / 3;
        return;
    case 0x1E0:
    case 0x180:
        scaled_value = state->value;
        scaled_value += state->remainder;
        state->value = scaled_value;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient = scaled_value;
        scaled_value &= 3;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient >>= 2;
        break;
    case 0x300:
    case 0x3C0:
        scaled_value = state->value;
        scaled_value += state->remainder;
        state->value = scaled_value;
        ASM_KEEP(scaled_value);   /* MATCH pin: slus-diff */
        quotient = scaled_value;
        scaled_value &= 7;
        quotient >>= 3;
        break;
    default:
        return;
    }

    state->remainder = scaled_value;
    state->value = quotient;
}
