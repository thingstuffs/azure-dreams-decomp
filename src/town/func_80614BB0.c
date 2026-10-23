#include "common.h"
#include "town/scene/entry_requests.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018E04[];
extern u8 D_8001925C[];

/* Forward two values and the fixed data buffers to func_800181C8. */
s32 dispatch_scene_request_with_fixed_data(s32 request, s32 unused, s32 value)
{
    return func_800181C8(D_80018E04, D_8001925C, request, value);
}
