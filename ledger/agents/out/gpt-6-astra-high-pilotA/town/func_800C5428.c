#include "common.h"

extern s16 func_80065F90(s32, s32, s32, s32);

/* Computes clamped 16.16 coordinate deltas and passes them to func_80065F90. */
s16 func_800C2B88(s32 x, s32 y, void *origin) {
    s32 delta_x;
    s32 delta_y;
    s32 clamped_y;
    s32 minimum;
    register s32 clamped_x ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    clamped_x = (s32)0x80010000;
    x <<= 16;
    ASM_KEEP(clamped_x);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    delta_x = x - *(s32 *)((u8 *)origin + 0);
    delta_y = (y << 16) - *(s32 *)((u8 *)origin + 4);
    minimum = clamped_x;
    if (delta_x > minimum) {
        clamped_x = delta_x;
    }
    clamped_y = (s32)0x80010000;
    if (delta_y > minimum) {
        clamped_y = delta_y;
    }
    return func_80065F90(clamped_x, clamped_y, minimum, clamped_x);
}
