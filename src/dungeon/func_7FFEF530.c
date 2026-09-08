#include "common.h"

extern s32 func_80065F90(s32, s32);

/* Checks successive angular gaps between four vectors, accepting zero vectors. */
s32 func_8008CC90(
    s16 x_a, s16 y_a, s16 x_b, s16 y_b,
    u16 x_c, u16 y_c, u16 x_d, u16 y_d)
{
    s32 base_angle;
    s32 angle_c;
    s32 angle_b;
    s32 accepted;
    s32 gap_bc;
    s32 gap_cd;
    s32 y_a_shifted;
    s32 angle_d;
    s32 angle_work;

    if (((u32)y_a << 16) == 0) {
        if (((u32)x_a << 16) == 0) return 1;
    }
    if (((u32)y_b << 16) == 0) {
        if (((u32)x_b << 16) == 0) return 1;
    }
    if (y_c == 0) {
        if (x_c == 0) return 1;
    }
    if (y_d == 0) {
        if (x_d == 0) {
            accepted = 1;
            goto out;
        }
        y_a_shifted = (s32)((u32)y_a << 16);
    } else {
        y_a_shifted = (s32)((u32)y_a << 16);
    }

    base_angle = func_80065F90(y_a_shifted >> 16, (s16)x_a) & 0xFFF;
    angle_b = func_80065F90((s16)y_b, (s16)x_b) & 0xFFF;
    angle_c = func_80065F90((s16)y_c, (s16)x_c) & 0xFFF;
    angle_d = func_80065F90((s16)y_d, (s16)x_d) & 0xFFF;
    angle_d = (angle_d - base_angle) & 0xFFF;
    angle_c = (angle_c - base_angle) & 0xFFF;
    angle_b = (angle_b - base_angle) & 0xFFF;
    angle_work = angle_c - angle_b;
    gap_bc = angle_work & 0xFFF;
    angle_work = angle_d - angle_c;
    gap_cd = angle_work & 0xFFF;
    angle_work = 0x1000;
    angle_d = angle_work - angle_d;

    if (angle_b < 0x801 && gap_bc < 0x801) {
        if (gap_cd >= 0x801) { accepted = 0; goto out; }
        angle_d = angle_d < 0x801;
        if (angle_d != 0) { accepted = 1; goto out; }
    }
    accepted = 0;
out:
    return accepted;
}
