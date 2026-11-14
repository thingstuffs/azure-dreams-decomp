#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/town_handler_entries.h"
#include "shared/entity.h"
#include "shared/town_object.h"

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */


#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "shared/sprite_frame_state.h"
void init_actor_action_state(TownObjectRecord *record, void *ptr, void *ptr2);



/* Update the entity, handle a large value change, and advance the state countdown. */
void update_ground_timed_action(TownObjectRecord *state, ObjectPosition *entity, SpriteFrameState *context) {
    s16 sampled_value;
    s16 ticks_left;

    resolve_collision_axis_order(entity);
    apply_velocity_friction(entity);
    sampled_value = query_capped_surface_height(entity, &position_query_scratch);
    if ((sampled_value - entity->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(state, entity, context);
            return;
        }
    } else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity((entity), sampled_value, (struct TownVec * *)(&position_query_scratch));
    }
    if (state->unk_0A == 0) {
        dispatch_selected_entry_if_nonzero(D_800D00E0, state, context);
    }
    ticks_left = (u16) state->unk_0A - 1;
    state->unk_0A = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        init_actor_action_state(state, entity, context);
    }
}
