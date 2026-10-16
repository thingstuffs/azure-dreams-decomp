/* Selector 59, retail file [0x1990D44, 0x1990D98); complete callable clone. */
#include "common.h"
#include "shared/object_node.h"

/* Draw each linked record with zero depth bias; the next record is chained through the previous header's
 * unk_18 link, and its node supplies the transform and object pointers. */
s32 dungeonDrawLinkedRecordsZeroDepthBias(void *record, void *transform, void *object) {
    ObjectNodeHeader *node;

    for (;;) {
        dungeonProjectAndQueueVisibleShadedQuad(record, transform, object, 0);
        node = ((ObjectNodeHeader *)record - 1)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        transform = node->unk_08;
        object = node->unk_0C;
    }
}

