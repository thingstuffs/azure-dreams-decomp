#include "common.h"
#include "shared/town_dispatch_object.h"
#include "m2c_compat.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"
#include "town/scene/flags.h"

extern ScenePositionEntry town_map_override_response_entries;
extern u8 town_map_square_flag_override_response;

/* Process the selected entry and return its result or the override pointer. */
s32 select_response_with_override(void *context, s32 unused, s32 entry_id) {
    s32 entry_result;

    entry_result = apply_entry_position(&town_map_override_response_entries, active_scene_dispatch_context, context, entry_id);
    return resolve_entry_flag(&town_map_override_response_entries, context, entry_id) != 0
        ? (s32)&town_map_square_flag_override_response
    : entry_result;
}
