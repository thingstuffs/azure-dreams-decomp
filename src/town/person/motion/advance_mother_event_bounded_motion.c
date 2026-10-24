#include "common.h"
#include "shared/entity.h"

typedef struct S_800C7674_0 {
    u8 pad_00[0x72];
    s16 unk_72;
    u8 pad_74[0x10];
    union { s16 s; u16 u; } unk_84;   /* accessed as both */
    union { s16 s; u16 u; } unk_86;   /* accessed as both */
    u8 pad_88[0x4];
    union { s16 s; u16 u; } unk_8C;   /* accessed as both */
    union { s16 s; u16 u; } unk_8E;   /* accessed as both */
} S_800C7674_0;   /* arg0 in advance_mother_event_bounded_motion */


typedef struct Motion {
    s32 pos_x;
    s32 pos_y;
    s16 field_08;
    s16 height;
    s32 step_x;
    s32 step_y;
} Motion;

extern s16 query_lowered_transform_position();
extern s32 select_object_setup_path();
extern void initialize_mother_event_actor();
extern int abs(int);

extern s32 town_x_acceleration[4];
extern s32 town_x_speed_limits[4];
extern s32 town_y_acceleration[4];
extern s32 town_y_speed_limits[4];

/* Advance motion, clamp it to the directional bound, and update velocity. */
void advance_mother_event_bounded_motion(S_800C7674_0 *entity, EntityRec *motion_state, void *context)
{
    s32 quadrant;
    s32 angle;
    s32 speed;
    s32 step_x;
    s32 pos_y;

    pos_y = entity->unk_72;
    angle = 0x400 - pos_y;
    if (angle < 0) {
        angle += 0x3ff;
    }

    {
        Motion *motion;
        s32 pos_x;
        s32 step_y;

        motion = (Motion *)motion_state;
        pos_x = motion->pos_x;
        step_x = motion->step_x;
        pos_y = motion->pos_y;
        step_y = motion->step_y;
        pos_x += step_x;
        pos_y += step_y;
        motion->pos_x = pos_x;
        quadrant = (angle >> 10) & 3;
        motion->pos_y = pos_y;
        motion->height = query_lowered_transform_position(motion, step_x, step_y, angle);
    }

    if (select_object_setup_path(entity, motion_state, context) != 0) {
        return;
    }

    switch (quadrant) {
    case 0:
        if (entity->unk_84.s + entity->unk_8C.s < motion_state->x.w.i) {
            motion_state->x.w.i = entity->unk_84.u + entity->unk_8C.u;
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    case 1:
        if (entity->unk_86.s + entity->unk_8E.s < motion_state->y.w.i) {
            motion_state->y.w.i = entity->unk_86.u + entity->unk_8E.u;
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    case 2:
        if (motion_state->x.w.i < entity->unk_84.s - entity->unk_8C.s) {
            motion_state->x.w.i = entity->unk_84.u - entity->unk_8C.u;
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    default:
        if (motion_state->y.w.i < entity->unk_86.s - entity->unk_8E.s) {
            motion_state->y.w.i = entity->unk_86.u - entity->unk_8E.u;
            initialize_mother_event_actor(entity, motion_state, context);
            return;
        }
        break;
    }
    step_x = 0x20000;
    speed = motion_state->unk_0C + town_x_acceleration[quadrant];
    motion_state->unk_0C = speed;
    speed = abs(speed);
    speed = step_x < speed;
    if (speed != 0)
        motion_state->unk_0C = town_x_speed_limits[quadrant];
    speed = motion_state->unk_10 + town_y_acceleration[quadrant];
    motion_state->unk_10 = speed;
    speed = abs(speed);
    speed = step_x < speed;
    if (speed != 0)
        motion_state->unk_10 = town_y_speed_limits[quadrant];
}
