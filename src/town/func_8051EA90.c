#include "common.h"

extern s32 D_80019178[];

/* Increment the counter and report whether it has reached three. */
s32 func_8051EA90(void) {
    s32 count;

    count = D_80019178[0] + 1;
    D_80019178[0] = count;
    return count >= 3;
}
