#include "common.h"

extern s32 func_80018044(void *, void *, s32, s32);
extern u8 D_80018B20[];
extern u8 D_80018E34[];

s32 func_80016968(s32 arg0, s32 arg1, s32 arg2)
{
    return func_80018044(D_80018B20, D_80018E34, arg0, arg2);
}
