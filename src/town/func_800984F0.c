#include "common.h"

extern s16 func_8008C6B8(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D041C;

s16 func_80095C50(s32 arg0, s32 arg1) {
    return func_8008C6B8(arg0, D_800D041C, arg1);
}
