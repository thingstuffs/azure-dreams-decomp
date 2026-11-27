#include "common.h"


#include "town/person/object_setup.h"
#include "sdk/libc.h"
#include "town/person/motion.h"
#include "town/person/state.h"
#include "town/data.h"
extern s16 get_clamped_transform_coordinate(void *object, s32 step_x, s32 step_y);



/* Advance motion, clamp at the facing boundary, and update directional speed. */
void advance_bounded_motion(TownObjectRecord *entity, ObjectPosition *motion, SpriteFrameState *context, s32 check_param)
{
    s32 pos_x;
    s32 step_y;
    s32 angle;
    s32 quadrant;
    s32 speed;
    s32 max_speed;

    if (select_object_setup_path(entity, motion, context) != 0) {
        return;
    }

    pos_x = motion->x.v;
    max_speed = motion->velocity_x;
    pos_x += max_speed;
    speed = motion->y.v;
    step_y = motion->velocity_y;
    speed += step_y;
    motion->x.v = pos_x;
    motion->y.v = speed;
    motion->z.w.i = get_clamped_transform_coordinate(motion, max_speed, step_y);

    angle = 0x400 - entity->heading;
    quadrant = (angle / 0x400) & 3;

    switch (quadrant) {
    case 0:
        if (entity->origin_x + entity->roam_range_x < motion->x.w.i) {
            motion->x.unsigned_parts.integer = ((u16)entity->origin_x) + *(u16 *)&entity->roam_range_x;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    case 1:
        if ((entity->origin_y) + entity->roam_range_y < motion->y.w.i) {
            motion->y.unsigned_parts.integer = (u16)entity->origin_y + *(u16 *)&entity->roam_range_y;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    case 2:
        if (motion->x.w.i < entity->origin_x - entity->roam_range_x) {
            u16 center;
            u16 extent;
            center = ((u16)entity->origin_x);
            extent = *(u16 *)&entity->roam_range_x;
            motion->x.unsigned_parts.integer = center - extent;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    default:
        if (motion->y.w.i < (entity->origin_y) - entity->roam_range_y) {
            u16 center;
            u16 extent;
            center = (u16)entity->origin_y;
            extent = *(u16 *)&entity->roam_range_y;
            motion->y.unsigned_parts.integer = center - extent;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    }

    max_speed = 0x20000;

    speed = motion->velocity_x + town_x_acceleration[quadrant];
    motion->velocity_x = speed;
    speed = abs(speed);
    speed = max_speed < speed;
    if (speed != 0) {
        motion->velocity_x = town_x_speed_limits[quadrant];
    }

    speed = motion->velocity_y + town_y_acceleration[quadrant];
    motion->velocity_y = speed;
    speed = abs(speed);
    speed = max_speed < speed;
    if (speed != 0) {
        motion->velocity_y = town_y_speed_limits[quadrant];
    }
}
