#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800169EC[];
extern u8 D_800170D0[];

s32 func_8047BA30(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80018FC8(D_800169EC, D_800170D0, arg0, arg2);
}
