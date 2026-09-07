#include "common.h"

extern s16 func_8008C4C8(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D0410;

s16 func_80095BC0(s32 arg0, s32 arg1) {
    return func_8008C4C8(arg0, D_800D0410, arg1);
}
