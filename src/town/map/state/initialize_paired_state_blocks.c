#include "town/map/camera.h"
#include "town/map.h"
#include "town/map/state.h"

extern s32 town_secondary_callback_state[];

/* Initialize both state blocks and finish setup. */
void initialize_paired_state_blocks(void) {
    s32 *state = town_secondary_callback_state;

    initialize_control_block(&town_camera_chase_state);
    initialize_paired_state_callbacks(state);
    clear_transition_word();
}
