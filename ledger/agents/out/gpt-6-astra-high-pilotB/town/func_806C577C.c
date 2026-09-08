#include "common.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E14[];
extern u8 D_800190B4[];

/* Passes the fixed data buffers and two values to func_800182E4. */
s32 func_8001677C(s32 first_value, s32 unused, s32 second_value)
{
    return func_800182E4(D_80018E14, D_800190B4, first_value, second_value);
}
