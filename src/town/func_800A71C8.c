#include "common.h"

extern s32 D_80100DB8[];
extern s32 D_80100DE0[];

extern void initialize_control_block(s32 *control);
extern void initialize_paired_state_callbacks(s32 *state);
extern void clear_transition_word(void);

/* Initialize both state blocks and finish setup. */
void initialize_paired_state_blocks(void) {
    s32 *state = D_80100DB8;

    initialize_control_block(D_80100DE0);
    initialize_paired_state_callbacks(state);
    clear_transition_word();
}
