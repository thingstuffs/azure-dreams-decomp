#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800165F8[];
extern u8 D_800170D0[];

/* Forward the input values to func_80018FC8 with D_800165F8 and D_800170D0. */
s32 dispatch_through_tables_165_f_8_and_170_d_0(s32 input_value, s32 unused, s32 extra_value)
{
    return func_80018FC8(D_800165F8, D_800170D0, input_value, extra_value);
}
