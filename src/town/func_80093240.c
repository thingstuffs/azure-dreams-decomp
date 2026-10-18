#include "modules/town_player_init.h"

/* func_800909A0: Moves the camera offset toward zero in steps of 16. */
s32 func_800909A0() {
    GameWork *camera_state = &g_game_work;
    s16 camera_offset = camera_state->view.viewAngle;
    u16 next_offset = ((u16)camera_state->view.viewAngle);

    if (camera_offset != 0) {
        if (camera_offset > 0) {
            next_offset -= 0x10;
            camera_state->view.viewAngle = next_offset;
            if ((s16)next_offset < 0) {
                camera_state->view.viewAngle = 0;
            }
        } else if (camera_offset < 0) {
            next_offset += 0x10;
            camera_state->view.viewAngle = next_offset;
            if ((s16)next_offset > 0) {
                camera_state->view.viewAngle = 0;
            }
        }
    }

    return camera_state->view.viewAngle;
}
