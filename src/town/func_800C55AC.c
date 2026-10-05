#include "common.h"
#include "shared/game_work.h"


/* Returns the quarter-turn sector of the stored angle relative to the offset input angle. */
u32 func_800C2D0C(s32 angle) {
    s32 angle_delta;

    angle -= 0x600;
    angle_delta = (gameWork.view.viewAngle - angle) & 0xFFF;
    return (u32)(angle_delta / 1024);
}
