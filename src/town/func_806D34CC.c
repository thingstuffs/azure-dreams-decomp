#include "common.h"

extern void * volatile D_80016000;

void func_80016CCC(s32 arg0) {
    s32 value = arg0;
    register s32 quotient ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 mask;
    s32 *word;
    void *object;
    s32 *base;

    if (value == 0) {
        return;
    }
    object = D_80016000;
    if (value < 0) {
        quotient = value + 31;
    } else {
        quotient = value;
    }
    quotient >>= 5;
    word = (s32 *)(quotient << 2);
    quotient <<= 5;
    base = *(s32 **)((s8 *)object + 24);
    quotient = value - quotient;
    word = (s32 *)((s8 *)word + (s32)base);
    mask = (1 << quotient) | *word;
    *word = mask;
}

/* MECHANISM: Frameless leaf; guarded pins preserve retail's a1/v1/a0/v0 roles.
   The quotient is split into byte-offset and remainder phases around the field load.
   The ordered OR expression keeps the mask/result in v0 through the final store. */
