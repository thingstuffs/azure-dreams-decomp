#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/event.h"


/* Check whether the first entry's state byte is 2. */
s32 is_event_state_two(void) {
    return town_event_state->selected_entry == 2;
}
