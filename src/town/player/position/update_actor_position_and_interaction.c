#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/town_handler_entries.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/player/coordinates.h"
#include "engine/script.h"
#include "town/event.h"
#include "town/event/motion.h"
#include "town/player.h"
#include "town/player/position_handlers.h"
#include "town/player/position.h"
#include "town/shop.h"

void submit_object_resource_data();
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);
struct ObjectPosition; void initialize_input_driven_scene_object(s32 * *, struct ObjectPosition *, s32);
void init_radial_effects_action(s32 **record, void *ptr, void *ptr2);
void initialize_busy_checked_countdown_action(TownObjectRecord *record,void *unused,void *setup_value);
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void init_motion_action_callback(s32 record, s32 setup_value, s32 init_value);
#include "records/Rec_func_8009B828_arg0.h"

extern s32 town_actor_control;
extern s32 *town_player_action_callback;


typedef struct S_80092A84_3 {
    u8 pad_00[0x50];
    void * unk_50;
} S_80092A84_3;   /* entity in update_actor_position_and_interaction */

typedef struct S_80092A84_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092A84_4;   /* base in update_actor_position_and_interaction */

/* Updates the actor's position and dispatches town actions from input and interaction state. */
void update_actor_position_and_interaction(TownObjectRecord *actor, ObjectPosition *body, s32 context) {
    GameWork *input_state;
    s32 *position_data;
    s32 *interaction_ctrl;
    s16 position;
    s32 input_flags;
    s32 action_result;
    S_80092A84_3 *entity;
    void *handler;
    S_80092A84_4 *interaction_state;

    input_state = &g_game_work;
    resolve_collision_axis_order(body);
    apply_velocity_friction(body);

    position_data = &position_query_scratch;
    position = query_capped_surface_height(body, position_data);
    if ((position - body->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            init_radial_effects_action(actor, body, context);
            return;
        }
    } else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity((body), position, (struct TownVec * *)(position_data));
    }

    input_flags = (input_state->pressed_buttons);
    if (input_flags & 0x10) {
        initialize_input_driven_scene_object((s32 * *)(actor), (body), context);
        return;
    }
    if (input_flags & 0x40) {
        initialize_busy_checked_countdown_action(actor, body, context);
        return;
    }

    interaction_ctrl = &town_actor_control;
    if ((get_status_active_entry_matching_direction(interaction_ctrl) == -1) && (is_map_state_in_special_range() == 0)) {
        select_entry_by_input_direction(interaction_ctrl);
        store_input_angle(actor);
        dispatch_selected_entry_if_nonzero(movement_action_handler_table, actor, (void *)(context));
        init_motion_action_callback(actor, body, context);

        entity = actor->unk_2C;
        handler = entity->unk_50;
        if ((handler != &update_motion_toward_shared_target) && (handler != &update_motion_toward_town_target)) {
            if (handler != resolve_owner_position_and_dispatch) {
                actor->unk_2C = 0;
            }
        }

        interaction_state = &town_actor_control;
        action_result = select_response_text(interaction_state->unk_10, actor->unk_2C);
        if (action_result != 0) {
            call_script(action_result);
        } else {
            submit_object_resource_data(interaction_state->unk_10);
        }
        town_player_action_callback = (s32 *)&begin_town_actor_interaction;
        return;
    }

    if (input_state->buttons & 0xF000) {
        position = ((u16)actor->unk_3E) - 1;
        actor->unk_3E = position;
        play_periodic_sound(position, 0xC);
        store_input_angle(actor);
        accelerate_toward_input_keep_speed(body);
        return;
    }

    initialize_actor_movement_interaction_action(actor, body, context);
}
