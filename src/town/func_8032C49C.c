#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001BA2C[];
extern u8 D_8001C354[];

s32 func_80016C9C(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80019DFC(D_8001BA2C, D_8001C354, arg0, arg2);
}
