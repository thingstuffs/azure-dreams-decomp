#include "town/shop/display_objects.h"
#include "town/shop.h"
#include "town/shop/object.h"
typedef struct Obj_800B45A0 Obj_800B45A0;

/* Sets the object's pointer to ease_value_and_remove_node. */
void set_advance_inner_value_callback(ObjectNodeHeader *object) {
    object->update_callback = &ease_value_and_remove_node;
}
