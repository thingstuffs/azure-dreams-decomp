#include "common.h"
#include "town/scene/entry_requests.h"

extern s32 func_800182E4(void *, void *, s32, s32);
extern u8 D_80018E34[];
extern u8 D_800190B4[];

/* Call the shared handler with the two fixed tables and supplied values. */
s32 dispatch_scene_request_with_alternate_tables(s32 request, s32 unused, s32 mode)
{
    return func_800182E4(D_80018E34, D_800190B4, request, mode);
}
