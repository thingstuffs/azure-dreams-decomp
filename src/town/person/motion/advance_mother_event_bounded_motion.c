#include "common.h"
#include "shared/entity.h"

extern s16 query_lowered_transform_position();
#include "town/person/object_setup.h"
#include "sdk/libc.h"
#include "town/person/motion.h"
#include "town/person.h"
#include "town/data.h"

/* Advance motion, clamp it to the directional bound, and update velocity. */
void advance_mother_event_bounded_motion(TownObjectRecord *entity, ObjectPosition *motion_state, SpriteFrameState *context)
{
    s32 quadrant;
    s32 angle;
    s32 speed;
    s32 step_x;
    s32 pos_y;

    pos_y = entity->heading;
    angle = 0x400 - pos_y;
    if (angle < 0) {
        angle += 0x3ff;
    }

    {
        s32 pos_x;
        s32 step_y;

        pos_x = motion_state->x.v;
        step_x = motion_state->velocity_x;
        pos_y = motion_state->y.v;
        step_y = motion_state->velocity_y;
        pos_x += step_x;
        pos_y += step_y;
        motion_state->x.v = pos_x;
        quadrant = (angle >> 10) & 3;
        motion_state->y.v = pos_y;
        motion_state->z.w.i = query_lowered_transform_position(motion_state, step_x, step_y, angle);
    }

    if (select_object_setup_path(entity, motion_state, context) != 0) {
        return;
    }

    switch (quadrant) {
    case 0:
        if (((s16)entity->origin_x) + entity->roam_range_x < motion_state->x.w.i) {
            motion_state->x.w.i = entity->origin_x + ((u16)entity->roam_range_x);
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    case 1:
        if (((s16)entity->origin_y) + ((s16)entity->roam_range_y) < motion_state->y.w.i) {
            motion_state->y.w.i = entity->origin_y + entity->roam_range_y;
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    case 2:
        if (motion_state->x.w.i < ((s16)entity->origin_x) - entity->roam_range_x) {
            motion_state->x.w.i = entity->origin_x - ((u16)entity->roam_range_x);
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    default:
        if (motion_state->y.w.i < ((s16)entity->origin_y) - ((s16)entity->roam_range_y)) {
            motion_state->y.w.i = entity->origin_y - entity->roam_range_y;
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    }
    step_x = 0x20000;
    speed = motion_state->velocity_x + town_x_acceleration[quadrant];
    motion_state->velocity_x = speed;
    speed = abs(speed);
    speed = step_x < speed;
    if (speed != 0)
        motion_state->velocity_x = town_x_speed_limits[quadrant];
    speed = motion_state->velocity_y + town_y_acceleration[quadrant];
    motion_state->velocity_y = speed;
    speed = abs(speed);
    speed = step_x < speed;
    if (speed != 0)
        motion_state->velocity_y = town_y_speed_limits[quadrant];
}
