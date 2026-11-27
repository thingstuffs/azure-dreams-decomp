#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"

/* extern */


/* Initialize the state fields before calling reset_catalog_scroll_indicators. */
void enter_catalog_detail_input(CatalogDisplay *state) {
    state->phase = 8;
    state->transition_frame = 0;
    state->transition_duration = 0;
    reset_catalog_scroll_indicators(state);
}
