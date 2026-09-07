#include "common.h"

extern s8 D_80016000[];

s32 func_80016D78(s32 arg0)
{
    s32 quotient;
    s32 result;
    s32 *base;
    s32 *words;
    s32 word;

    if (arg0 == 0) {
        goto zero;
    }
    if (arg0 == 1) {
        goto one;
    }

    base = *(s32 **)D_80016000;
    quotient = arg0 / 32;
    words = *(s32 **)((s8 *)base + 0x18);
    word = words[quotient];
    result = 1 << (arg0 - quotient * 32);
    result &= word;
    goto done;

one:
    result = 1;
    goto done;

zero:
    result = 0;

done:
    return result;
}

/* MECHANISM: frameless leaf under the TRUE-space name with a shared result join.
   Tail-placed zero/one blocks preserve retail beq polarity and body-first emission.
   A named root pointer holds *D_80016000 across /32; one-read word preserves and order. */
