#include "town/map/camera.h"
#include "town/map.h"

/* Set the camera chase callback and its default target. */
void tcame_chase_set(void) {
    town_camera_chase_state.track_target = reset_or_copy_state_values;
    town_camera_chase_state.target = &town_position_reference_state;
}
