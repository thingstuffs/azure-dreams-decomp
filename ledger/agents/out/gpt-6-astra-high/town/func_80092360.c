#include "common.h"

typedef struct {
    s32 *part0;
    s32 *part1;
} Parts92360;

typedef struct {
    u8 pad0[8];
    Parts92360 parts;
} Object92360;

typedef struct {
    s32 axis;
    s32 amount;
} Result92360;

extern Result92360 D_800CFE60[];

/* Returns the smallest signed overlap axis and amount for two intersecting object boxes. */
Result92360 *func_8008FAC0(Object92360 *box_a, Object92360 *box_b)
{
    register s32 *a_bounds = box_a->parts.part1;
    register s32 *b_bounds = box_b->parts.part1;
    register s32 *a_position = box_a->parts.part0;
    register s32 *b_position = box_b->parts.part0;
    s32 *a_offset = a_bounds;
    s32 *a_coords = a_position;
    s32 *b_coords = b_position;
    s32 *b_extents = b_bounds;
    register s32 a_min_x, b_min_x, a_min_y, b_min_y, a_min_z, b_min_z;
    register s32 overlap_x, overlap_x_alt, overlap_y, overlap_y_alt, overlap_z, overlap_z_alt, a_max_x;
    register s32 abs_x, abs_x_alt, abs_y, abs_y_alt, abs_z, abs_z_alt;
    register s32 depth_x, depth_y, depth_z_for_x, depth_z_for_y, y_shallower_z, x_shallower_z, y_shallower_z_alt;

    a_min_x = a_coords[0] + a_offset[0];
    b_min_x = b_coords[0] + b_bounds[0];
    overlap_x = a_min_x - (b_min_x + b_extents[3]);
    if (overlap_x > 0) return 0;
    a_max_x = a_min_x + a_bounds[3];
    overlap_x_alt = a_max_x - b_min_x;
    x_shallower_z = 0;
    if (overlap_x_alt < 0) goto no_overlap;

    a_min_y = a_coords[1] + a_offset[1];
    b_min_y = b_coords[1] + b_bounds[1];
    overlap_y = a_min_y - (b_min_y + b_extents[4]);
    if (overlap_y > 0) return 0;
    overlap_y_alt = (a_min_y + a_bounds[4]) - b_min_y;
    x_shallower_z = 0;
    if (overlap_y_alt < 0) goto no_overlap;

    a_min_z = a_coords[2] + a_offset[2];
    b_min_z = b_coords[2] + b_bounds[2];
    overlap_z = a_min_z - (b_min_z + b_extents[5]);
    if (overlap_z > 0) return 0;
    overlap_z_alt = (a_min_z + a_bounds[5]) - b_min_z;
    if (overlap_z_alt < 0) return 0;

    do {
        abs_x = __builtin_abs(overlap_x);
    } while (0);
    abs_x_alt = __builtin_abs(overlap_x_alt);
    if (abs_x_alt < abs_x) overlap_x = overlap_x_alt;
    abs_y = __builtin_abs(overlap_y);
    abs_y_alt = __builtin_abs(overlap_y_alt);
    if (abs_y_alt < abs_y) overlap_y = overlap_y_alt;
    abs_z = __builtin_abs(overlap_z);
    abs_z_alt = __builtin_abs(overlap_z_alt);
    if (abs_z_alt < abs_z) overlap_z = overlap_z_alt;

    if (overlap_x == 0) {
        if (overlap_y == 0) return 0;
        if (overlap_z == 0) return 0;
    }
    if (overlap_y != 0) goto choose_axis;
    if (overlap_z != 0) goto choose_axis;
no_overlap:
    return 0;

choose_axis:
    depth_x = __builtin_abs(overlap_x);
    depth_y = __builtin_abs(overlap_y);
    if (depth_x < depth_y) {
        depth_z_for_x = __builtin_abs(overlap_z);
        y_shallower_z = depth_y < depth_z_for_x;
        if (y_shallower_z) goto use_x;
        x_shallower_z = depth_x < depth_z_for_x;
        if (!x_shallower_z) goto use_z;
use_x:
        D_800CFE60[0].axis = 0;
        D_800CFE60[0].amount = overlap_x;
        return D_800CFE60;
    }
    depth_z_for_y = __builtin_abs(overlap_z);
    y_shallower_z_alt = depth_y < depth_z_for_y;
    if (y_shallower_z_alt) {
        D_800CFE60[0].axis = 1;
        D_800CFE60[0].amount = overlap_y;
        return D_800CFE60;
    }
use_z:
    D_800CFE60[0].axis = 2;
    D_800CFE60[0].amount = overlap_z;
    return D_800CFE60;
}
