#include "common.h"
#include "town/shop.h"
#include "town/shop/item.h"

/* Sets the object's data pointer when the object is present. */
void schedule_item_menu_child_release(ObjectNodeHeader *object) {
    if (object != 0) {
        object->update_callback = &release_item_menu_display;
    }
}
