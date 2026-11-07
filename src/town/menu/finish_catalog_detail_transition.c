#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"

/* extern */


/* Advance the counter and invoke completion when it reaches the target, then reset the state. */
void finish_catalog_detail_transition(CatalogDisplay *state) {
    u16 next_count;

    next_count = state->unk_04 + 1;
    state->unk_04 = next_count;
    if ((s16) next_count == state->unk_06) {
        reset_catalog_scroll_indicators(state);
        state->unk_0A = 8;
        state->unk_06 = 0;
        state->unk_04 = 0U;
    }
}
