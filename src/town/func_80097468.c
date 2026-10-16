#include "common.h"
#include "shared/game_work.h"

extern s32 townDirectionalButtonsToAngle(s32);

/* Adds an offset to the shared angle and wraps to 12 bits, preserving failure. */
s32 townInputAngleWithOffset(s32 unused, s32 angle_offset) {
    s32 base_angle;

    base_angle = townDirectionalButtonsToAngle(gameWork.buttons);
    if ((s16)base_angle == -1) {
        return -1;
    }
    return (base_angle + angle_offset) & 0xFFF;
}
