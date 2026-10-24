#include "town/map/camera.h"

/* Restore the default camera target. */
void tcame_chase_tgt_reset(void) {
    town_camera_chase_state.target = &town_position_reference_state;
}
