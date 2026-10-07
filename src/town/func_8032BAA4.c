#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK D_8001DCD4;
extern M2C_UNK D_8001DF1B;

/* Pick one of two global records by the selector. */
M2C_UNK *func_800162A4(s32 unused_a, s32 unused_b, s32 selector) {
    if (selector == 1) {
        return &D_8001DF1B;
        }
        return &D_8001DCD4;
    }
