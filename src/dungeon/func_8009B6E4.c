#include "common.h"

extern s32 func_800A6D30(s32, s32, s32, s32);
extern s16 D_80083466[];

void func_800A0E44(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_80083466[0] = func_800A6D30(arg0, arg1, arg2, arg3) & 0xF;
}
