#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800165E0[];
extern u8 D_800170CC[];

/* Forward the input values to func_80018FC8 with D_800165E0 and D_800170CC. */
s32 func_8047B370(s32 input_value, s32 unused, s32 extra_value)
{
    return func_80018FC8(D_800165E0, D_800170CC, input_value, extra_value);
}
