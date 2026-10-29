#include "common.h"
#include "town/scene/collision.h"

extern CollisionOverlap box_overlap[];

/* Returns the smallest signed overlap axis and amount for two intersecting object boxes. */
CollisionOverlap *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(void *first_box, void *second_box)
{
    ColliderView *box_a = first_box;
    ColliderView *box_b = second_box;
    register s32 *a_bounds = &box_a->bounds->offset_x;
    register s32 *b_bounds = &box_b->bounds->offset_x;
    register s32 *a_position = &box_a->position->x.v;
    register s32 *b_position = &box_b->position->x.v;
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
    if (overlap_x > 0)
        return 0;
    a_max_x = a_min_x + a_bounds[3];
    overlap_x_alt = a_max_x - b_min_x;
    x_shallower_z = 0;
    if (overlap_x_alt < 0)
        return 0;

    a_min_y = a_coords[1] + a_offset[1];
    b_min_y = b_coords[1] + b_bounds[1];
    overlap_y = a_min_y - (b_min_y + b_extents[4]);
    if (overlap_y > 0)
        return 0;
    overlap_y_alt = (a_min_y + a_bounds[4]) - b_min_y;
    x_shallower_z = 0;
    if (overlap_y_alt < 0)
        return 0;

    a_min_z = a_coords[2] + a_offset[2];
    b_min_z = b_coords[2] + b_bounds[2];
    overlap_z = a_min_z - (b_min_z + b_extents[5]);
    if (overlap_z > 0)
        return 0;
    overlap_z_alt = (a_min_z + a_bounds[5]) - b_min_z;
    if (overlap_z_alt < 0)
        return 0;

    /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: town/func_80092360). */
    do {
        abs_x = __builtin_abs(overlap_x);
    } while (0);
    abs_x_alt = __builtin_abs(overlap_x_alt);
    if (abs_x_alt < abs_x)
        overlap_x = overlap_x_alt;
    abs_y = __builtin_abs(overlap_y);
    abs_y_alt = __builtin_abs(overlap_y_alt);
    if (abs_y_alt < abs_y)
        overlap_y = overlap_y_alt;
    abs_z = __builtin_abs(overlap_z);
    abs_z_alt = __builtin_abs(overlap_z_alt);
    if (abs_z_alt < abs_z)
        overlap_z = overlap_z_alt;

    if (overlap_x == 0) {
        if (overlap_y == 0)
            return 0;
        if (overlap_z == 0)
            return 0;
    }
    if (overlap_y == 0) {
        if (overlap_z == 0)
            return 0;
    }

    depth_x = __builtin_abs(overlap_x);
    depth_y = __builtin_abs(overlap_y);
    if (depth_x < depth_y) {
        depth_z_for_x = __builtin_abs(overlap_z);
        y_shallower_z = depth_y < depth_z_for_x;
        if (y_shallower_z || (x_shallower_z = depth_x < depth_z_for_x) != 0) {
            box_overlap[0].axis = 0;
            box_overlap[0].amount = overlap_x;
            return box_overlap;
        }
    } else {
        depth_z_for_y = __builtin_abs(overlap_z);
        y_shallower_z_alt = depth_y < depth_z_for_y;
        if (y_shallower_z_alt) {
            box_overlap[0].axis = 1;
            box_overlap[0].amount = overlap_y;
            return box_overlap;
        }
    }
    box_overlap[0].axis = 2;
    box_overlap[0].amount = overlap_z;
    return box_overlap;
}
