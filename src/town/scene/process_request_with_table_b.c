#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001B918[];
extern u8 scene_dispatch_context[];

/*
 * Calls apply_entry_position with D_8001B918, scene_dispatch_context, request, context and returns
 * its result.
 */
s32 process_request_with_table_b_918(s32 request, s32 unused, s32 context)
{
    return apply_entry_position(D_8001B918, scene_dispatch_context, request, context);
}
