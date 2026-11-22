#include "common.h"
#include "m2c_compat.h"
#include "town/shop/item.h"

/* Re-enable the primary item menu after closing its selected display. */
void set_item_menu_record_active(ItemMenuObjectNode *object) {
    object->menu.enabled = 1;
}
