#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/town_handler.h"
#include "town/person/effects.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/position_handlers.h"
#include "town/system.h"
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
#include "shared/sprite_frame_state.h"
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                      /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */

/* Advance the state counter and update the entity, handling threshold and flag transitions. */
void update_threshold_and_interaction(TownObjectRecord *state, ObjectPosition *entity, SpriteFrameState *context) {
    s16 threshold;
    u16 counter;

    counter = ((u16)state->unk_0A) + 1;
    state->unk_0A = counter;
    if ((s16) counter == 6) {
        dispatch_selected_entry_if_nonzero(action_object_handler_table, state, context);
    }
    resolve_collision_axis_order(entity);
    store_input_angle(state);
    accelerate_toward_input_keep_speed(entity);
    threshold = query_capped_surface_height(entity, &position_query_scratch);
    if (entity->z.w.i >= threshold) {
        select_sound_command_from_mode();
        set_height_and_slope_velocity((entity), threshold, (struct TownVec * *)(&position_query_scratch));
        spawn_person_radial_effects(entity);
        initialize_action_object_type_six(state, entity, context);
        return;
    }
    if (town_action_state_flag != 0) {
        select_sound_command_from_mode();
        entity->velocity_z = 0;
        copy_z_to_collision_motion((entity));
        initialize_action_object_type_six(state, entity, context);
        return;
    }
    add_vertical_gravity(entity);
}
