#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800165E0[];
extern u8 D_800170CC[];

s32 func_80017B70(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80018FC8(D_800165E0, D_800170CC, arg0, arg2);
}
