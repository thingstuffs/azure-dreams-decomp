/* Selector 59, retail file [0x1990D44, 0x1990D98); complete callable clone. */
#include "common.h"
#include "shared/object_node.h"

extern void func_8002406C(void *record, void *transform, void *object, s32 depth_bias);

/* Draw each linked record with zero depth bias; the next record is chained through the previous header's
 * unk_18 link, and its node supplies the transform and object pointers. */
s32 func_80024544(void *record, void *transform, void *object) {
    ObjectNodeHeader *node;

    for (;;) {
        func_8002406C(record, transform, object, 0);
        node = (ObjectNodeHeader *)((ObjectNodeHeader *)record - 1)->unk_18;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        transform = node->unk_08;
        object = node->unk_0C;
    }
}
