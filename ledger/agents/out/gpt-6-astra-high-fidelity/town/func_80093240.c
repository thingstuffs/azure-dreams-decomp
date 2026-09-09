#include "common.h"

extern u8 D_80083160[];

/* to_camera_zero_00: Moves the camera offset toward zero in steps of 16. */
s32 func_800909A0(void) {
    s16 *camera_state = (s16 *)D_80083160;
    s16 camera_offset = camera_state[0x64];
    u16 next_offset = ((u16 *)camera_state)[0x64];

    if (camera_offset != 0) {
        if (camera_offset > 0) {
            next_offset -= 0x10;
            camera_state[0x64] = next_offset;
            if ((s16)next_offset < 0) {
                camera_state[0x64] = 0;
            }
        } else if (camera_offset < 0) {
            next_offset += 0x10;
            camera_state[0x64] = next_offset;
            if ((s16)next_offset > 0) {
                camera_state[0x64] = 0;
            }
        }
    }

    return camera_state[0x64];
}
