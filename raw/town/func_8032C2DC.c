#include "common.h"

extern void func_80016A84(s32, s32, s32);
extern void func_80019DFC(s32 *, s32 *, s32, s32);
extern s32 D_8001B920[];
extern s32 D_8001B964[];
extern s32 D_8001B994[];
extern s32 D_8001C358[];

void func_80016ADC(s32 arg0, s32 arg1, s32 arg2) {
    s32 *ptr;

    if (D_8001B920[0] != 0) {
        ptr = D_8001B994;
    } else {
        ptr = D_8001B964;
    }
    if ((u32)(arg2 - 0x40) < 3U) {
        D_8001B920[0] = 1;
    }
    if (arg2 != 0x3E) {
        func_80019DFC(ptr, D_8001C358, arg0, arg2);
    } else {
        func_80016A84(arg0, arg1, 0x3E);
    }
}
