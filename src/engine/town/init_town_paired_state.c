#include "common.h"

#include "engine/town.h"
#include "town/map/state.h"


/* Dispatch to the town runtime routine. */
void init_town_paired_state(void) {
    initialize_town_camera_states();
}
