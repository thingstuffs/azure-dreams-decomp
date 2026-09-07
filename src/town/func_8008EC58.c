#include "common.h"

s32 func_8008C3B8(s32 arg0, s32 arg1, s32 arg2) {
    s32 scale;
    s32 first;
    s32 rounded;
    s32 value;

    arg1 = (arg1 << 4) + arg0;
    scale = *(s32 *)arg1;
    first = *(s16 *)arg2;
    if (scale < 0) {
        scale += 4095;
    }
    scale >>= 12;
    first *= scale;
    arg1 = *(s32 *)(arg1 + 4);
    arg2 = *(s16 *)(arg2 + 2);
    rounded = arg1 >> 12;
    if (arg1 < 0) {
        arg1 += 4095;
        rounded = arg1 >> 12;
    }
    arg2 = first + arg2 * rounded;
    value = 0;
    if (arg2 != 0) {
        value = -1;
        if (arg2 >= 0) {
            value = 1;
        }
    }
    return value;
}

/* MECHANISM: Frameless leaf; destructive arg1/arg2 reuse preserves the retail
   record-pointer, second-word, coefficient, and sum lifetimes. Split pinned
   v0 scale/rounded lifetimes plus the v1 first product close the color cycle. */
