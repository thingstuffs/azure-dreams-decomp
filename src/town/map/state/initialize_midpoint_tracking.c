#include "town/map/camera.h"
#include "town/map/state.h"
#include "town/map.h"



/* Install midpoint tracking and initialize its targets and position. */
void initialize_midpoint_tracking(TownCameraState *state) {
    state->track_target = track_camera_midpoint;
    state->target = &town_position_reference_state;
    state->previous_target = &town_position_reference_state;
    state->other = &town_position_reference_state;
    state->x = town_position_reference_state.x;
    state->y = state->other->y;
    state->z = state->other->z;
    set_view_triplet_source((IntVector3 *)&state->x);
}
