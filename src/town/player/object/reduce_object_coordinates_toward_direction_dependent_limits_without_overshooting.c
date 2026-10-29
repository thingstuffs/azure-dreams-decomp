#include "common.h"
#include "shared/game_work.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"

typedef struct {
    s32 unk0[3];
    s32 x;
    s32 y;
} TownObject;

extern s16 input_angle_with_offset(s32, s16);

/*
 * For held input, reduces oversized X/Y components by sine/cosine steps scaled by 64 and clamps at
 * direction-dependent limits scaled by 128.
 */
void reduce_object_coordinates_toward_direction_dependent_limits_without_overshooting(TownObject *object) {
    s16 direction;
    s32 y_direction;
    s32 component_x;
    s32 limit_x;
    s32 limit_abs_x;
    s32 current_abs_x;
    s32 current_x;
    s32 step_x;
    s32 clamp_work_x;
    s32 clamp_abs_x;
    s32 clamp_cur;
    s32 component_y;
    s32 limit_y;
    s32 limit_abs_y;
    s32 current_abs_y;
    s32 current_y;
    s32 step_y;
    s32 clamp_work_y;
    s32 clamp_abs_y;

    direction = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);
    if (direction != -1) {
        component_x = rsin(direction);
        current_abs_x = object->x;
        limit_x = component_x << 7;
        limit_abs_x = limit_x;
        limit_abs_x = abs(limit_abs_x);
        current_abs_x = abs(current_abs_x);
        if (limit_abs_x < current_abs_x) {
            component_x = rsin(direction);
            current_x = object->x;
            step_x = component_x << 6;
            if (((current_x < 0) && (step_x < 0)) ||
                ((current_x > 0) && (step_x > 0))) {
                object->x = object->x - step_x;
            }
            clamp_cur = object->x;
            clamp_abs_x = limit_x;
            clamp_abs_x = abs(clamp_abs_x);
            clamp_cur = abs(clamp_cur);
            clamp_work_x = clamp_cur < clamp_abs_x;
            if (clamp_work_x) {
                object->x = limit_x;
            }
            clamp_work_x = (u32)(u16)direction << 16;
        } else {
            clamp_work_x = (u32)(u16)direction << 16;
        }

        y_direction = (s32)clamp_work_x >> 16;
        component_y = rcos(y_direction);
        current_abs_y = object->y;
        limit_y = component_y << 7;
        limit_abs_y = limit_y;
        limit_abs_y = abs(limit_abs_y);
        current_abs_y = abs(current_abs_y);
        if (limit_abs_y < current_abs_y) {
            component_y = rcos(y_direction);
            current_y = object->y;
            step_y = component_y << 6;
            if (((current_y < 0) && (step_y < 0)) ||
                ((current_y > 0) && (step_y > 0))) {
                object->y = object->y - step_y;
            }
            clamp_work_y = object->y;
            clamp_abs_y = limit_y;
            clamp_abs_y = abs(clamp_abs_y);
            clamp_work_y = abs(clamp_work_y);
            clamp_work_y = clamp_work_y < clamp_abs_y;
            if (clamp_work_y) {
                object->y = limit_y;
            }
        }
    }
}
