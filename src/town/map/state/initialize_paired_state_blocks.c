#include "town/map/camera.h"

extern s32 town_secondary_callback_state[];

extern void initialize_paired_state_callbacks(s32 *state);
extern void clear_transition_word(void);

/* Initialize both state blocks and finish setup. */
void initialize_paired_state_blocks(void) {
    s32 *state = town_secondary_callback_state;

    initialize_control_block(&town_camera_chase_state);
    initialize_paired_state_callbacks(state);
    clear_transition_word();
}
