#include "common.h"
#include "shared/object_node.h"
#include "shared/item_menu.h"
#include "town/shop/item_menu_actions.h"
#include "town/shop/object.h"
#ifndef NULL
#define NULL 0
#endif
extern s32 item_menu_record_callback[4];

/* Create an item-menu object, install its update handler and start its display ramp fully open. */
ItemMenuObjectNode *create_item_menu_handler_object(ItemMenuStateNode *owner) {
    ItemMenuObjectNode *object = create_item_menu_child_object(owner);
    if (object != NULL) {
        ItemMenuDisplayBlock *display = object->menu.links.display;
        object->header.update_callback = item_menu_record_callback;
        display->ramp = 0x1000;
    }
    return object;
}
