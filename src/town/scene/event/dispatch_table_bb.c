#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001BB64[];
extern u8 scene_dispatch_context[];

/*
 * Calls apply_entry_position with D_8001BB64, scene_dispatch_context, dispatch_value,
 * dispatch_context and returns its result.
 */
s32 dispatch_through_table_bb_64(s32 dispatch_value, s32 unused, s32 dispatch_context)
{
    return apply_entry_position(D_8001BB64, scene_dispatch_context, dispatch_value, dispatch_context);
}
