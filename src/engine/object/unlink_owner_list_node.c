#include "engine/object.h"
#include "engine/object/runtime_linked_node.h"

void unlink_owner_list_node(void *node_data) {
    RuntimeLinkedNode *node = node_data;
    node->backlink->next = node->next;
    node->next->backlink = node->backlink;
}
