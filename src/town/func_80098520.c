#include "common.h"
#include "m2c_compat.h"
extern int abs(int);

typedef struct S_80095C80_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_0;   /* base in func_80095C80 */

typedef struct S_80095C80_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80095C80_1;   /* arg0 in func_80095C80 */

typedef struct S_80095C80_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_2;   /* var_a0 in func_80095C80 */

typedef struct S_80095C80_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_3;   /* var_a0_2 in func_80095C80 */

typedef struct S_80095C80_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_4;   /* (M2C_UNK *)neg_work in func_80095C80 */

typedef struct S_80095C80_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_5;   /* var_a0_3 in func_80095C80 */

typedef struct S_80095C80_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_6;   /* var_a0_4 in func_80095C80 */

typedef struct S_80095C80_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80095C80_7;   /* final_base in func_80095C80 */


s32 func_80095BC0();                  /* extern */
s32 func_80095BF0();                  /* extern */
s32 func_80095C20();             /* extern */
s32 func_80095C50();             /* extern */
void func_800961A8(void *);                 /* extern */
void func_800961D8(void *);                 /* extern */
extern s32 D_800FE5C0[];
#ifdef NON_MATCHING
#define D_80100000 ((s32 *)((s8 *)D_800FE5C0 + 0x1A40))
#else
#define D_80100000 ((s32 *)0x80100000)
#endif

/* Resolves movement collisions along one axis using boundary probes and tile offsets. */
void func_80095C80(S_80095C80_1 *position) {
    struct {
        s32 x;
        s32 y;
        s32 z;
        s32 pad3;
        s32 pad4;
    } probe;
    M2C_UNK *motion;
    M2C_UNK *pos_xy_motion;
    M2C_UNK *pos_x_neg_y_motion;
    M2C_UNK *neg_x_pos_y_motion;
    M2C_UNK *neg_xy_motion;
    s32 neg_x_pos_y_x;
    s32 neg_xy_x;
    s32 y_step_or_side;
    s32 pos_x_hit;
    s32 pos_xy_y;
    s32 pos_x_neg_y_y;
    s32 neg_x_pos_y_y;
    s32 neg_y_hit;
    s32 neg_x_boundary;
    s32 neg_xy_y;
    s32 neg_xy_boundary;
    s32 pos_xy_test;
    s32 pos_x_neg_y_test;
    register s32 axis_test ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    M2C_UNK *motion_page;

    motion_page = (M2C_UNK *)D_80100000;
    ASM_KEEP_NV(motion_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    motion = (M2C_UNK *)((s8 *)motion_page - 0x1A40);
    {
        if (((S_80095C80_0 *)motion)->unk_0C <= 0) {
            goto check_neg_x;
        }
        if (((S_80095C80_0 *)motion)->unk_10 > 0) {
            register s32 x_hit ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            s32 boundary_test;
            register s32 probe_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            void *probe_ptr;
            probe.x = position->unk_00.at00.v - ((S_80095C80_0 *)motion)->unk_0C;
            probe.y = position->unk_04.at00.v;
            probe.z = position->unk_08;
            boundary_test = func_80095BC0(&probe, 0);
            probe_ptr = &probe;
            ASM_KEEP_NV(probe_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            x_hit = position->unk_00.at00.v;
            probe.x = x_hit;
            x_hit = x_hit < (boundary_test << 0x10);
            probe_coord = position->unk_04.at00.v;
            ASM_CLOBBER("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            y_step_or_side = ((S_80095C80_0 *)motion)->unk_10;
            x_hit ^= 1;
            probe.y = probe_coord - y_step_or_side;
            probe_coord = position->unk_08;
            probe.z = probe_coord;
            boundary_test = func_80095C20(probe_ptr, 0);
            probe_coord = position->unk_04.at00.v;
            boundary_test <<= 0x10;
            probe_coord = probe_coord < boundary_test;
            boundary_test = probe_coord ^ 1;
            if (x_hit == 0) {
                pos_xy_motion = (M2C_UNK *)D_80100000;
                if (boundary_test == 0) {
                    s32 x_offset;
                    s32 y_offset;
                    x_offset = position->unk_00.at02.v;
                    y_offset = position->unk_04.at02.v;
                    x_offset &= 0x3F;
                    y_offset &= 0x3F;
                    x_offset = x_offset < y_offset;
                    if (x_offset == 0) {
                        goto resolve_y;
                    }
                    goto resolve_x;
                }
                goto check_pos_xy_corner;
            }
            pos_xy_motion = (M2C_UNK *)D_80100000;
check_pos_xy_corner:
            pos_xy_motion = (M2C_UNK *)((s8 *)pos_xy_motion - 0x1A40);
            probe.x = position->unk_00.at00.v - ((S_80095C80_2 *)pos_xy_motion)->unk_0C;
            pos_xy_y = position->unk_04.at00.v;
            do {
                pos_xy_test = ((S_80095C80_2 *)pos_xy_motion)->unk_10;
            } while (0);
               /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            y_step_or_side = 0;
            ASM_KEEP_NV(y_step_or_side);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            probe.y = pos_xy_y - pos_xy_test;
            probe.z = position->unk_08 - pos_xy_test;
            pos_xy_test = position->unk_00.at00.v < (func_80095BC0(&probe, y_step_or_side) << 0x10);
            pos_xy_test ^= 1;
            if (pos_xy_test != 0) {
                goto resolve_x;
            }
            goto resolve_y;
        }
        if (((S_80095C80_0 *)motion)->unk_10 < 0) {
            probe.x = position->unk_00.at00.v - ((S_80095C80_0 *)motion)->unk_0C;
            probe.y = position->unk_04.at00.v;
            probe.z = position->unk_08;
            pos_x_hit = position->unk_00.at00.v < (func_80095BC0(&probe, 1) << 0x10);
            pos_x_hit ^= 1;
            probe.x = position->unk_00.at00.v;
            probe.y = position->unk_04.at00.v - ((S_80095C80_0 *)motion)->unk_10;
            probe.z = position->unk_08;
            neg_y_hit = (func_80095C50(&probe, 0) << 0x10) >= position->unk_04.at00.v;
            if (pos_x_hit == 0) {
                pos_x_neg_y_motion = (M2C_UNK *)D_80100000;
                if (neg_y_hit == 0) {
                    s32 x_offset;
                    x_offset = position->unk_00.at02.v;
                    axis_test = (s16) position->unk_04.at02.v;
                    x_offset &= 0x3F;
                    ASM_KEEP_NV(x_offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    if (axis_test < 0) {
                        axis_test = 0 - axis_test;
                    }
                    axis_test &= 0x3F;
                    x_offset = x_offset < axis_test;
                    if (x_offset != 0) {
                        goto resolve_x;
                    }
                    goto resolve_y;
                }
                goto check_pos_x_neg_y_corner;
            }
            pos_x_neg_y_motion = (M2C_UNK *)D_80100000;
check_pos_x_neg_y_corner:
            pos_x_neg_y_motion = (M2C_UNK *)((s8 *)pos_x_neg_y_motion - 0x1A40);
            probe.x = position->unk_00.at00.v - ((S_80095C80_3 *)pos_x_neg_y_motion)->unk_0C;
            pos_x_neg_y_y = position->unk_04.at00.v;
            do {
                pos_x_neg_y_test = ((S_80095C80_3 *)pos_x_neg_y_motion)->unk_10;
            } while (0);
               /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            y_step_or_side = 1;
            ASM_KEEP_NV(y_step_or_side);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            probe.y = pos_x_neg_y_y - pos_x_neg_y_test;
            probe.z = position->unk_08 - pos_x_neg_y_test;
            pos_x_neg_y_test = position->unk_00.at00.v >= (func_80095BC0(&probe, y_step_or_side) << 0x10);
            ASM_KEEP_NV(pos_x_neg_y_test);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            if (pos_x_neg_y_test != 0) {
                goto resolve_x;
            }
            goto resolve_y;
        }
        goto load_neg_x_motion;
    }
load_neg_x_motion:
    {
        unsigned long motion_or_hit;
        motion_page = (M2C_UNK *)D_80100000;
check_neg_x:
        motion_or_hit = (unsigned long)((s8 *)motion_page - 0x1A40);
        {
            if (((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_0C >= 0) {
                goto check_single_axis;
            }
            if (((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_10 > 0) {
                register s32 y_step_or_side ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                register s32 probe_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 y_test;
                probe.x = position->unk_00.at00.v - ((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_0C;
                probe.y = position->unk_04.at00.v;
                probe.z = position->unk_08;
                neg_x_boundary = func_80095BF0(&probe, 0);
                neg_x_pos_y_x = position->unk_00.at00.v;
                probe.x = neg_x_pos_y_x;
                probe_coord = position->unk_04.at00.v;
                y_step_or_side = ((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_10;
                motion_or_hit = neg_x_boundary << 0x10;
                motion_or_hit = (s32)motion_or_hit < neg_x_pos_y_x;
                motion_or_hit ^= 1;
                probe.y = probe_coord - y_step_or_side;
                probe_coord = position->unk_08;
                probe.z = probe_coord;
                y_test = func_80095C20(&probe, 1, neg_x_pos_y_x);
                probe_coord = position->unk_04.at00.v;
                y_test <<= 0x10;
                probe_coord = probe_coord < y_test;
                y_test = probe_coord ^ 1;
                if (motion_or_hit == 0) {
                    neg_x_pos_y_motion = (M2C_UNK *)D_80100000;
                    if (y_test == 0) {
                        s32 y_offset;
                        axis_test = (s16) position->unk_00.at02.v;
                        y_offset = position->unk_04.at02.v;
                        if (axis_test < 0) {
                            axis_test = 0 - axis_test;
                        }
                        axis_test &= 0x3F;
                        y_offset &= 0x3F;
                        if (axis_test < y_offset) {
                            goto resolve_x;
                        }
                        goto resolve_y;
                    }
                    goto check_neg_x_pos_y_corner;
                }
                neg_x_pos_y_motion = (M2C_UNK *)D_80100000;
check_neg_x_pos_y_corner:
                neg_x_pos_y_motion = (M2C_UNK *)((s8 *)neg_x_pos_y_motion - 0x1A40);
                probe.x = position->unk_00.at00.v - ((S_80095C80_5 *)neg_x_pos_y_motion)->unk_0C;
                neg_x_pos_y_y = position->unk_04.at00.v;
                do {
                    probe_coord = ((S_80095C80_5 *)neg_x_pos_y_motion)->unk_10;
                } while (0);
                   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                y_step_or_side = 0;
                ASM_KEEP_NV(y_step_or_side);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                probe.y = neg_x_pos_y_y - probe_coord;
                probe.z = position->unk_08 - probe_coord;
                axis_test = (func_80095BF0(&probe, y_step_or_side) << 0x10) < position->unk_00.at00.v;
                axis_test ^= 1;
                if (axis_test != 0) {
                    goto resolve_x;
                }
                goto resolve_y;
            }
            if (((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_10 < 0) {
                register s32 y_step_or_side ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                register s32 probe_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                probe.x = position->unk_00.at00.v - ((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_0C;
                probe.y = position->unk_04.at00.v;
                probe.z = position->unk_08;
                neg_xy_boundary = func_80095BF0(&probe, 1);
                neg_xy_x = position->unk_00.at00.v;
                probe.x = neg_xy_x;
                probe_coord = position->unk_04.at00.v;
                y_step_or_side = ((S_80095C80_4 *)((M2C_UNK *)motion_or_hit))->unk_10;
                motion_or_hit = neg_xy_boundary << 0x10;
                motion_or_hit = (s32)motion_or_hit < neg_xy_x;
                motion_or_hit ^= 1;
                probe.y = probe_coord - y_step_or_side;
                probe_coord = position->unk_08;
                probe.z = probe_coord;
                axis_test = func_80095C50(&probe, 1, neg_xy_x);
                probe_coord = position->unk_04.at00.v;
                axis_test <<= 0x10;
                axis_test = axis_test < probe_coord;
                axis_test ^= 1;
                if (motion_or_hit == 0) {
                    neg_xy_motion = (M2C_UNK *)D_80100000;
                    if (axis_test == 0) {
                        s32 y_offset;
                        axis_test = (s16) position->unk_00.at02.v;
                        y_offset = (s16) position->unk_04.at02.v;
                        if (axis_test < 0) {
                            axis_test = 0 - axis_test;
                        }
                        axis_test &= 0x3F;
                        y_offset = abs(y_offset);
                        y_offset &= 0x3F;
                        if (axis_test < y_offset) {
                            goto apply_y;
                        }
                        goto resolve_x;
                    }
                    goto check_neg_xy_corner;
                }
                neg_xy_motion = (M2C_UNK *)D_80100000;
check_neg_xy_corner:
                neg_xy_motion = (M2C_UNK *)((s8 *)neg_xy_motion - 0x1A40);
                probe.x = position->unk_00.at00.v - ((S_80095C80_6 *)neg_xy_motion)->unk_0C;
                neg_xy_y = position->unk_04.at00.v;
                do {
                    probe_coord = ((S_80095C80_6 *)neg_xy_motion)->unk_10;
                } while (0);
                   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                y_step_or_side = 1;
                ASM_KEEP_NV(y_step_or_side);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                probe.y = neg_xy_y - probe_coord;
                probe.z = position->unk_08 - probe_coord;
                axis_test = (func_80095BF0(&probe, y_step_or_side) << 0x10) >= position->unk_00.at00.v;
                ASM_KEEP_NV(axis_test);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                if (axis_test != 0) {
                    goto resolve_x;
                }
                goto resolve_y;
            }
            goto load_axis_motion;
        }
    }
load_axis_motion:
    {
        M2C_UNK *axis_motion;
        motion_page = (M2C_UNK *)D_80100000;
check_single_axis:
        axis_motion = (M2C_UNK *)((s8 *)motion_page - 0x1A40);
        if (((S_80095C80_7 *)axis_motion)->unk_0C == 0) {
            goto check_final_y;
        }
        if (((S_80095C80_7 *)axis_motion)->unk_10 != 0) {
            goto done;
        }

resolve_x:
        func_800961A8(position);
        goto done;

check_final_y:
        if (((S_80095C80_7 *)axis_motion)->unk_10 == 0) {
            goto done;
        }

resolve_y:
apply_y:
        func_800961D8(position);
    }

done:
    return;
}
