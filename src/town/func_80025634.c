/* Relink of matched town/func_80097C00; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/game_work.h"


/* Returns the sector of the wrapped angle difference with a 0x500 offset. */
u32 func_800C2D94(s32 angle) {
    s32 angle_delta;

    angle -= 0x500;
    angle_delta = (gameWork.view.viewAngle - angle) & 0xFFF;
    return (u32)(angle_delta / 512);
}
