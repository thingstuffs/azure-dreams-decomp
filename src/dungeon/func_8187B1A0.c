#include "common.h"
#include "shared/object_node.h"

#include "modules/dungeon_ovl_189a800.h"

/* Retail 8187B1A0 (decrement_object_counter).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 decrement_object_counter(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        transform_and_queue_mesh_primitives(record, context, data, 0);
        node = ((ObjectNodeHeader *)record - 1)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->unk_08;
        data = node->unk_0C;
    }
}
