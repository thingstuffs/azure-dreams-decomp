#include "common.h"

extern s32 D_8001673C[];
extern s32 D_80016754[];
extern s32 D_800170CC[];
extern s32 D_80019BB4[3];

extern s32 func_80018FC8(s32 *, s32 *, s32, s32);

s32 func_80017CC0(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret;

    if (arg2 != 1) {
        ret = func_80018FC8(D_8001673C, D_800170CC, arg0, arg2);
    } else {
        ret = D_80016754[D_80019BB4[0]];
    }
    return ret;
}

/* MECHANISM: The true-space three-argument definition holds the fourth call
   argument in a3 while a2 receives arg0; both arms join one return value. Wide array
   declarations force the retail hi/lo indexed-global addressing. */
