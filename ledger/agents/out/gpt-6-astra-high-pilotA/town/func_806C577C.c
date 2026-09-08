#include "common.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E14[];
extern u8 D_800190B4[];

/* Forwards two inputs to func_800182E4 with the fixed data tables. */
s32 func_8001677C(s32 primary_input, s32 unused, s32 secondary_input)
{
    return func_800182E4(D_80018E14, D_800190B4, primary_input, secondary_input);
}
