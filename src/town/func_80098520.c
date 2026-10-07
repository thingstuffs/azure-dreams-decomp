#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
extern int abs(int);

typedef struct Motion {
    u8 pad_00[0xC];
    s32 dx;
    s32 dy;
} Motion;

s16 func_80095BC0();                  /* extern */
s16 func_80095BF0();                  /* extern */
s16 func_80095C20();             /* extern */
s16 func_80095C50();             /* extern */
void func_800961A8(void *);                 /* extern */
void func_800961D8(void *);                 /* extern */
extern Motion D_800FE5C0;
#define D_80100000 ((s32 *)0x80100000)

/* Resolves movement collisions along one axis using boundary probes and tile offsets. */
void func_80095C80(EntityRec *position) {
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
    register s32 y_step_or_side ASM_REG("$5");
    s32 pos_x_hit;
    s32 pos_x_neg_y_y;
    s32 neg_y_hit;
    s32 neg_x_boundary;
    s32 neg_xy_boundary;
    s32 pos_xy_test;
    s32 pos_x_neg_y_test;
    s32 axis_test;

    motion = &D_800FE5C0;
    if (motion->dx > 0) {
        if (motion->dy > 0) {
            s32 boundary_test;
            s32 x_hit;
            probe.x = position->x.v - motion->dx;
            probe.y = position->y.v;
            probe.z = position->z.v;
            x_hit = position->x.v < (func_80095BC0(&probe, 0) << 0x10);
            x_hit ^= 1;
            probe.x = position->x.v;
            probe.y = position->y.v - motion->dy;
            probe.z = position->z.v;
            boundary_test = func_80095C20(&probe, 0) << 0x10;
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
                        func_800961D8(position);
                        return;
                    }
                    func_800961A8(position);
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
            pos_xy_test = position->x.v < (func_80095BC0(&probe, y_step_or_side) << 0x10);
            pos_xy_test ^= 1;
            if (pos_xy_test != 0) {
                func_800961A8(position);
                return;
            }
            func_800961D8(position);
            return;
        }
        if (motion->dy < 0) {
            probe.x = position->x.v - motion->dx;
            probe.y = position->y.v;
            probe.z = position->z.v;
            pos_x_hit = position->x.v < (func_80095BC0(&probe, 1) << 0x10);
            pos_x_hit ^= 1;
            probe.x = position->x.v;
            probe.y = position->y.v - motion->dy;
            probe.z = position->z.v;
            neg_y_hit = (func_80095C50(&probe, 0) << 0x10) >= position->y.v;
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
                        func_800961A8(position);
                        return;
                    }
                    func_800961D8(position);
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
            pos_x_neg_y_test = position->x.v >= (func_80095BC0(&probe, y_step_or_side) << 0x10);
            if (pos_x_neg_y_test != 0) {
                func_800961A8(position);
                return;
            } else {
                func_800961D8(position);
                return;
            }
        }
    }
    {
        unsigned long motion_or_hit;
        motion_or_hit = (unsigned long)&D_800FE5C0;
        if (((Motion *)motion_or_hit)->dx < 0) {
            if (((Motion *)motion_or_hit)->dy > 0) {
                s32 y_test;
                probe.x = position->x.v - ((Motion *)motion_or_hit)->dx;
                probe.y = position->y.v;
                probe.z = position->z.v;
                neg_x_boundary = func_80095BF0(&probe, 0);
                neg_x_pos_y_x = position->x.v;
                probe.x = neg_x_pos_y_x;
                probe_coord = position->y.v;
                y_step_or_side = ((Motion *)motion_or_hit)->dy;
                motion_or_hit = neg_x_boundary << 0x10;
                motion_or_hit = (s32)motion_or_hit < neg_x_pos_y_x;
                motion_or_hit ^= 1;
                probe_coord -= y_step_or_side;
                probe.y = probe_coord;
                probe_coord = position->z.v;
                probe.z = probe_coord;
                y_test = func_80095C20(&probe, 1, neg_x_pos_y_x);
                probe_coord = position->y.v;
                y_test <<= 0x10;
                probe_coord = probe_coord < y_test;
                y_test = probe_coord ^ 1;
                if (motion_or_hit == 0) {
                    neg_x_pos_y_motion = (Motion *)D_80100000;
                    if (y_test == 0) {
                        s32 y_offset;
                        s32 absolute_x = abs(position->x.w.i);
                        y_offset = ((u16)position->y.w.i);
                        absolute_x &= 0x3F;
                        y_offset &= 0x3F;
                        if (absolute_x < y_offset) {
                            func_800961A8(position);
                            return;
                        }
                        func_800961D8(position);
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
                axis_test = (func_80095BF0(&probe, y_step_or_side) << 0x10) < position->x.v;
                axis_test ^= 1;
                if (axis_test != 0) {
                    func_800961A8(position);
                    return;
                }
                func_800961D8(position);
                return;
            }
            if (((Motion *)motion_or_hit)->dy < 0) {
                probe.x = position->x.v - ((Motion *)motion_or_hit)->dx;
                probe.y = position->y.v;
                probe.z = position->z.v;
                neg_xy_boundary = func_80095BF0(&probe, 1);
                neg_xy_x = position->x.v;
                probe.x = neg_xy_x;
                probe_coord = position->y.v;
                y_step_or_side = ((Motion *)motion_or_hit)->dy;
                motion_or_hit = neg_xy_boundary << 0x10;
                motion_or_hit = (s32)motion_or_hit < neg_xy_x;
                motion_or_hit ^= 1;
                probe_coord -= y_step_or_side;
                probe.y = probe_coord;
                probe_coord = position->z.v;
                probe.z = probe_coord;
                axis_test = func_80095C50(&probe, 1, neg_xy_x);
                probe_coord = position->y.v;
                axis_test <<= 0x10;
                axis_test = axis_test < probe_coord;
                axis_test ^= 1;
                if (motion_or_hit == 0) {
                    neg_xy_motion = (Motion *)D_80100000;
                    if (axis_test == 0) {
                        s32 y_offset;
                        s32 absolute_x = abs(position->x.w.i);
                        y_offset = (s16)position->y.w.i;
                        absolute_x &= 0x3F;
                        y_offset = abs(y_offset);
                        y_offset &= 0x3F;
                        if (absolute_x < y_offset) {
                            func_800961D8(position);
                            return;
                        }
                        func_800961A8(position);
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
                axis_test = func_80095BF0(&probe, y_step_or_side);
                axis_test <<= 16;
                axis_test = axis_test < position->x.v;
                axis_test ^= 1;
                if (axis_test != 0) {
                    func_800961A8(position);
                    return;
                }
                func_800961D8(position);
                return;
            }
        }
    }
    {
        Motion *axis_motion;
        axis_motion = &D_800FE5C0;
        if (axis_motion->dx != 0) {
            if (axis_motion->dy != 0) {
                return;
            }
            func_800961A8(position);
            return;
        }
        if (axis_motion->dy == 0) {
            return;
        }

        func_800961D8(position);
    }
}
