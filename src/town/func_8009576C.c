#include "town/player/position_handlers.h"
/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "town/person/effects.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/system.h"

s32 initialize_actor_movement_interaction_action();        
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
#include "town/player.h"

/* Resolves actor movement, handles button 0x40, and starts an action with radial effects at a surface. */
void update_actor_movement_with_radial_effects(s32 object_id, ObjectPosition *object, s32 update_context) {
    s16 update_threshold;
    GameWork *town_state;

    town_state = &g_game_work;
    resolve_collision_axis_order(object);
    store_input_angle((void *)(object_id));
    accelerate_toward_input_keep_speed(object);
    if ((town_state->pressed_buttons) & 0x40) {
        init_sound_threshold_action(object_id, object, update_context);
    }
    update_threshold = query_capped_surface_height(object, &position_query_scratch);
    if (object->z.w.i >= update_threshold) {
        play_overlay_height_sound();
        set_height_and_slope_velocity((object), update_threshold, (struct TownVec * *)(&position_query_scratch));
        spawn_person_radial_effects(object);
        initialize_actor_movement_interaction_action(object_id, object, update_context);
    } else if (town_action_state_flag != 0) {
        play_overlay_height_sound();
        object->velocity_z = 0;
        copy_z_to_collision_motion((object));
        initialize_actor_movement_interaction_action(object_id, object, update_context);
    } else {
        add_vertical_gravity(object);
    }
}
