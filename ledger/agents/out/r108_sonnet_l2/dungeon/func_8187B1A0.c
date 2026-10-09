#include "common.h"
#include "shared/object_node.h"

extern void func_800241A8(void *record, void *context, void *data, s32 depth_bias);

/* Retail 8187B1A0 (func_800249A0).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 func_800249A0(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        func_800241A8(record, context, data, 0);
        node = (ObjectNodeHeader *)((ObjectNodeHeader *)record - 1)->unk_18;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->unk_08;
        data = node->unk_0C;
    }
}
