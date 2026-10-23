#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

extern void D_800B90B4();


/* Allocate an object and set its data pointer. */
void allocate_object_with_data_pointer(void) {
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->update_callback = &D_800B90B4;
    }
}
