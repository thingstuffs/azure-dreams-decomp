#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"

/* extern */


/* Advance the counter and invoke completion when it reaches the target, then reset the state. */
void finish_catalog_detail_transition(CatalogDisplay *state) {
    u16 next_count;

    next_count = state->transition_frame + 1;
    state->transition_frame = next_count;
    if ((s16) next_count == state->transition_duration) {
        reset_catalog_scroll_indicators(state);
        state->phase = 8;
        state->transition_duration = 0;
        state->transition_frame = 0U;
    }
}
