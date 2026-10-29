#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/event.h"

/* Set unk_02 to 0xFF before forwarding three values to advance_to_next_enabled_entry. */
void reset_event_selection_and_advance(void) {
    town_event_state->entry_index = 0xFF;
    advance_to_next_enabled_entry();
}
