#include "common.h"
#include "shared/game_work.h"


/* to_camera_zero_00: Moves the camera offset toward zero in steps of 16. */
s32 func_800909A0(void) {
    GameWork *camera_state = &gameWork;
    s16 camera_offset = camera_state->viewAngle;
    u16 next_offset = ((u16)camera_state->viewAngle);

    if (camera_offset != 0) {
        if (camera_offset > 0) {
            next_offset -= 0x10;
            camera_state->viewAngle = next_offset;
            if ((s16)next_offset < 0) {
                camera_state->viewAngle = 0;
            }
        } else if (camera_offset < 0) {
            next_offset += 0x10;
            camera_state->viewAngle = next_offset;
            if ((s16)next_offset > 0) {
                camera_state->viewAngle = 0;
            }
        }
    }

    return camera_state->viewAngle;
}
