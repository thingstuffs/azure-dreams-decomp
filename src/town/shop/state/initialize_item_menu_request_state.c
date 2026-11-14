#include "common.h"
#include "shared/item_menu.h"
#include "town/shop/state.h"
#include "town/shop/item.h"



/* Binds the item-menu object to its owning menu node and state, enables it and installs its update callback. */
void initialize_item_menu_request_state(ItemMenuObject *object, ItemMenuStateNode *owner) {
    object->owner = owner;
    object->menu = &owner->state;
    object->enabled = 1;
    ITEM_MENU_OBJECT_NODE(object)->header.update_callback = advance_item_menu_open_ramp;
}
