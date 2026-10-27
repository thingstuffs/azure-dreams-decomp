#include "town/shop/item_menu_actions.h"

/* Sets the object's data pointer to start_item_menu_object_processing. */
void set_item_menu_data_pointer(ItemMenuStateNode *owner) {
    owner->header.update_callback = &release_item_menu_object;
}
