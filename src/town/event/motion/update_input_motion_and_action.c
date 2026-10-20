#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"

extern s32 func_80064584(s32 wave_input);
extern void initialize_action_object(void *controller, void *object, s32 update_value);
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(void *record);
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(void *position, void *out_value);
extern void compute_and_clamps_vector_based_adjustment_updates_town(void *obj, s16 base_value, void *vec_ptr);
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(void *position);
extern void update_positions_from_origin(void *origin);
extern void initialize_record_with_pointer_and_code(void *controller, void *object, s32 update_value);

extern s32 D_800D0B14;
extern s16 D_80100D18;
extern s32 D_80100D1C;
extern u8 D_80100D60[];
extern s16 D_80100D80;
extern s16 D_80100D82;

/* Updates input-driven motion and handles object action transitions. */
void update_input_motion_and_action(void *controller, void *object, s32 update_arg) {
    s32 saved_arg;
    GameWork *buttons;
    u8 *position;
    s16 angle;
    s32 wave;
    s32 rise;

    saved_arg = update_arg;
    buttons = &g_game_work;
    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(object);
    angle = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, ((u8 *)&D_800FE488));
    if (angle - *(s16 *)((u8 *)object + 0xA) >= 4) {
        if (D_800CFCEF == 0) {
            initialize_action_object(controller, object, saved_arg);
            D_800D0B14 = 0;
            return;
        }
    } else if (D_800CFCEF == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(object, angle, ((u8 *)&D_800FE488));
    }

    if ((((s32)buttons->pressed_buttons) & 0x40) && D_80100D1C >= 0x800) {
        initialize_record_with_pointer_and_code(controller, object, saved_arg);
        D_800D0B14 = 0;
        return;
    }

    if (buttons->buttons & 0x2000) {
        if (D_80100D80 < 0x100) {
            D_80100D80 = (u16)D_80100D80 + 8;
        } else {
            D_80100D80 = 0x100;
        }
    }
    if (buttons->buttons & 0x8000) {
        if (D_80100D80 < -0xFF) {
            D_80100D80 = -0x100;
        } else {
            D_80100D80 = (u16)D_80100D80 - 8;
        }
    }
    if (buttons->buttons & 0x4000) {
        if (D_80100D82 < 0x100) {
            D_80100D82 = (u16)D_80100D82 + 8;
        } else {
            D_80100D82 = 0x100;
        }
    }
    if (buttons->buttons & 0x1000) {
        if (D_80100D82 < -0xFF) {
            D_80100D82 = -0x100;
        } else {
            D_80100D82 = (u16)D_80100D82 - 8;
        }
    }

    position = D_80100D60;
    wave = func_80064584(*(s16 *)(position + 2) - 0x400);
    *(s32 *)position += 0x500000 - (wave << 10);
    rise = D_80100D1C;
    *(u16 *)((u8 *)controller + 0x10) = *(u16 *)(position + 2);

    if (rise < 0x800) {
        D_80100D1C = rise + 0x80;
    } else {
        D_80100D1C = 0x800;
    }
    if (D_80100D18 < 0x1000) {
        D_80100D18 = (u16)D_80100D18 + 0x100;
    } else {
        D_80100D18 = 0x1000;
    }
    update_positions_from_origin(object);
}
