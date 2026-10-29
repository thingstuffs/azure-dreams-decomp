#include "town/map/camera.h"
#include "town/map.h"

/* Clear the camera target override. */
void tcame_chase_fix_reset(void) {
    town_camera_chase_state.override_target = 0;
}
