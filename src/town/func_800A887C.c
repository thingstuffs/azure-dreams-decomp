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
extern s32 runtime_estimate_vector_length();
extern void SD_Call();
extern s32 read_map_cell_at_world_position();
extern s16 input_angle_with_offset();
extern void store_the_valid_shared_angle_in_offset_hex_10();
extern void add_a_directional_step_vector_scale_down_exceeds_length_limit();
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();
extern void add_hex_20000_s_signed_offset_hex_14();
extern void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2();
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
extern void compute_and_clamps_vector_based_adjustment_updates_town();
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
extern void spawn_directional_effects();
extern void initialize_effect_and_adjust_value();
extern s32 compute_height_based_offset();
extern s32 check_masked_value_in_current_range();
extern int abs(int);

extern s32 D_800A58CC;
extern u8 D_800CFCEE[];
extern s32 D_80100E20[];


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
                                  globals->view.viewAngle);
        if (direction != -1) {
            add_a_directional_step_vector_scale_down_exceeds_length_limit(direction, D_80100E20[0], table);
        }
        random_choice = scale_random_to_unsigned_halfword_limit(1);
        spawn_directional_effects(table, (u16)random_choice);
    } else {
        if (input_flags & 0x10) {
            move_both_components_toward_zero_direction_dependent_steps_clamping_zero(table);
        }
        move_both_components_toward_zero_direction_dependent_steps_clamping_zero(table);
    }

    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(table, ((u8 *)&D_800FE488));
    if (table->z.w.i >= ground_height) {
        compute_and_clamps_vector_based_adjustment_updates_town(table, ground_height, ((u8 *)&D_800FE488));
    } else if (D_800CFCEE[1] != 0) {
        table->flags14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(table);
    } else {
        add_hex_20000_s_signed_offset_hex_14(table);
    }
    tile_id = read_map_cell_at_world_position(D_80083780.x.w.i,
                            D_80083780.y.w.i);
    if (check_masked_value_in_current_range((u16)tile_id) != 0) {
        table->flags14 -= compute_height_based_offset(table);
    }

    speed = runtime_estimate_vector_length(table->unk_0C,
                          table->unk_10);
    if (D_80100E20[0] != 0) {
        speed_delta = abs(D_80100E20[0] - speed);
        sound_interval = (s32)((u32)speed_delta * 7U) / D_80100E20[0];
        if ((globals->unk_004 % (sound_interval + 2)) == 0) {
            SD_Call(0x60A);
        }
    }

    if (speed == 0) {
        globals->view.viewAngle =
            (((u16)globals->view.viewAngle) + 8) & 0xFFF0;
    }

    speed /= 0x10000;
    if (globals->buttons & 4) {
        turn_angle = ((u16)globals->view.viewAngle) + 0x10;
        globals->view.viewAngle = turn_angle + speed;
    }
    if (globals->buttons & 8) {
        turn_angle = ((u16)globals->view.viewAngle) - 0x10;
        globals->view.viewAngle = turn_angle - speed;
    }

    if ((((s32)globals->unk_010) & 0x10) &&
        (D_800CFCEE[0] == 0)) {
        initialize_effect_and_adjust_value(state, table, context);
        return;
    }

    if (((s32)globals->unk_010) & 0x100) {
        ((S_800A5FDC_0 *)state)->unk_00 = (s32)&D_800A58CC;
        ((S_800A5FDC_0 *)state)->unk_0A.u = 8;
    }
    return;
}
