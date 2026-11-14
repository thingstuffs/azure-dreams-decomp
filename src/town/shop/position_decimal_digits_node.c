#include "common.h"
#include "town.h"
#include "town/shop.h"

/* Calls place_item_menu_cursor_parts with base + 0x20. */
void position_decimal_digits_node(s32 base) {
    place_item_menu_cursor_parts(base + 0x20);
}
