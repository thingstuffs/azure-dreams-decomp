#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"
#include "slus.h"

extern ObjectNodeHeader *active_node_list_head;

/* Removes the first eligible active node other than excluded_node, then retries allocation. */
void *evict_node_and_allocate(void *flags, void *excluded_node)
{
    ObjectNodeHeader *node;

    node = active_node_list_head;
    if (node != 0) {
        do {
            if ((node->flags & 0x200) && excluded_node != (void *)node) {
                unlink_node(node);
                unlink_active_node(node);
                if (!(node->flags & 0x80)) {
                    push_node_onto_free_list(node);
                }
                if (excluded_node != 0) {
                    node = allocate_list_node(flags, excluded_node);
                } else {
                    node = allocate_flagged_object_node(flags);
                }
                return node;
            }
            node = node->next;
        } while (node != 0);
    }
    return 0;
}
