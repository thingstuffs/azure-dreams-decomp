#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"


extern s32 test_resident_bitmap_bit();
extern void submit_object_resource_data();
extern s32 read_map_cell_at_world_position();
extern void initialize_scene_action_record();
extern void func_80093E58();
extern void initialize_randomized_object_action();
extern void func_80093FC8();
extern void func_80094088();
extern void initialize_actor_action_state();
extern void initialize_action_object();
extern void func_800943B8();
extern void initialize_action_object_with_counter();
extern void initialize_actor_movement_interaction_action();
extern void trigger_event_hex_519_interval_multiples_enabled();
extern void store_the_valid_shared_angle_in_offset_hex_10();
extern void handle_adjust_vector_toward_selected_angle_limit_magnitude();
extern void reduce_object_coordinates_toward_direction_dependent_limits_without_overshooting();
extern void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58();
extern void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides();
extern s32 select_an_available_entry_matching_direction_returns_status();
extern s32 select_an_eligible_source_entry_stores_pointer_in_destination();
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
extern void compute_and_clamps_vector_based_adjustment_updates_town();
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
extern void initialize_record_and_select_active_data();
extern s32 check_masked_value_in_current_range();

extern s32 D_800CFCB4[];
extern u8 D_800CFCEF[];


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

    height = select_the_smaller_position_query_result_capped_n_64_writes_associated(position, ((u8 *)&D_800FE488));
    if ((height - position->z.w.i) >= 4) {
        if (D_800CFCEF[0] == 0) {
            initialize_action_object(actor, position, context);
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(position, height, ((u8 *)&D_800FE488));
    }

    input_flags = ((s32)input_state->unk_010);
    if (input_flags & 0x10) {
        initialize_actor_action_state(actor, position, context);
        return;
    }

    if (input_flags & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(actor, D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(actor, position, context);
                return;
            } else {
                initialize_action_object_with_counter(actor, position, context);
                return;
            }
        } else if (test_resident_bitmap_bit(0xA4) != 0) {
            func_80094088(actor, position, context);
            return;
        }
        return;
    }

    action_data = D_800CFCB4;
    action_result = select_an_available_entry_matching_direction_returns_status(action_data);
    if (action_result != 0) {
        if (action_result == -1) {
            store_the_valid_shared_angle_in_offset_hex_10(actor);
            initialize_record_and_select_active_data(actor, position, context);
            actor->unk_2C = 0;
            submit_object_resource_data(action_data[4]);
            return;
        } else {
            func_800943B8(actor, position, context);
            return;
        }
        return;
    }

    input_flags = input_state->buttons;
    if (input_flags & 0x20) {
        if (actor->unk_16 == 1) {
            tile_id = read_map_cell_at_world_position(position->x.w.i, position->y.w.i);
            if (check_masked_value_in_current_range((u16)tile_id) != 0 &&position->z.v > 0) {
                func_80093FC8(actor, position, context);
                return;
            } else {
                func_80093E58(actor, position, context);
                return;
            }
        } else {
            initialize_randomized_object_action(actor, position, context);
            store_the_valid_shared_angle_in_offset_hex_10(actor);
            call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(position);
            return;
        }
        return;
    }

    if (input_flags & 0xF000) {
        remaining_count = actor->unk_3E.u - 1;
        actor->unk_3E.s = remaining_count;
        trigger_event_hex_519_interval_multiples_enabled(remaining_count, 12);
        store_the_valid_shared_angle_in_offset_hex_10(actor);
        handle_adjust_vector_toward_selected_angle_limit_magnitude(position);
        reduce_object_coordinates_toward_direction_dependent_limits_without_overshooting(position);
        return;
    } else {
        initialize_scene_action_record(actor, position, context);
    }
}
