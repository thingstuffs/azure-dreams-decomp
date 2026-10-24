#include "script_symbols.h"
#include "shared/town_action_flag.h"
#include "shared/position_query.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 test_resident_bitmap_bit(s32 value);
extern s32 scale_random_to_unsigned_halfword_limit(s32 value);
extern s32 runtime_estimate_vector_length(s32 value, s32 other_value);
extern void submit_object_resource_data(s32 value);
extern void initialize_scene_action_record(void *action_state, void *actor, s32 context);
extern void init_unchanged_action_fallback(void *action_state, void *actor, s32 context);
extern void initialize_motion_action(void *action_state, void *actor, s32 context);
extern void init_threshold_countdown_action(void *action_state, void *actor, s32 context);
extern void initialize_actor_action_state(void *action_state, void *actor, s32 context);
extern void initialize_action_object(void *action_state, void *actor, s32 context);
extern void init_movement_action(void *action_state, void *actor, s32 context);
extern void initialize_action_object_with_counter(void *action_state, void *actor, s32 context);
extern void initialize_actor_movement_interaction_action(void *action_state, void *actor, s32 context);
extern void play_periodic_sound(s16 timer, s32 limit);
extern void store_the_valid_shared_angle_in_offset_hex_10(void *action_state);
extern void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(void *actor);
extern void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(void *actor);
extern s32 select_an_available_entry_matching_direction_returns_status(void *menu_state);
extern s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *action_state, void *menu_state);
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(void *actor, void *map_work);
extern void compute_and_clamps_vector_based_adjustment_updates_town(void *actor, s16 height, void *map_work);
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(void *actor);
extern void spawn_directional_effects(void *actor, s32 value);
extern void initialize_record_and_select_active_data(void *action_state, void *actor, s32 context);
extern s32 town_actor_control;
/* Updates the actor and dispatches town actions from input and interaction state. */
void update_actor_input_and_interaction(void *action_state, void *actor, s32 context)
{
    GameWork *input_state = &g_game_work;
    register s32 saved_context;
    u8 *map_work;
    u8 *menu_state;
    s16 sampled_height;
    u16 timer;
    s32 buttons;
    s32 action_result;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(actor);
    move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(actor);
    map_work = ((u8 *)&position_query_scratch);
    sampled_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, map_work);
    if ((sampled_height - (*((s16 *) (((u8 *) actor) + 0xA)))) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(action_state, actor, context);
            return;
        }
    }
    else
        if (town_action_state_flag == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town(actor, sampled_height, map_work);
        }
    timer = (*((u16 *) (((u8 *) action_state) + 0xA))) - 1;
    *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
    if (((s16) timer) <= 0) {
        timer = scale_random_to_unsigned_halfword_limit(4) + 6;
        *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
        spawn_directional_effects(actor, ((u16) scale_random_to_unsigned_halfword_limit(2)) + 2);
    }
    buttons = input_state->pressed_buttons;
    if (buttons & 0x10) {
        initialize_actor_action_state(action_state, actor, context);
        return;
    }
    if (buttons & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(action_state, &town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(action_state, actor, context);
                return;
            }
            initialize_action_object_with_counter(action_state, actor, context);
            return;
        }
        if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action(action_state, actor, context);
            return;
        }
        return;
    }
    menu_state = (u8 *) (&town_actor_control);
    action_result = select_an_available_entry_matching_direction_returns_status(menu_state);
    if (action_result != 0) {
        if (action_result == (-1)) {
            store_the_valid_shared_angle_in_offset_hex_10(action_state);
            initialize_record_and_select_active_data(action_state, actor, context);
            *((s32 *) (((u8 *) action_state) + 0x2C)) = 0;
            submit_object_resource_data(*((s32 *) (menu_state + 0x10)));
            return;
        }
        init_movement_action(action_state, actor, context);
        return;
    }
    buttons = input_state->buttons;
    if (!(buttons & 0x20)) {
        initialize_motion_action(action_state, actor, context);
        store_the_valid_shared_angle_in_offset_hex_10(action_state);
        call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(actor);
        return;
    }
    if (buttons & 0xF000) {
        timer = (*((u16 *) (((u8 *) action_state) + 0x3E))) - 1;
        *((u16 *) (((u8 *) action_state) + 0x3E)) = timer;
        play_periodic_sound((s16) timer, 8);
        store_the_valid_shared_angle_in_offset_hex_10(action_state);
        call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(actor);
        return;
    }
    action_result = runtime_estimate_vector_length(*((s32 *) (((u8 *) actor) + 0xC)), *((s32 *) (((u8 *) actor) + 0x10)));
    if (action_result > 0xFFFFF) {
        init_unchanged_action_fallback(action_state, actor, context);
        return;
    }
    initialize_scene_action_record(action_state, actor, context);
}
