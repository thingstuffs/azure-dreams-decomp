#include "town/player/position_handlers.h"
#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
#include "shared/sprite_frame_state.h"

/* Updates the record and selects a handler based on its computed threshold. */
void update_actor_and_select_ground_handler(s32 context, ObjectPosition *record, SpriteFrameState *action_data) {
    s16 threshold;

    resolve_collision_axis_order(record);
    threshold = query_capped_surface_height(record, &position_query_scratch);
    if (record->z.w.i >= threshold) {
        set_height_and_slope_velocity((record), threshold, (struct TownVec * *)(&position_query_scratch));
        start_ground_motion_adjust(context, record, action_data);
        return;
    }
    add_vertical_gravity(record);
}
