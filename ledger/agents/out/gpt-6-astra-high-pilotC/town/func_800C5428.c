#include "common.h"

extern s16 func_80065F90(s32, s32, s32, s32);

/* Clamp the fixed-point coordinate deltas to the minimum before passing them to the helper. */
s16 func_800C2B88(s32 x, s32 y, void *origin) {
    s32 x_delta;
    s32 y_delta;
    s32 clamped_y_delta;
    s32 minimum;
    register s32 clamped_x_delta ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    clamped_x_delta = (s32)0x80010000;
    x <<= 16;
    ASM_KEEP(clamped_x_delta);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    x_delta = x - *(s32 *)((u8 *)origin + 0);
    y_delta = (y << 16) - *(s32 *)((u8 *)origin + 4);
    minimum = clamped_x_delta;
    if (x_delta > minimum) {
        clamped_x_delta = x_delta;
    }
    clamped_y_delta = (s32)0x80010000;
    if (y_delta > minimum) {
        clamped_y_delta = y_delta;
    }
    return func_80065F90(clamped_x_delta, clamped_y_delta, minimum, clamped_x_delta);
}
