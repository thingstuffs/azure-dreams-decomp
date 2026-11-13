#include "town/shop/item_menu_actions.h"
#include "town/shop/item.h"

/* Sets the object's data pointer to start_item_menu_object_processing. */
void set_item_menu_release_callback(ItemMenuStateNode *owner) {
    owner->header.update_callback = &release_item_menu_object;
}
