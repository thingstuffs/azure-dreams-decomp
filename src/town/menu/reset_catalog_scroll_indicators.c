#include "common.h"
#include "town/menu.h"
#include "town/menu/catalog_parts.h"

/* Reset the controller fields and clear four shared state values. */
void reset_catalog_scroll_indicators(void *controller) {
    ItemMenuPart **state = catalog_display_node_slots;

    *((u8 *)controller + 0xC) = 1;
    *((s16 *)((u8 *)controller + 8)) = 0;
    *((u8 *)controller + 0xE) = 0;
    state[12]->handler = 0;
    state[13]->handler = 0;
    state[26]->handler = 0;
    state[27]->handler = 0;
}
