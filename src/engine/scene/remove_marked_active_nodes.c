#include "common.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "slus.h"

extern ObjectNodeHeader *active_node_list_head;

/* Detaches nodes flagged 0x8000 from the global list and frees those without flag 0x80 after detachment. */
void remove_marked_active_nodes(void)
{
    ObjectNodeHeader *node;
    ObjectNodeHeader *next;

    node = active_node_list_head;
    if (node != 0) {
        do {
            next = node->next;
            if (node->flags & NODE_REMOVE) {
                unlink_node(node);
                unlink_active_node(node);
                if (!(node->flags & 0x80)) {
                    push_node_onto_free_list(node);
                }
            }
            node = next;
        } while (node != 0);
    }
}
