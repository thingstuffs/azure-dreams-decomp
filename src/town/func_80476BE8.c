#include "common.h"

extern s32 func_80017BE0(s32);
extern s32 D_800166F8[];
extern s32 D_80016718[];
extern s32 D_80016738;
extern s32 D_80019BB4;

s32 func_80017BE8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 1) {
        return func_80017BE0(D_80019BB4);
    }
    if (D_80016738 == 0) {
        s32 *table = D_800166F8;

        D_80016738 = 1;
        return table[D_80019BB4];
    }
    {
        s32 *table = D_80016718;
        return table[D_80019BB4];
    }
}

/* MECHANISM: Three-argument ABI places the selector in $a2 and shared constant 1 in $a0.
   A zero-test plus arm-scoped table pointers gives retail polarity and tail merging.
   The zero-arm store precedes its index read; the lone frame save is $ra. */
