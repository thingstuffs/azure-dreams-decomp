#include "common.h"
#include "town/menu/digit_parts.h"
#include "town/shop.h"

void position_decimal_digits_node(ObjectNodeHeader *node) {
    place_item_menu_cursor_parts(NODE_BODY(node));
}
