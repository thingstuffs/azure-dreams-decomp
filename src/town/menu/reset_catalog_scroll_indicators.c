#include "common.h"
#include "town/menu.h"
#include "town/menu/catalog_parts.h"
#include "town/menu/catalog.h"

/* Reset the controller fields and clear four shared state values. */
void reset_catalog_scroll_indicators(CatalogDisplay *controller) {
    ItemMenuPart **state = catalog_display_node_slots;

    controller->scroll_indicator_visible = 1;
    controller->scroll_blink_timer = 0;
    controller->scroll_direction_mask = 0;
    state[12]->handler = 0;
    state[13]->handler = 0;
    state[26]->handler = 0;
    state[27]->handler = 0;
}
