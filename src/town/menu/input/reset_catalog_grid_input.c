#include "common.h"
#include "m2c_compat.h"
#include "town/menu/catalog.h"


/* Initialize state with its byte field set to one and both 16-bit fields cleared. */
void reset_catalog_grid_input(CatalogDisplay *state) {
    state->phase = 1;
    state->transition_frame = 0;
    state->transition_duration = 0;
}
