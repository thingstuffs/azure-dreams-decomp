#ifndef SLUS_OWNED_800448BC_H
#define SLUS_OWNED_800448BC_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

typedef struct {
    u8 a;
    u8 b;
    u8 pad2;
    u8 pad3;
} S_80081508;

extern S_80081508 *D_80081508;

/* Returns whether the terminated record array contains both input values truncated to 16 bits. */

s32 hasRuntimeKeyPair(s32 first_value, s32 second_value);

#endif
