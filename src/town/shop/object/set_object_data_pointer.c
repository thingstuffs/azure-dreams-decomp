#include "town/shop/display_objects.h"
#include "town/shop.h"
#include "town/shop/object.h"
typedef struct Obj_800B45A0 Obj_800B45A0;

/* Sets the object's pointer to advance_inner_value_and_complete. */
void set_object_data_pointer_2(ObjectNodeHeader *object) {
    object->update_callback = &advance_inner_value_and_complete;
}
