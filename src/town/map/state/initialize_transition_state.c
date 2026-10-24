#include "town/map/camera.h"

extern void apply_and_store_setting(IntVector3 *setting);

/* Install midpoint tracking and initialize its targets and position. */
void initialize_transition_state(TownCameraState *state) {
    state->track_target = restart_or_update_midpoint_tracking;
    state->target = &town_position_reference_state;
    state->previous_target = &town_position_reference_state;
    state->other = &town_position_reference_state;
    state->x = town_position_reference_state.x;
    state->y = state->other->y;
    state->z = state->other->z;
    apply_and_store_setting((IntVector3 *)&state->x);
}
