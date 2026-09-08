#include "common.h"

extern s32 D_80083168;
extern s32 func_80094B58(s32);

/* Adds an offset to the shared angle and wraps to 12 bits, preserving failure. */
s32 func_80094BC8(s32 unused, s32 angle_offset) {
    s32 base_angle;

    base_angle = func_80094B58(D_80083168);
    if ((s16)base_angle == -1) {
        return -1;
    }
    return (base_angle + angle_offset) & 0xFFF;
}
