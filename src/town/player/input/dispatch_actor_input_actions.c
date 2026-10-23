#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"


#include "engine/object/test_resident_bitmap_bit_api.h"
extern void submit_object_resource_data();
s32 read_map_cell_at_world_position(s16, s16);
extern void initialize_scene_action_record();
void init_ground_input_fallback(s32 * *, void *, void *);
struct Rec_func_80094268_arg0; void initialize_randomized_object_action(struct Rec_func_80094268_arg0 *, s32, s32);
struct Rec_func_80094268_arg0; void init_periodic_effect_action(struct Rec_func_80094268_arg0 *, s32, s32);
struct Rec_func_80094268_arg0; void init_threshold_countdown_action(struct Rec_func_80094268_arg0 *, void *, void *);
struct Rec_func_80094268_arg0; struct ObjectPosition; void initialize_actor_action_state(struct Rec_func_80094268_arg0 *, struct ObjectPosition *, s32);
void initialize_action_object(s32 * *, void *, void *);
struct Rec_func_80094268_arg0; void init_movement_action(struct Rec_func_80094268_arg0 *, s32, s32);
struct Rec_func_80094268_arg0; void initialize_action_object_with_counter(struct Rec_func_80094268_arg0 *, s32, s32);
void initialize_actor_movement_interaction_action(s32 * *, void *, void *);
void play_periodic_sound(s32, s32);
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
extern void handle_adjust_vector_toward_selected_angle_limit_magnitude();
extern void reduce_object_coordinates_toward_direction_dependent_limits_without_overshooting();
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(s32);
extern void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides();
s32 select_an_available_entry_matching_direction_returns_status(void *);
s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *, void *);
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void initialize_record_and_select_active_data(s32, s32, s32);
s32 check_masked_value_in_current_range(s32);

extern s32 town_actor_control[];


typedef struct S_80091260_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    u8 pad_30[0xE];
    union { u16 u; s16 s; } unk_3E;   /* accessed as both */
} S_80091260_2;   /* arg0 in dispatch_actor_input_actions */

/* Dispatch actor actions from input flags and position checks. */
void dispatch_actor_input_actions(S_80091260_2 *actor, EntityRec *position, s32 context) {
    GameWork *input_state = &g_game_work;
    s32 input_flags;
    s32 action_result;
    s32 tile_id;
    s16 height;
    s16 remaining_count;
    s32 *action_data;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(position);
    move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(position);

    height = select_the_smaller_position_query_result_capped_n_64_writes_associated(position, ((u8 *)&position_query_scratch));
    if ((height - position->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object((s32 * *)(actor), position, (void *)(context));
            return;
        }
    } else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(position), height, (struct TownVec * *)(((u8 *)&position_query_scratch)));
    }

    input_flags = ((s32)input_state->pressed_buttons);
    if (input_flags & 0x10) {
        initialize_actor_action_state((struct Rec_func_80094268_arg0 *)(actor), (struct ObjectPosition *)(position), context);
        return;
    }

    if (input_flags & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(actor, town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action((s32 * *)(actor), position, (void *)(context));
                return;
            } else {
                initialize_action_object_with_counter((struct Rec_func_80094268_arg0 *)(actor), (s32)(position), context);
                return;
            }
        } else if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action((struct Rec_func_80094268_arg0 *)(actor), position, (void *)(context));
            return;
        }
        return;
    }

    action_data = town_actor_control;
    action_result = select_an_available_entry_matching_direction_returns_status(action_data);
    if (action_result != 0) {
        if (action_result == -1) {
            store_the_valid_shared_angle_in_offset_hex_10(actor);
            initialize_record_and_select_active_data((s32)(actor), (s32)(position), context);
            actor->unk_2C = 0;
            submit_object_resource_data(action_data[4]);
            return;
        } else {
            init_movement_action((struct Rec_func_80094268_arg0 *)(actor), (s32)(position), context);
            return;
        }
        return;
    }

    input_flags = input_state->buttons;
    if (input_flags & 0x20) {
        if (actor->unk_16 == 1) {
            tile_id = read_map_cell_at_world_position(position->x.w.i, position->y.w.i);
            if (check_masked_value_in_current_range((u16)tile_id) != 0 &&position->z.v > 0) {
                init_periodic_effect_action((struct Rec_func_80094268_arg0 *)(actor), (s32)(position), context);
                return;
            } else {
                init_ground_input_fallback((s32 * *)(actor), position, (void *)(context));
                return;
            }
        } else {
            initialize_randomized_object_action((struct Rec_func_80094268_arg0 *)(actor), (s32)(position), context);
            store_the_valid_shared_angle_in_offset_hex_10(actor);
            call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58((s32)(position));
            return;
        }
        return;
    }

    if (input_flags & 0xF000) {
        remaining_count = actor->unk_3E.u - 1;
        actor->unk_3E.s = remaining_count;
        play_periodic_sound(remaining_count, 12);
        store_the_valid_shared_angle_in_offset_hex_10(actor);
        handle_adjust_vector_toward_selected_angle_limit_magnitude(position);
        reduce_object_coordinates_toward_direction_dependent_limits_without_overshooting(position);
        return;
    } else {
        initialize_scene_action_record(actor, position, context);
    }
}
