#include "common.h"

extern s32 D_80019BB0[3];

extern s32 func_800175B0(void);
extern s32 func_800198D0(s32 arg0);
extern s32 func_80019A8C(void);

// Resets D_80019BB0[0] and returns whether the paired-ID check or threshold check succeeds.
s32 func_800177D4(void) {
    D_80019BB0[0] = 0;

    if ((func_800198D0(0x145B) != 0) &&
        (func_800198D0(0x146E) == 0)) {
        return 1;
    }

    if ((func_800175B0() != 0) && (func_80019A8C() >= 20)) {
        return 1;
    }

    return 0;
}
