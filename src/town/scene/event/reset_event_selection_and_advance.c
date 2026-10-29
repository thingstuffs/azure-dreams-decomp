#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/scene/event.h"

/* Clear the selected entry (0xFF), advance to the next enabled entry and return what that advance returns. */
s32 reset_event_selection_and_advance(void) {
    town_event_state->entry_index = 0xFF;
    return advance_to_next_enabled_entry();
}
