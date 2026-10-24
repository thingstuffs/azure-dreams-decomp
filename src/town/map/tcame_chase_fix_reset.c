#include "town/map/camera.h"

/* Clear the camera target override. */
void tcame_chase_fix_reset(void) {
    town_camera_chase_state.override_target = 0;
}
