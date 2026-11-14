#include "common.h"

#include "engine/town.h"

void initialize_town_camera_states(void);

/* Dispatch to the town runtime routine. */
void init_town_paired_state(void) {
    initialize_town_camera_states();
}
