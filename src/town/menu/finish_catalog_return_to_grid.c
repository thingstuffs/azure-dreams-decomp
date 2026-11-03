#include "common.h"
#include "m2c_compat.h"
#include "town/menu.h"
#include "town/menu/catalog.h"


/* Advance the counter and switch to state one when the limit is reached. */
void finish_catalog_return_to_grid(CatalogDisplay *controller) {
    u16 next_count;

    next_count = controller->unk_04.as_u16 + 1;
    controller->unk_04.as_u16 = next_count;
    if ((s16) next_count == controller->unk_06.as_s16) {
        controller->unk_0A.as_s8 = 1;
        controller->unk_06.as_s16 = 0;
        controller->unk_04.as_u16 = 0U;
    }
}
