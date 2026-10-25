#include "common.h"

extern s32 player_motion_bounds[4];

/* Clamps coordinates to the configured bounds and returns flags for the crossed edges. */
s32 clamp_coordinates_to_bounds(s32 *x_ptr, s32 *y_ptr)
{
    s32 x;
    s32 y;
    s32 x_bound;
    s32 y_bound;
    s32 clamp_flags;

    x = *x_ptr;
    x_bound = player_motion_bounds[0];
    clamp_flags = 0;
    if (x < x_bound) {
        *x_ptr = x_bound;
        clamp_flags = 0x10;
    } else {
        if (((s32)(player_motion_bounds[1])) < x) {
            *x_ptr = ((s32)(player_motion_bounds[1]));
            clamp_flags = 1;
        }
    }

    y = *y_ptr;
    y_bound = player_motion_bounds[2];
    if (y < y_bound) {
        *y_ptr = y_bound;
        clamp_flags |= 0x1000;
    } else {
        s32 vertical_bound;
        vertical_bound = player_motion_bounds[3];
        if (vertical_bound < y) {
            *y_ptr = vertical_bound;
            clamp_flags |= 0x100;
        }
    }
    return clamp_flags;
}
