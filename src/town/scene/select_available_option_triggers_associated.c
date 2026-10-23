#include "common.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018F9C[];
extern u8 scene_request_context[];

/*
 * Calls func_800181C8 with D_80018F9C, scene_request_context, request, parameter and returns its
 * result.
 */
s32 select_available_option_triggers_associated(s32 request, s32 unused, s32 parameter)
{
    return func_800181C8(D_80018F9C, scene_request_context, request, parameter);
}
