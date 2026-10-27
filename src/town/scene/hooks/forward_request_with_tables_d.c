#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/scene/position_entries.h"

extern ScenePositionEntry D_80018E34[];
extern u8 scene_state_dispatch_context[];

/* Call the shared handler with the two fixed tables and supplied values. */
s32 dispatch_scene_alt_tables(void *request, s32 unused, s32 mode)
{
    return func_800182E4(D_80018E34, scene_state_dispatch_context, request, mode);
}
