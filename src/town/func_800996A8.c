#include "common.h"

extern s32 D_800FE508[4];

/* Clamps coordinates to the configured bounds and returns flags for the crossed edges. */
s32 func_80096E08(s32 *x_ptr, s32 *y_ptr)
{
    s32 x;
    s32 y;
    s32 x_bound;
    s32 y_bound;
    register s32 clamp_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    x = *x_ptr;
    x_bound = D_800FE508[0];
    clamp_flags = 0;
    if (x < x_bound) {
        *x_ptr = x_bound;
        clamp_flags = 0x10;
    } else {
        x_bound = D_800FE508[1];
        if (x_bound < x) {
            *x_ptr = x_bound;
            clamp_flags = 1;
            ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        }
    }

    y = *y_ptr;
    y_bound = D_800FE508[2];
    if (y < y_bound) {
        *y_ptr = y_bound;
        clamp_flags |= 0x1000;
    } else {
        y_bound = D_800FE508[3];
        if (y_bound < y) {
            *y_ptr = y_bound;
            clamp_flags |= 0x100;
        }
    }
    ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return clamp_flags;
}
