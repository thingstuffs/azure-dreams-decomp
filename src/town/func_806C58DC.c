#include "common.h"

extern s32 D_80018E2C;
extern s32 D_800190B4;

s32 func_800182E4();
s32 func_80018D6C();

s32 func_800168DC(s32 arg0, s32 arg1, s32 arg2) {
    s32 result;

    if (func_80018D6C(0xFDD) != 0) {
        result = func_800182E4(&D_80018E2C, &D_800190B4, arg0, arg2);
    } else {
        result = 0;
    }
    return result;
}
