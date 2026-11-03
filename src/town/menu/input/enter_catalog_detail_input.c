#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"

/* extern */


/* Initialize the state fields before calling reset_catalog_scroll_indicators. */
void enter_catalog_detail_input(CatalogDisplay *state) {
    state->unk_0A.as_s8 = 8;
    state->unk_04.as_s16 = 0;
    state->unk_06.as_s16 = 0;
    reset_catalog_scroll_indicators(state);
}
