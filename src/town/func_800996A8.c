#include "common.h"

extern s32 D_800FE508[4];

/* Clamps coordinates to the configured bounds and returns flags for the crossed edges. */
s32 func_80096E08(s32 *x_ptr, s32 *y_ptr)
{
    s32 x;
    s32 y;
    s32 x_bound;
    s32 y_bound;
    s32 clamp_flags;

    x = *x_ptr;
    x_bound = D_800FE508[0];
    clamp_flags = 0;
    if (x < x_bound) {
        *x_ptr = x_bound;
        clamp_flags = 0x10;
    } else {
        if (((s32)(D_800FE508[1])) < x) {
            *x_ptr = ((s32)(D_800FE508[1]));
            clamp_flags = 1;
        }
    }

    y = *y_ptr;
    y_bound = D_800FE508[2];
    if (y < y_bound) {
        *y_ptr = y_bound;
        clamp_flags |= 0x1000;
    } else {
        s32 y_bound;
        y_bound = D_800FE508[3];
        if (y_bound < y) {
            *y_ptr = y_bound;
            clamp_flags |= 0x100;
        }
    }
    return clamp_flags;
}
