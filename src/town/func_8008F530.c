#include "common.h"

extern s32 func_80065F90(s32, s32);

/* Checks cyclic half-turn limits for four vector directions, accepting zero vectors. */
s32 func_8008CC90(
    s16 first_x, s16 first_y, s16 second_x, s16 second_y,
    u16 third_x, u16 third_y, u16 fourth_x, u16 fourth_y)
{
    s32 base_angle;
    s32 third_angle;
    s32 second_angle;
    s32 within_limits;
    s32 second_gap;
    s32 third_gap;
    s32 shifted_y;
    s32 closing_gap;
    s32 angle_work;

    if (((u32)first_y << 16) == 0) {
        if (((u32)first_x << 16) == 0) return 1;
    }
    if (((u32)second_y << 16) == 0) {
        if (((u32)second_x << 16) == 0) return 1;
    }
    if (third_y == 0) {
        if (third_x == 0) return 1;
    }
    if (fourth_y == 0) {
        if (fourth_x == 0) {
            within_limits = 1;
            goto out;
        }
        shifted_y = (s32)((u32)first_y << 16);
    } else {
        shifted_y = (s32)((u32)first_y << 16);
    }

    base_angle = func_80065F90(shifted_y >> 16, (s16)first_x) & 0xFFF;
    second_angle = func_80065F90((s16)second_y, (s16)second_x) & 0xFFF;
    third_angle = func_80065F90((s16)third_y, (s16)third_x) & 0xFFF;
    closing_gap = func_80065F90((s16)fourth_y, (s16)fourth_x) & 0xFFF;
    closing_gap = (closing_gap - base_angle) & 0xFFF;
    third_angle = (third_angle - base_angle) & 0xFFF;
    second_angle = (second_angle - base_angle) & 0xFFF;
    angle_work = third_angle - second_angle;
    second_gap = angle_work & 0xFFF;
    angle_work = closing_gap - third_angle;
    third_gap = angle_work & 0xFFF;
    angle_work = 0x1000;
    closing_gap = angle_work - closing_gap;

    if (second_angle < 0x801 && second_gap < 0x801) {
        if (third_gap >= 0x801) { within_limits = 0; goto out; }
        closing_gap = closing_gap < 0x801;
        if (closing_gap != 0) { within_limits = 1; goto out; }
    }
    within_limits = 0;
out:
    return within_limits;
}
