#include "town/scene/hooks.h"
#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

/* Apply the position template for the scene choice controlled by flag 20. */
void dispatch_scene_request_with_flag_20_template(struct TownObjectSet *request, s32 unused, s32 value)
{
    ScenePositionTemplate rows = flag_20_choice_position_template;

    apply_entry_position(rows.rows, flag_20_choice_position_flags, request, value);
}
