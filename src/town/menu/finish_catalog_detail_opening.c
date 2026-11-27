#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"

/* extern */


/* Advance the counter and initialize state eight when the limit is reached. */
void finish_catalog_detail_opening(CatalogDisplay *controller) {
    u16 next_count;

    next_count = controller->transition_frame + 1;
    controller->transition_frame = next_count;
    if ((s16) next_count == controller->transition_duration) {
        controller->texture_load_phase = 0;
        controller->phase = 8;
        controller->transition_duration = 0;
        controller->transition_frame = 0U;
        reset_catalog_scroll_indicators(controller);
    }
}
