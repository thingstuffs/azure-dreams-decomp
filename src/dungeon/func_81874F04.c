#include "modules/dungeon_native_abi.h"
#include "modules/dungeon_ovl_1894800.h"
#include "common.h"
#include "shared/object_node.h"

extern void func_80024188(void *record, void *context, void *data, s16 depth_bias);

/* Retail 81874F04 (func_80024704).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 func_80024704(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        func_80024188(record, context, data, 0);
        node = (ObjectNodeHeader *)((ObjectNodeHeader *)record - 1)->unk_18;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->unk_08;
        data = node->unk_0C;
    }
}
