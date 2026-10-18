#include "common.h"

extern s32 count_nonzero_word_prefix(s32 *a0, s32 a1);
extern s32 func_8004B404(s32 a0);

/* Allocates a 0x104-byte block, stores its address at the looked-up array index, and returns it. */
s32 func_80048FBC(s32 *values, s32 lookup_key)
{
    s32 index = count_nonzero_word_prefix(values, lookup_key);
    s32 value = func_8004B404(0x104);
    values[index] = value;
    return value;
}
