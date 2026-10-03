#include "common.h"

extern s16 func_80065F90(s32, s32);

/* Clamp the fixed-point coordinate deltas to the minimum before passing them to the helper. */
s16 func_800C2B88(s32 x, s32 y, void *origin) {
    s32 x_delta;
    s32 y_delta;
    s32 clamped_y_delta;
    s32 minimum;
    s32 clamped_x_delta;

    x <<= 16;
    x_delta = x - *(s32 *)((u8 *)origin + 0);
    y_delta = (y << 16) - *(s32 *)((u8 *)origin + 4);
    minimum = (s32)0x80010000;

    if (x_delta > minimum) {
        clamped_x_delta = x_delta;
    } else {
        clamped_x_delta = minimum;
    }
    if (y_delta > minimum) {
        clamped_y_delta = y_delta;
    } else {
        clamped_y_delta = minimum;
    }
    return func_80065F90(clamped_x_delta, clamped_y_delta);
}
