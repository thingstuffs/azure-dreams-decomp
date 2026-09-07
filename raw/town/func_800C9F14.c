#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

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

void func_800C7674(void *arg0, void *arg1, s32 arg2)
{
    s32 quadrant;
    s32 angle;
    s32 value;
    s32 step_x;
    s32 pos_y;

    pos_y = FIELD(arg0, s16, 0x72);
    angle = 0x400 - pos_y;
    if (angle < 0) {
        angle += 0x3ff;
    }

    {
        Motion *motion;
        s32 pos_x;
        s32 step_y;

        motion = (Motion *)arg1;
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

    if (func_800C30E0(arg0, arg1, arg2) != 0) {
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
    if (FIELD(arg0, s16, 0x84) + FIELD(arg0, s16, 0x8c) < FIELD(arg1, s16, 2)) {
        FIELD(arg1, s16, 2) = FIELD(arg0, u16, 0x84) + FIELD(arg0, u16, 0x8c);
        goto position_clamped;
    }
    goto apply_velocity;
case_one:
    if (FIELD(arg0, s16, 0x86) + FIELD(arg0, s16, 0x8e) < FIELD(arg1, s16, 6)) {
        FIELD(arg1, s16, 6) = FIELD(arg0, u16, 0x86) + FIELD(arg0, u16, 0x8e);
        goto position_clamped;
    }
    goto apply_velocity;
case_two:
    if (FIELD(arg1, s16, 2) < FIELD(arg0, s16, 0x84) - FIELD(arg0, s16, 0x8c)) {
        FIELD(arg1, s16, 2) = FIELD(arg0, u16, 0x84) - FIELD(arg0, u16, 0x8c);
        goto position_clamped;
    }
    goto apply_velocity;
case_three:
    if (FIELD(arg1, s16, 6) < FIELD(arg0, s16, 0x86) - FIELD(arg0, s16, 0x8e)) {
        FIELD(arg1, s16, 6) = FIELD(arg0, u16, 0x86) - FIELD(arg0, u16, 0x8e);
        goto position_clamped;
    }
    goto apply_velocity;
position_clamped:
    func_800C7A6C(arg0, arg1, arg2);
    return;
apply_velocity:
    step_x = 0x20000;
    value = FIELD(arg1, s32, 0xc) + D_800D4FE8[quadrant];
    FIELD(arg1, s32, 0xc) = value;
    value = abs(value);
    value = step_x < value;
    if (value != 0) FIELD(arg1, s32, 0xc) = D_800D4FF8[quadrant];
    value = FIELD(arg1, s32, 0x10) + D_800D5008[quadrant];
    FIELD(arg1, s32, 0x10) = value;
    value = abs(value);
    value = step_x < value;
    if (value != 0) FIELD(arg1, s32, 0x10) = D_800D5018[quadrant];
}
