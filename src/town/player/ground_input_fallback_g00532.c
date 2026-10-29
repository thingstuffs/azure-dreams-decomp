/* G00532: ground input fallback. */
/* Original-file evidence (G00532): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800938A0. */
#include "town/player/ground_input_fallback_g00532.h"
#include "town/player.h"

/* Update the actor against ground height, then dispatch input actions. */
void update_actor_ground_and_input(s32 controller, EntityRec *actor, s32 context) {
    s16 ground_height;
    GameWork *input_state = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(actor);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &position_query_scratch);
    if ((ground_height - actor->z.w.i) >= 4) {
        if (((S_80091000_1 *)(&town_action_state_flag))->unk_00 == 0) {
            initialize_action_object(controller, actor, context);
            return;
        }
    } else {
        if (((S_80091000_1 *)(&town_action_state_flag))->unk_00 == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town(actor, ground_height, &position_query_scratch);
        }
    }
    if ((input_state->pressed_buttons) & 0x10) {
        initialize_actor_action_state(controller, actor, context);
        return;
    }
    if (input_state->buttons & 0xF000) {
        store_the_valid_shared_angle_in_offset_hex_10(controller);
    }
}

/* Updates the value and dispatches follow-up handling if it remains unchanged. */
void update_and_fallback_on_input(s32 *value, S_80091114_1 *context, s32 update_arg) {
    s32 saved_update_arg ;   /* Required for the retail saved-register set and frame layout. */
    s32 previous_value;
    GameWork *state = &g_game_work;

    previous_value = *value;
    update_actor_ground_and_input((s32)value, (EntityRec *)context, update_arg);

    if (previous_value == *value) {
        saved_update_arg = update_arg;
        if (!(state->buttons & 0x20)) {
            initialize_scene_action_record((Rec_func_80094268_arg0 *)value, context, (void *)saved_update_arg);
            return;
        }

        if ((context->unk_0C == 0) &&
            (context->unk_10 == 0)) {
            init_input_action_fallback(value, context, saved_update_arg);
        }
    }
}

/* Calls initialize_scene_action_record if update_actor_ground_and_input leaves the value unchanged and flag 0x20 is clear. */
void update_input_and_fallback_action(s32 *value, s32 input_a, s32 input_b) {
    GameWork *state;
    s32 old_value;

    state = &g_game_work;
    old_value = *value;
    update_actor_ground_and_input((s32)value, (EntityRec *)input_a, input_b);
    if ((old_value == *value) && !(state->buttons & 0x20)) {
        initialize_scene_action_record((Rec_func_80094268_arg0 *)value, (void *)input_a, (void *)input_b);
    }
}
