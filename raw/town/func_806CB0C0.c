#include "common.h"

extern s32 func_80016CB0(void *, void *, s32, s32);
extern u8 D_8001775C[];
extern u8 D_80017890[];

s32 func_806CB0C0(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80016CB0(D_8001775C, D_80017890, arg0, arg2);
}
