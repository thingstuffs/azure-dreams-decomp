#include "shared/object_node.h"
#include "common.h"
#include "engine/item.h"
#include "engine/scene.h"

/* Allocates a pool node, installs its record and callback when both values exist, and returns its payload or NULL. */
void *create_node_with_record_pair(s32 *watched_value, s32 initial_count, unsigned long unused_value)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        if (watched_value != 0 && initial_count != 0) {
            NodeRemovalCounter *counter = (NodeRemovalCounter *)node->position;
            counter->count = initial_count;
            counter->watched_value = watched_value;
            node->update_callback = mark_and_release_record_pair;
        }
        node = NODE_BODY(node);
    }
    return node;
}
