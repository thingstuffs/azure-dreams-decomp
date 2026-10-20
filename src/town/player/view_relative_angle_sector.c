#include "common.h"
#include "shared/game_work.h"


/* Returns the sector of the wrapped angle difference with a 0x500 offset. */
u32 view_relative_angle_sector(s32 angle) {
    s32 angle_delta;

    angle -= 0x500;
    angle_delta = (g_game_work.view.camera_rotation.parts.viewAngle - angle) & 0xFFF;
    return (u32)(angle_delta / 512);
}
