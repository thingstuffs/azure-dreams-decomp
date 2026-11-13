#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/map/object.h"
#include "town/map.h"

/* Allocate an object and set its data pointer. */
void create_idle_map_object(void) {
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->update_callback = &no_op_map_callback;
    }
}
