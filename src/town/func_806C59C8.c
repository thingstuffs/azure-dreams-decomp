#include "common.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E3C[];
extern u8 D_800190B4[];

s32 func_800169C8(s32 arg0, s32 arg1, s32 arg2)
{
    return func_800182E4(D_80018E3C, D_800190B4, arg0, arg2);
}
