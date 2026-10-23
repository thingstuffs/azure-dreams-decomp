#include "common.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018F84[];
extern u8 scene_request_context[];

/* Invoke func_800181C8 with D_80018F84 and the shared D_8001925C table. */
s32 forward_request_with_shared_table(s32 request, s32 unused, s32 parameter)
{
    return func_800181C8(D_80018F84, scene_request_context, request, parameter);
}
