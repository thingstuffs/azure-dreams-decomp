#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800169EC[];
extern u8 scene_pair_dispatch_context[];

/*
 * Calls func_80018FC8 with D_800169EC, scene_pair_dispatch_context, input_value, extra_value and
 * returns its result.
 */
s32 forward_inputs_with_tables_169ec_170d0_copy(s32 input_value, s32 unused, s32 extra_value)
{
    return func_80018FC8(D_800169EC, scene_pair_dispatch_context, input_value, extra_value);
}
