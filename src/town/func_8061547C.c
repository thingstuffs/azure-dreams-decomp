#include "common.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018F9C[];
extern u8 D_8001925C[];

s32 func_80016C7C(s32 arg0, s32 arg1, s32 arg2)
{
    return func_800181C8(D_80018F9C, D_8001925C, arg0, arg2);
}
