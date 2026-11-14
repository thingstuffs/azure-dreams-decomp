#include "common.h"
#include "m2c_compat.h"

#include "shared/object_links.h"
#include "engine/object.h"
#include "engine/object/runtime_linked_node.h"

   /* arg0 in unlink_owner_list_node */

/* Unlink a node from a doubly linked list by connecting its neighbors. */
void unlink_owner_list_node(void *node_data) {
    RuntimeLinkedNode *node = node_data;
    ((ListBacklinkView *)node->backlink)->unk_08 = node->next;
    node->next->backlink = node->backlink;
}
