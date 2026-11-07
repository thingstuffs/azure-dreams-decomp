#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"

/* extern */


/* Advance the counter and initialize state eight when the limit is reached. */
void finish_catalog_detail_opening(CatalogDisplay *controller) {
    u16 next_count;

    next_count = controller->unk_04 + 1;
    controller->unk_04 = next_count;
    if ((s16) next_count == controller->unk_06) {
        controller->unk_0B = 0;
        controller->unk_0A = 8;
        controller->unk_06 = 0;
        controller->unk_04 = 0U;
        reset_catalog_scroll_indicators(controller);
    }
}
