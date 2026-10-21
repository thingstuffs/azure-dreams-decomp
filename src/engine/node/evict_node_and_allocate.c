#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"
#include "slus.h"

typedef struct Node {
    struct Node *next;      /* 0x00 */
    unsigned char pad[0x1E - 4];
    unsigned short field_1E; /* 0x1E */
} Node;

extern Node *active_node_list_head;

/* Removes the first eligible active node other than excluded_node, then retries allocation. */
void *evict_node_and_allocate(void *flags, void *excluded_node)
{
    Node *node;

    node = active_node_list_head;
    if (node != 0) {
        do {
            if ((node->field_1E & 0x200) && excluded_node != (void *)node) {
                unlink_node(node);
                unlink_active_node(node);
                if (!(node->field_1E & 0x80)) {
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
