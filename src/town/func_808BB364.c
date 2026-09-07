#include "common.h"

extern s32 func_800006C4(s32);
extern s32 func_80000754(s32);
extern s32 func_80000858(s32, s32);

extern s32 D_00000F08[3];
extern s32 D_00000F4C[3];
extern s32 D_00001028[3];

s32 func_808BB364(void) {
    s32 index;
    s32 value;

    func_80000754(1);
    index = D_00000F08[0];
    value = D_00000F4C[index * 4];
    func_80000858(index, 1);
    func_800006C4(1);
    return value + D_00001028[0];
}

/* MECHANISM: The three low absolute-address objects are declared as arrays so
   GCC emits the retail hi/lo address sequences instead of zero-based short loads.
   The indexed table value stays live in the sole saved register across both calls. */
