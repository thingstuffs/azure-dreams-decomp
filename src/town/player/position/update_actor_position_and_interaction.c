#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/town_handler_entries.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void call_script(s32);
void submit_object_resource_data();
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);
struct ObjectPosition; void initialize_input_driven_scene_object(s32 * *, struct ObjectPosition *, s32);
void initialize_action_callback_from_entry(s32 **record, void *ptr, void *ptr2);
void initialize_busy_checked_countdown_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);
void play_periodic_sound(s32, s32);
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
void handle_adjust_vector_toward_selected_angle_limit_magnitude();
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
s32 select_an_available_entry_matching_direction_returns_status(void *);
s32 get_status_active_entry_matching_direction(void *);
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void init_motion_action_callback(s32 record, s32 setup_value, s32 init_value);
s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41();
s32 select_response_for_source_and_target();
void dispatch_actor_action(void *actor, s32 position, s32 context);
#include "records/Rec_func_8009B828_arg0.h"
void update_motion_toward_shared_target(Rec_func_8009B828_arg0 *state, s32 context, ObjectPosition *motion, s32 transition_arg);
void update_motion_toward_town_target(void *state, s32 context, void *motion, s32 next_arg);
extern u8 town_owner_dispatch_address[];
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
void update_actor_position_and_interaction(Rec_func_80094268_arg0 *actor, EntityRec *body, s32 context) {
    GameWork *input_state;
    u8 *position_data;
    s32 *interaction_ctrl;
    s16 position;
    s32 input_flags;
    s32 action_result;
    S_80092A84_3 *entity;
    void *handler;
    S_80092A84_4 *interaction_state;

    input_state = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(body);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(body);

    position_data = ((u8 *)&position_query_scratch);
    position = select_the_smaller_position_query_result_capped_n_64_writes_associated(body, position_data);
    if ((position - body->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_callback_from_entry(actor, body, context);
            return;
        }
    } else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(body), position, (struct TownVec * *)(position_data));
    }

    input_flags = ((s32)input_state->pressed_buttons);
    if (input_flags & 0x10) {
        initialize_input_driven_scene_object((s32 * *)(actor), (struct ObjectPosition *)(body), context);
        return;
    }
    if (input_flags & 0x40) {
        initialize_busy_checked_countdown_action(actor, body, context);
        return;
    }

    interaction_ctrl = &town_actor_control;
    if ((get_status_active_entry_matching_direction(interaction_ctrl) == -1) && (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0)) {
        select_an_available_entry_matching_direction_returns_status(interaction_ctrl);
        store_the_valid_shared_angle_in_offset_hex_10(actor);
        call_the_handler_selects_nonzero_entry(movement_action_handler_table, actor, (void *)(context));
        init_motion_action_callback(actor, body, context);

        entity = actor->unk_2C;
        handler = entity->unk_50;
        if ((handler != &update_motion_toward_shared_target) && (handler != &update_motion_toward_town_target)) {
            if (handler != town_owner_dispatch_address) {
                actor->unk_2C = 0;
            }
        }

        interaction_state = &town_actor_control;
        action_result = select_response_for_source_and_target(interaction_state->unk_10, actor->unk_2C);
        if (action_result != 0) {
            call_script(action_result);
        } else {
            submit_object_resource_data(interaction_state->unk_10);
        }
        town_player_action_callback = (s32 *)&dispatch_actor_action;
        return;
    }

    if (input_state->buttons & 0xF000) {
        position = actor->unk_3E.as_u16 - 1;
        actor->unk_3E.as_u16 = position;
        play_periodic_sound(position, 0xC);
        store_the_valid_shared_angle_in_offset_hex_10(actor);
        handle_adjust_vector_toward_selected_angle_limit_magnitude(body);
        return;
    }

    initialize_actor_movement_interaction_action(actor, body, context);
}
