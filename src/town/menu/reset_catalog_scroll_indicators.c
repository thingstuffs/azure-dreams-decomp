#include "common.h"
#include "town/menu.h"
#include "town/menu/catalog_parts.h"
#include "town/menu/catalog.h"

/* Reset the controller fields and clear four shared state values. */
void reset_catalog_scroll_indicators(CatalogDisplay *controller) {
    ItemMenuPart **state = catalog_display_node_slots;

    controller->unk_0C = 1;
    controller->unk_08 = 0;
    controller->unk_0E = 0;
    state[12]->handler = 0;
    state[13]->handler = 0;
    state[26]->handler = 0;
    state[27]->handler = 0;
}
