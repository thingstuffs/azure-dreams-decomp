#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001BB64[];
extern u8 scene_dispatch_context[];

/* Dispatch through D_8001BB64 and D_8001C354 and return the result. */
s32 dispatch_through_table_bb_64(s32 dispatch_value, s32 unused, s32 dispatch_context)
{
    return apply_entry_position(D_8001BB64, scene_dispatch_context, dispatch_value, dispatch_context);
}
