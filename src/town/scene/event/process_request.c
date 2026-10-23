#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001BA0C[];
extern u8 scene_dispatch_context[];

/*
 * Calls apply_entry_position with D_8001BA0C, scene_dispatch_context, request, context and returns
 * its result.
 */
s32 process_request(s32 request, s32 unused, s32 context)
{
    return apply_entry_position(D_8001BA0C, scene_dispatch_context, request, context);
}
