#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800C7674_0 {
    u8 pad_00[0x72];
    s16 unk_72;
    u8 pad_74[0x10];
    union { s16 s; u16 u; } unk_84;   /* accessed as both */
    union { s16 s; u16 u; } unk_86;   /* accessed as both */
    u8 pad_88[0x4];
    union { s16 s; u16 u; } unk_8C;   /* accessed as both */
    union { s16 s; u16 u; } unk_8E;   /* accessed as both */
} S_800C7674_0;   /* arg0 in func_800C7674 */




typedef struct Motion {
    s32 pos_x;
    s32 pos_y;
    s16 field_08;
    s16 height;
    s32 step_x;
    s32 step_y;
} Motion;

extern s16 func_800C2AE8();
extern s32 func_800C30E0();
extern void func_800C7A6C();
extern int abs(int);

extern s32 D_800D4FE8[4];
extern s32 D_800D4FF8[4];
extern s32 D_800D5008[4];
extern s32 D_800D5018[4];

/* Advance motion, clamp it to the directional bound, and update velocity. */
void func_800C7674(S_800C7674_0 *entity, Rec_D_800E3D7C *motion_state, s32 context)
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
        motion->height = func_800C2AE8(motion, step_x, step_y, angle);
    }

    if (func_800C30E0(entity, motion_state, context) != 0) {
        return;
    }

    if (quadrant == 1) goto case_one;
    if (quadrant < 2) {
        if (quadrant == 0) goto case_zero;
        goto case_three;
    }
    if (quadrant == 2) goto case_two;
    goto case_three;

case_zero:
    if (entity->unk_84.s + entity->unk_8C.s < motion_state->unk_00.at02_s16.v) {
        motion_state->unk_00.at02_s16.v = entity->unk_84.u + entity->unk_8C.u;
        goto position_clamped;
    }
    goto apply_velocity;
case_one:
    if (entity->unk_86.s + entity->unk_8E.s < motion_state->unk_04.at02_s16.v) {
        motion_state->unk_04.at02_s16.v = entity->unk_86.u + entity->unk_8E.u;
        goto position_clamped;
    }
    goto apply_velocity;
case_two:
    if (motion_state->unk_00.at02_s16.v < entity->unk_84.s - entity->unk_8C.s) {
        motion_state->unk_00.at02_s16.v = entity->unk_84.u - entity->unk_8C.u;
        goto position_clamped;
    }
    goto apply_velocity;
case_three:
    if (motion_state->unk_04.at02_s16.v < entity->unk_86.s - entity->unk_8E.s) {
        motion_state->unk_04.at02_s16.v = entity->unk_86.u - entity->unk_8E.u;
        goto position_clamped;
    }
    goto apply_velocity;
position_clamped:
    func_800C7A6C(entity, motion_state, context);
    return;
apply_velocity:
    step_x = 0x20000;
    speed = motion_state->unk_0C.as_s32 + D_800D4FE8[quadrant];
    motion_state->unk_0C.as_s32 = speed;
    speed = abs(speed);
    speed = step_x < speed;
    if (speed != 0) motion_state->unk_0C.as_s32 = D_800D4FF8[quadrant];
    speed = motion_state->unk_10.at00_s32.v + D_800D5008[quadrant];
    motion_state->unk_10.at00_s32.v = speed;
    speed = abs(speed);
    speed = step_x < speed;
    if (speed != 0) motion_state->unk_10.at00_s32.v = D_800D5018[quadrant];
}
