#include "common.h"
#include "shared/game_work.h"


/* Returns the sector of the wrapped angle difference with a 0x500 offset. */
u32 func_80095360(s32 angle) {
    s32 angle_delta;

    angle -= 0x500;
    angle_delta = (gameWork.viewAngle - angle) & 0xFFF;
    if (angle_delta < 0) {
        angle_delta += 0x1FF;
    }
    return (u32)angle_delta >> 9;
}
