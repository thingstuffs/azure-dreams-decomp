#include "town/map/camera.h"
#include "town/map.h"

/* Set the camera chase callback and its default target. */
void tcame_chase_set(void) {
    town_camera_chase_state.track_target = follow_camera_target;
    town_camera_chase_state.target = &town_position_reference_state;
}
