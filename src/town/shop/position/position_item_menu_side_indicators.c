#include "common.h"
#include "shared/item_menu.h"
#include "town/shop/position.h"

/* Set the positions of the two side indicators (parts 38 and 39). */
void position_item_menu_side_indicators(ItemMenuPart **parts) {
    parts[38]->position->x = -0x40;
    parts[38]->position->y = 0x30;
    parts[39]->position->x = 0xC4;
    parts[39]->position->y = 0x30;
}
