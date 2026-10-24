#include "town/map/camera.h"

/* Set midpoint tracking and both default targets. */
void tcame_chase2_set(void) {
    town_camera_chase_state.track_target = restart_or_update_midpoint_tracking;
    town_camera_chase_state.target = &town_position_reference_state;
    town_camera_chase_state.other = &town_position_reference_state;
}
