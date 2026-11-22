#include "common.h"
#include "m2c_compat.h"
#include "town/shop/object.h"
#include "town/shop.h"


/* Set the object's data pointer when the object is present. */
void set_apply_record_values_callback(ObjectNodeHeader *object) {
    if (object != NULL) {
        object->update_callback = &close_item_move_menu;
    }
}
