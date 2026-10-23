#include "shared/town_event_state.h"
#include "common.h"

extern u8 D_8001FD7A[];

/* Reset byte 5 and set byte 1 of the first entry, then return D_8001FD7A. */
u8 *reset_event_entry_and_get_resource(void) {
    town_event_state->selection_mode = 0;
    town_event_state->dispatchState = 2;
    return D_8001FD7A;
}
