#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"


/* Advance the counter and switch to state one when the limit is reached. */
void finish_catalog_return_to_grid(CatalogDisplay *controller) {
    u16 next_count;

    next_count = controller->transition_frame + 1;
    controller->transition_frame = next_count;
    if ((s16) next_count == controller->transition_duration) {
        controller->phase = 1;
        controller->transition_duration = 0;
        controller->transition_frame = 0U;
    }
}
