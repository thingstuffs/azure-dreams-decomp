#include "town/shop/item_menu_actions.h"

/* Sets the object's pointer at offset 0x10 to D_800AE494. */
void set_item_menu_secondary_handler(ItemMenuStateNode *owner) {
    owner->header.update_callback = &D_800AE494;
}
