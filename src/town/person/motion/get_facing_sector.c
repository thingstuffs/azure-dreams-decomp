#include "common.h"
#include "shared/game_work.h"


/* Returns the quarter-turn sector of the stored angle relative to the offset input angle. */
u32 get_facing_sector(s32 angle) {
    s32 angle_delta;

    angle -= 0x600;
    angle_delta = (g_game_work.view.camera_rotation.parts.viewAngle - angle) & 0xFFF;
    return (u32)(angle_delta / 1024);
}
