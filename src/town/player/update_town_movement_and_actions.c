#include "shared/position_query.h"
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_800A5FDC_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5FDC_0;   /* state in update_town_movement_and_actions */


extern s32 scale_random_to_unsigned_halfword_limit();
s32 runtime_estimate_vector_length(s32, s32);
extern void SD_Call();
s32 read_map_cell_at_world_position(s16, s16);
extern s16 input_angle_with_offset();
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
extern void add_a_directional_step_vector_scale_down_exceeds_length_limit();
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
extern void add_hex_20000_s_signed_offset_hex_14();
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void spawn_directional_effects(void *, s32);
struct EntityRec; void initialize_effect_and_adjust_value(void *, struct EntityRec *, s32);
struct EntityRec; s32 compute_height_based_offset(struct EntityRec *);
s32 check_masked_value_in_current_range(s32);
extern int abs(int);

extern s32 D_800A58CC;
extern u8 town_blocked_directions[];
extern s32 town_movement_speed[];


/* Updates town movement, terrain response, facing, and action state from input. */
void update_town_movement_and_actions(u8 *state, EntityRec *table, void *action_context)
{
    u8 *context;
    GameWork *globals;
    s32 random_choice;
    s32 tile_id;
    s32 speed;
    s32 speed_delta;
    s32 sound_interval;
    s32 input_flags;
    s32 turn_angle;
    s16 direction;
    s16 ground_height;

    context = action_context;
    globals = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(table);

    ((S_800A5FDC_0 *)state)->unk_0A.s--;
    if (((S_800A5FDC_0 *)state)->unk_0A.u <= 0) {
        ((S_800A5FDC_0 *)state)->unk_0A.s = scale_random_to_unsigned_halfword_limit(3) + 5;
        random_choice = scale_random_to_unsigned_halfword_limit(2);
        spawn_directional_effects(table, (u16)random_choice + 2);
    }

    input_flags = globals->buttons;
    if (input_flags & 0xF000) {
        store_the_valid_shared_angle_in_offset_hex_10(state);
        direction = input_angle_with_offset(globals->buttons,
                                  globals->view.camera_rotation.parts.viewAngle);
        if (direction != -1) {
            add_a_directional_step_vector_scale_down_exceeds_length_limit(direction, town_movement_speed[0], table);
        }
        random_choice = scale_random_to_unsigned_halfword_limit(1);
        spawn_directional_effects(table, (u16)random_choice);
    } else {
        if (input_flags & 0x10) {
            move_both_components_toward_zero_direction_dependent_steps_clamping_zero(table);
        }
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero(table);
    }

    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(table, ((u8 *)&position_query_scratch));
    if (table->z.w.i >= ground_height) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(table), ground_height, (struct TownVec * *)(((u8 *)&position_query_scratch)));
    } else if (town_blocked_directions[1] != 0) {
        table->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(table));
    } else {
        add_hex_20000_s_signed_offset_hex_14(table);
    }
    tile_id = read_map_cell_at_world_position(view_reference_entity.x.w.i,
                            view_reference_entity.y.w.i);
    if (check_masked_value_in_current_range((u16)tile_id) != 0) {
        table->flags14 -= compute_height_based_offset(table);
    }

    speed = runtime_estimate_vector_length(table->unk_0C,
                          table->unk_10);
    if (town_movement_speed[0] != 0) {
        speed_delta = abs(town_movement_speed[0] - speed);
        sound_interval = (s32)((u32)speed_delta * 7U) / town_movement_speed[0];
        if ((globals->unk_004 % (sound_interval + 2)) == 0) {
            SD_Call(0x60A);
        }
    }

    if (speed == 0) {
        globals->view.camera_rotation.parts.viewAngle =
            (((u16)globals->view.camera_rotation.parts.viewAngle) + 8) & 0xFFF0;
    }

    speed /= 0x10000;
    if (globals->buttons & 4) {
        turn_angle = ((u16)globals->view.camera_rotation.parts.viewAngle) + 0x10;
        globals->view.camera_rotation.parts.viewAngle = turn_angle + speed;
    }
    if (globals->buttons & 8) {
        turn_angle = ((u16)globals->view.camera_rotation.parts.viewAngle) - 0x10;
        globals->view.camera_rotation.parts.viewAngle = turn_angle - speed;
    }

    if ((((s32)globals->pressed_buttons) & 0x10) &&
        (town_blocked_directions[0] == 0)) {
        initialize_effect_and_adjust_value(state, table, (s32)(context));
        return;
    }

    if (((s32)globals->pressed_buttons) & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&D_800A58CC;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
    return;
}
