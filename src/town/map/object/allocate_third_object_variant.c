#include "shared/object_node.h"
#include "common.h"
void no_op_entry_callback(void);


/* Allocate an object and set its data pointer. */
void allocate_third_object_variant(void) {
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != 0) {
        object->update_callback = &no_op_entry_callback;
    }
}
