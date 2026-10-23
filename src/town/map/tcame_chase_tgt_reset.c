#include "common.h"

extern s32 town_camera_chase_state[];
extern u8 town_position_reference_state[];
/* Sets the town camera chase target to town_position_reference_state. */
void tcame_chase_tgt_reset(void) {
    *town_camera_chase_state = (s32) town_position_reference_state;
}
