#include "common.h"
#include "town/shop.h"
#include "town/shop/storage_menu.h"                         /* extern */

void update_storage_display_node(ObjectNodeHeader *node) {
    update_storage_display(NODE_BODY(node));
}
