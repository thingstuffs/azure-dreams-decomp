#include "common.h"

extern s32 D_800287CC[];
/* Returns whether the first entry in D_800287CC is nonzero. */
s32 func_8002190C(void) {
    return *D_800287CC != 0;
}
