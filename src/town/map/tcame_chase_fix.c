#include "town/map/camera.h"
#include "town/map.h"

/* Use the supplied position as the camera target override. */
void tcame_chase_fix(IntVector3 *target) {
    town_camera_chase_state.override_target = target;
}
