#include "town/map/camera.h"
#include "town/map.h"
#include "town/map/state.h"
#include "town/data.h"

/* Initialize both state blocks and finish setup. */
void initialize_town_camera_states(void) {
    MapSecondaryCallbackState *state = &town_secondary_callback_state;

    init_town_camera_chase_state(&town_camera_chase_state);
    initialize_secondary_view_state(state);
    reset_view_brightness();
}
