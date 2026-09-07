#include "common.h"

extern s32 func_80016D10(void *, void *, s32, s32);
extern u8 D_8001795C[];
extern u8 D_80017A94[];

s32 func_8054F9D4(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80016D10(D_8001795C, D_80017A94, arg0, arg2);
}
