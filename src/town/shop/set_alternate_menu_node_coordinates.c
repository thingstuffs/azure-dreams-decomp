#include "common.h"
#include "town/menu.h"
#include "town/shop.h"


void set_alternate_menu_node_coordinates(ObjectNodeHeader *node) {
    set_alternate_menu_entry_coordinates(NODE_BODY(node));
}
