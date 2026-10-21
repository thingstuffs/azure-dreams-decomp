#include "common.h"

extern s32 town_camera_chase_state[];
extern u8 town_position_reference_state[];
/* tcame_chase_tgt_reset: Reset the camera chase target to D_80100D98. */
void tcame_chase_tgt_reset(void) {
    *town_camera_chase_state = (s32) town_position_reference_state;
}
