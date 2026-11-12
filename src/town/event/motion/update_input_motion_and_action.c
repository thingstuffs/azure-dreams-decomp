#include "shared/position_query.h"
#include "town/event/mesh_motion.h"
#include "common.h"
#include "town/event/motion_step_data.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "town/player/coordinates.h"
#include "town/event.h"
#include "sdk/libgte.h"
#include "town/event/motion.h"
#include "town/player.h"
#include "town/player/position.h"
struct TownObj;
struct TownVec;

extern void initialize_action_object(void *controller, void *object, s32 update_value);
extern void initialize_record_with_pointer_and_code(void *controller, void *object, s32 update_value);

extern s32 town_saved_motion_pointer;


extern u8 town_event_motion_pair[];

/* Updates input-driven motion and handles object action transitions. */
void update_input_motion_and_action(void *controller, ObjectPosition *object, s32 update_arg) {
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
    angle = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch);
    if (angle - object->z.w.i >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(controller, object, saved_arg);
            town_saved_motion_pointer = 0;
            return;
        }
    } else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(object, angle, &position_query_scratch);
    }

    if (((buttons->pressed_buttons) & 0x40) && town_orbit_radius >= 0x800) {
        initialize_record_with_pointer_and_code(controller, object, saved_arg);
        town_saved_motion_pointer = 0;
        return;
    }

    if (buttons->buttons & 0x2000) {
        if (town_motion_x_step < 0x100) {
            town_motion_x_step = (u16)town_motion_x_step + 8;
        } else {
            town_motion_x_step = 0x100;
        }
    }
    if (buttons->buttons & 0x8000) {
        if (town_motion_x_step < -0xFF) {
            town_motion_x_step = -0x100;
        } else {
            town_motion_x_step = (u16)town_motion_x_step - 8;
        }
    }
    if (buttons->buttons & 0x4000) {
        if (town_motion_y_step < 0x100) {
            town_motion_y_step = (u16)town_motion_y_step + 8;
        } else {
            town_motion_y_step = 0x100;
        }
    }
    if (buttons->buttons & 0x1000) {
        if (town_motion_y_step < -0xFF) {
            town_motion_y_step = -0x100;
        } else {
            town_motion_y_step = (u16)town_motion_y_step - 8;
        }
    }

    position = town_event_motion_pair;
    wave = rcos(*(s16 *)(position + 2) - 0x400);
    *(s32 *)position += 0x500000 - (wave << 10);
    rise = town_orbit_radius;
    *(u16 *)((u8 *)controller + 0x10) = *(u16 *)(position + 2);

    if (rise < 0x800) {
        town_orbit_radius = rise + 0x80;
    } else {
        town_orbit_radius = 0x800;
    }
    if (town_mesh_scale < 0x1000) {
        town_mesh_scale = (u16)town_mesh_scale + 0x100;
    } else {
        town_mesh_scale = 0x1000;
    }
    update_positions_from_origin(object);
}
