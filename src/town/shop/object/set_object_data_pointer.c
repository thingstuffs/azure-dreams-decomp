#include "town/shop/display_objects.h"
typedef struct Obj_800B45A0 Obj_800B45A0;
void advance_inner_value_and_complete(Obj_800B45A0 *obj);


/* Sets the object's pointer to advance_inner_value_and_complete. */
void set_object_data_pointer_2(ObjectNodeHeader *object) {
    object->update_callback = &advance_inner_value_and_complete;
}
