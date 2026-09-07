#include "common.h"

extern s16 func_8008C610(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D0418;

s16 func_80095C20(s32 arg0, s32 arg1) {
    return func_8008C610(arg0, D_800D0418, arg1);
}
