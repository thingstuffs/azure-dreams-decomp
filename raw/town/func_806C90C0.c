#include "common.h"

extern s32 func_80016CB4(void *, void *, s32, s32);
extern u8 D_80017760[];
extern u8 D_800178C0[];

s32 func_806C90C0(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80016CB4(D_80017760, D_800178C0, arg0, arg2);
}
