#include "common.h"

extern s16 D_80083228[5];

/* Returns the quarter-turn sector of the stored angle relative to the offset input angle. */
u32 func_800C2D0C(s32 angle) {
    s32 angle_delta;

    angle -= 0x600;
    angle_delta = (D_80083228[0] - angle) & 0xFFF;
    if (angle_delta < 0) {
        angle_delta += 0x3FF;
    }
    return (u32)angle_delta >> 10;
}
