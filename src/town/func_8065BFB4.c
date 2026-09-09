#include "common.h"

extern s32 func_80016788();
extern s32 func_80016CB4(s32, s32, s32, s32);

s32 func_8065BFB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 less_than_three;

    if (func_80016CB4(arg0, arg1, arg2, arg3) == 0) {
        goto return_one;
    }
    less_than_three = func_80016788() < 2;
    if (less_than_three != 0) {
        return 0;
    }
return_one:
    return 1;
}
