#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void D_800B93B8();


/* Allocate an object and set its data pointer. */
void allocate_second_object_variant(void) {
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->update_callback = &D_800B93B8;
    }
}
