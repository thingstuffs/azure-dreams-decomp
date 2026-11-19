#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"

/* Set the object's value, preserve its previous value, and reset its state. */
void card_boot_begin_selected_value_transition(ObjectNodeHeader *panel, s32 value) {
    CardCommandPanelBody *state;
    s32 previous_value;

    if (panel != 0) {
        state = NODE_BODY(panel);
        previous_value = state->selected_entry;
        state->animation_tick = 0;
        state->animation_frames = 3;
        state->selected_entry = value;
        state->previous_selection = previous_value;
    }
}
