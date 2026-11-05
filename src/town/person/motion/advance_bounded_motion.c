#include "common.h"


#include "town/person/object_setup.h"
#include "sdk/libc.h"
#include "town/person/motion.h"
#include "town/person/state.h"
#include "town/data.h"
extern s16 get_clamped_transform_coordinate(void *object, s32 step_x, s32 step_y);



/* Advance motion, clamp at the facing boundary, and update directional speed. */
void advance_bounded_motion(TownObjectRecord *entity, void *motion_arg, SpriteFrameState *context, s32 check_param)
{
    ObjectPosition *motion = motion_arg;
    s32 pos_x;
    s32 step_y;
    s32 angle;
    s32 quadrant;
    s32 speed;
    s32 max_speed;
    s32 *motion_words;

    if (select_object_setup_path(entity, motion, context) != 0) {
        return;
    }

    motion_words = (s32 *)motion;
    pos_x = motion_words[0];
    max_speed = motion_words[3];
    pos_x += max_speed;
    speed = motion_words[1];
    step_y = motion_words[4];
    speed += step_y;
    motion->x.v = pos_x;
    motion->y.v = speed;
    motion->z.w.i = get_clamped_transform_coordinate(motion, max_speed, step_y);

    angle = 0x400 - entity->heading;
    quadrant = (angle / 0x400) & 3;

    switch (quadrant) {
    case 0:
        if (entity->unk_84 + entity->unk_8C < motion->x.w.i) {
            motion->x.unsigned_parts.integer = ((u16)entity->unk_84) + *(u16 *)&entity->unk_8C;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    case 1:
        if (((s16)entity->unk_86) + entity->unk_8E < motion->y.w.i) {
            motion->y.unsigned_parts.integer = (u16)entity->unk_86 + *(u16 *)&entity->unk_8E;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    case 2:
        if (motion->x.w.i < entity->unk_84 - entity->unk_8C) {
            u16 center;
            u16 extent;
            center = ((u16)entity->unk_84);
            extent = *(u16 *)&entity->unk_8C;
            motion->x.unsigned_parts.integer = center - extent;
            initialize_object_assigns_state_data(entity, motion, context);
            return;
        }
        break;
    default:
        if (motion->y.w.i < ((s16)entity->unk_86) - entity->unk_8E) {
            u16 center;
            u16 extent;
            center = (u16)entity->unk_86;
            extent = *(u16 *)&entity->unk_8E;
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
