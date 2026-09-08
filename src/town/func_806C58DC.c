#include "common.h"

extern s32 D_80018E2C;
extern s32 D_800190B4;

s32 func_800182E4();
s32 func_80018D6C();

// Returns func_800182E4's result when func_80018D6C(0xFDD) is nonzero, otherwise zero.
s32 func_800168DC(s32 firstInput, s32 unusedInput, s32 secondInput) {
    s32 result;

    if (func_80018D6C(0xFDD) != 0) {
        result = func_800182E4(&D_80018E2C, &D_800190B4, firstInput, secondInput);
    } else {
        result = 0;
    }
    return result;
}
