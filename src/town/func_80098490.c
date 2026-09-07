#include "common.h"

extern s16 func_8008C570(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D0414;

s16 func_80095BF0(s32 arg0, s32 arg1) {
    return func_8008C570(arg0, D_800D0414, arg1);
}
