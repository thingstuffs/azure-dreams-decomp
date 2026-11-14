#include "town/map/camera.h"
#include "town/map.h"

/* Set midpoint tracking and both default targets. */
void tcame_chase2_set(void) {
    town_camera_chase_state.track_target = track_camera_midpoint;
    town_camera_chase_state.target = &town_position_reference_state;
    town_camera_chase_state.other = &town_position_reference_state;
}
