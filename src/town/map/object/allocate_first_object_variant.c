#include "shared/object_node.h"
#include "common.h"
#include "town/map.h"
#include "town/map/object.h"

/* Allocate an object and set its data pointer. */
void allocate_first_object_variant(void) {
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        object->update_callback = &update_wrapping_indices_and_input;
    }
}
