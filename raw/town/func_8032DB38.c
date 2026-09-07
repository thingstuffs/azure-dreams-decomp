#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001BDBC[];
extern u8 D_8001C358[];

s32 func_80018338(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80019DFC(D_8001BDBC, D_8001C358, arg0, arg2);
}
