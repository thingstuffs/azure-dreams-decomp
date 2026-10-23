#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
extern int abs(int);

typedef struct Motion {
    u8 pad_00[0xC];
    s32 dx;
    s32 dy;
} Motion;

s16 call_callee_8008_c_4_c_8_global_800_d_0410_parameter(s32 input_value, s32 parameter);
s16 call_callee_8008_c_570_global_800_d_0414_parameter(s32 input_value, s32 parameter);
s16 call_callee_8008_c_610_global_800_d_0418_parameter(s32 input_value, s32 parameter);
s16 call_callee_8008_c_6_b_8_global_800_d_041_c_parameter(s32 input_value, s32 parameter);
void call_the_callee_80096208_callee_800962_b_8(void *);                 /* extern */
void call_the_callee_800962_b_8_callee_80096208(void *);                 /* extern */
extern Motion town_collision_motion;
#define D_80100000 ((s32 *)0x80100000)

/* Resolves movement collisions along one axis using boundary probes and tile offsets. */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(EntityRec *position) {
    s32 probe_coord;
    struct {
        s32 x;
        s32 y;
        s32 z;
        s32 pad3;
        s32 pad4;
    } probe;
    Motion *motion;
    Motion *probe_ptr;
    Motion *pos_x_neg_y_motion;
    Motion *neg_x_pos_y_motion;
    Motion *neg_xy_motion;
    s32 neg_x_pos_y_x;
    s32 neg_xy_x;
    s32 y_step_or_side;
    s32 pos_x_hit;
    s32 pos_x_neg_y_y;
    s32 neg_y_hit;
    s32 neg_x_boundary;
    s32 neg_xy_boundary;
    s32 pos_xy_test;
    s32 pos_x_neg_y_test;
    s32 axis_test;

    motion = &town_collision_motion;
    if (motion->dx > 0) {
        if (motion->dy > 0) {
            s32 boundary_test;
            s32 x_hit;
            probe.x = position->x.v - motion->dx;
            probe.y = position->y.v;
            probe.z = position->z.v;
            x_hit = position->x.v < (call_callee_8008_c_4_c_8_global_800_d_0410_parameter(&probe, 0) << 0x10);
            x_hit ^= 1;
            probe.x = position->x.v;
            probe.y = position->y.v - motion->dy;
            probe.z = position->z.v;
            boundary_test = call_callee_8008_c_610_global_800_d_0418_parameter(&probe, 0) << 0x10;
            boundary_test = position->y.v < boundary_test;
            boundary_test ^= 1;
            if (x_hit == 0) {
                probe_ptr = (Motion *)D_80100000;
                if (boundary_test == 0) {
                    s32 x_offset;
                    s32 y_offset;
                    x_offset = ((u16)position->x.w.i);
                    y_offset = ((u16)position->y.w.i);
                    x_offset &= 0x3F;
                    y_offset &= 0x3F;
                    x_offset = x_offset < y_offset;
                    if (x_offset == 0) {
                        call_the_callee_800962_b_8_callee_80096208(position);
                        return;
                    }
                    call_the_callee_80096208_callee_800962_b_8(position);
                    return;
                }
            } else {
                probe_ptr = (Motion *)D_80100000;
            }
            probe_ptr = (Motion *)((s8 *)probe_ptr - 0x1A40);
            probe.x = position->x.v - probe_ptr->dx;
            pos_x_neg_y_y = position->y.v;
            pos_xy_test = probe_ptr->dy;

            y_step_or_side = 0;
            probe.y = pos_x_neg_y_y - pos_xy_test;
            probe.z = position->z.v - pos_xy_test;
            pos_xy_test = position->x.v < (call_callee_8008_c_4_c_8_global_800_d_0410_parameter(&probe, y_step_or_side) << 0x10);
            pos_xy_test ^= 1;
            if (pos_xy_test != 0) {
                call_the_callee_80096208_callee_800962_b_8(position);
                return;
            }
            call_the_callee_800962_b_8_callee_80096208(position);
            return;
        }
        if (motion->dy < 0) {
            probe.x = position->x.v - motion->dx;
            probe.y = position->y.v;
            probe.z = position->z.v;
            pos_x_hit = position->x.v < (call_callee_8008_c_4_c_8_global_800_d_0410_parameter(&probe, 1) << 0x10);
            pos_x_hit ^= 1;
            probe.x = position->x.v;
            probe.y = position->y.v - motion->dy;
            probe.z = position->z.v;
            neg_y_hit = (call_callee_8008_c_6_b_8_global_800_d_041_c_parameter(&probe, 0) << 0x10) >= position->y.v;
            if (pos_x_hit == 0) {
                pos_x_neg_y_motion = (Motion *)D_80100000;
                if (neg_y_hit == 0) {
                    s32 x_offset;
                    s32 absolute_y;
                    x_offset = ((u16)position->x.w.i);
                    absolute_y = position->y.w.i;
                    x_offset &= 0x3F;
                    absolute_y = abs(absolute_y);
                    absolute_y &= 0x3F;
                    x_offset = x_offset < absolute_y;
                    if (x_offset != 0) {
                        call_the_callee_80096208_callee_800962_b_8(position);
                        return;
                    }
                    call_the_callee_800962_b_8_callee_80096208(position);
                    return;
                }
            } else {
                pos_x_neg_y_motion = (Motion *)D_80100000;
            }
            pos_x_neg_y_motion = (Motion *)((s8 *)pos_x_neg_y_motion - 0x1A40);
            probe.x = position->x.v - pos_x_neg_y_motion->dx;
            pos_x_neg_y_y = position->y.v;
            pos_x_neg_y_test = pos_x_neg_y_motion->dy;

            y_step_or_side = 1;
            probe.y = pos_x_neg_y_y - pos_x_neg_y_test;
            probe.z = position->z.v - pos_x_neg_y_test;
            pos_x_neg_y_test = position->x.v >= (call_callee_8008_c_4_c_8_global_800_d_0410_parameter(&probe, y_step_or_side) << 0x10);
            if (pos_x_neg_y_test != 0) {
                call_the_callee_80096208_callee_800962_b_8(position);
                return;
            } else {
                call_the_callee_800962_b_8_callee_80096208(position);
                return;
            }
        }
    }
    {
        Motion *neg_x_motion;
        neg_x_motion = &town_collision_motion;
        if (neg_x_motion->dx < 0) {
            if (neg_x_motion->dy > 0) {
                s32 y_test;
                s32 hit_a;
                probe.x = position->x.v - neg_x_motion->dx;
                probe.y = position->y.v;
                probe.z = position->z.v;
                neg_x_boundary = call_callee_8008_c_570_global_800_d_0414_parameter(&probe, 0);
                neg_x_pos_y_x = position->x.v;
                probe.x = neg_x_pos_y_x;
                hit_a = (neg_x_boundary << 0x10) >= neg_x_pos_y_x;
                probe.y = position->y.v - neg_x_motion->dy;
                probe.z = position->z.v;
                y_test = call_callee_8008_c_610_global_800_d_0418_parameter(&probe, 1);
                probe_coord = position->y.v;
                y_test <<= 0x10;
                probe_coord = probe_coord < y_test;
                y_test = probe_coord ^ 1;
                if (hit_a == 0) {
                    neg_x_pos_y_motion = (Motion *)D_80100000;
                    if (y_test == 0) {
                        s32 y_offset;
                        s32 absolute_x = abs(position->x.w.i);
                        y_offset = ((u16)position->y.w.i);
                        absolute_x &= 0x3F;
                        y_offset &= 0x3F;
                        if (absolute_x < y_offset) {
                            call_the_callee_80096208_callee_800962_b_8(position);
                            return;
                        }
                        call_the_callee_800962_b_8_callee_80096208(position);
                        return;
                    }
                } else {
                    neg_x_pos_y_motion = (Motion *)D_80100000;
                }
                neg_x_pos_y_motion = (Motion *)((s8 *)neg_x_pos_y_motion - 0x1A40);
                probe.x = position->x.v - neg_x_pos_y_motion->dx;
                pos_x_neg_y_y = position->y.v;
                probe_coord = neg_x_pos_y_motion->dy;

                y_step_or_side = 0;
                probe.y = pos_x_neg_y_y - probe_coord;
                probe.z = position->z.v - probe_coord;
                axis_test = (call_callee_8008_c_570_global_800_d_0414_parameter(&probe, y_step_or_side) << 0x10) < position->x.v;
                axis_test ^= 1;
                if (axis_test != 0) {
                    call_the_callee_80096208_callee_800962_b_8(position);
                    return;
                }
                call_the_callee_800962_b_8_callee_80096208(position);
                return;
            }
            if (neg_x_motion->dy < 0) {
                s32 hit_b;
                probe.x = position->x.v - neg_x_motion->dx;
                probe.y = position->y.v;
                probe.z = position->z.v;
                neg_xy_boundary = call_callee_8008_c_570_global_800_d_0414_parameter(&probe, 1);
                neg_xy_x = position->x.v;
                probe.x = neg_xy_x;
                hit_b = (neg_xy_boundary << 0x10) >= neg_xy_x;
                probe.y = position->y.v - neg_x_motion->dy;
                probe.z = position->z.v;
                axis_test = call_callee_8008_c_6_b_8_global_800_d_041_c_parameter(&probe, 1);
                probe_coord = position->y.v;
                axis_test <<= 0x10;
                axis_test = axis_test < probe_coord;
                axis_test ^= 1;
                if (hit_b == 0) {
                    neg_xy_motion = (Motion *)D_80100000;
                    if (axis_test == 0) {
                        s32 y_offset;
                        s32 absolute_x = abs(position->x.w.i);
                        y_offset = (s16)position->y.w.i;
                        absolute_x &= 0x3F;
                        y_offset = abs(y_offset);
                        y_offset &= 0x3F;
                        if (absolute_x < y_offset) {
                            call_the_callee_800962_b_8_callee_80096208(position);
                            return;
                        }
                        call_the_callee_80096208_callee_800962_b_8(position);
                        return;
                    }
                } else {
                    neg_xy_motion = (Motion *)D_80100000;
                }
                neg_xy_motion = (Motion *)((s8 *)neg_xy_motion - 0x1A40);
                probe.x = position->x.v - neg_xy_motion->dx;
                pos_x_neg_y_y = position->y.v;
                probe_coord = neg_xy_motion->dy;

                y_step_or_side = 1;
                probe.y = pos_x_neg_y_y - probe_coord;
                probe.z = position->z.v - probe_coord;
                axis_test = call_callee_8008_c_570_global_800_d_0414_parameter(&probe, y_step_or_side);
                axis_test <<= 16;
                axis_test = axis_test < position->x.v;
                axis_test ^= 1;
                if (axis_test != 0) {
                    call_the_callee_80096208_callee_800962_b_8(position);
                    return;
                }
                call_the_callee_800962_b_8_callee_80096208(position);
                return;
            }
        }
    }
    {
        Motion *axis_motion;
        axis_motion = &town_collision_motion;
        if (axis_motion->dx != 0) {
            if (axis_motion->dy != 0) {
                return;
            }
            call_the_callee_80096208_callee_800962_b_8(position);
            return;
        }
        if (axis_motion->dy == 0) {
            return;
        }

        call_the_callee_800962_b_8_callee_80096208(position);
    }
}
