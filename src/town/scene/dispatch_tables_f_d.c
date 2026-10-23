#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800165F8[];
extern u8 scene_pair_dispatch_context[];

/*
 * Calls func_80018FC8 with D_800165F8, scene_pair_dispatch_context, request_value, option_value
 * and returns its result.
 */
s32 dispatch_through_tables_165_f_8_and_170_d_0(s32 request_value, s32 unused, s32 option_value)
{
    return func_80018FC8(D_800165F8, scene_pair_dispatch_context, request_value, option_value);
}
