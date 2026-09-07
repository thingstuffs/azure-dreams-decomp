#include "common.h"

extern void * volatile D_80016000;

void func_80016CCC(s32 arg0) {
    register s32 value ASM_REG("$5") = arg0;
    register s32 quotient ASM_REG("$3");
    register s32 mask ASM_REG("$2");
    register s32 *word ASM_REG("$4");
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
    ASM_KEEP(value);
    quotient >>= 5;
    ASM_KEEP(quotient);
    word = (s32 *)(quotient << 2);
    ASM_KEEP(word);
    quotient <<= 5;
    ASM_KEEP(quotient);
    base = *(s32 **)((s8 *)object + 24);
    quotient = value - quotient;
    word = (s32 *)((s8 *)word + (s32)base);
    mask = (1 << quotient) | *word;
    ASM_KEEP(mask);
    *word = mask;
}

/* MECHANISM: Frameless leaf; guarded pins preserve retail's a1/v1/a0/v0 roles.
   The quotient is split into byte-offset and remainder phases around the field load.
   The ordered OR expression keeps the mask/result in v0 through the final store. */
