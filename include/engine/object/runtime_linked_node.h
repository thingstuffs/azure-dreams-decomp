#ifndef ENGINE_OBJECT_RUNTIME_LINKED_NODE_H
#define ENGINE_OBJECT_RUNTIME_LINKED_NODE_H

#include "common.h"

/* prepend_owner_list_node links this record into an owner head.
 * The backlink is either a preceding node or the owner head biased by eight bytes;
 * unlink_owner_list_node writes its +8 link to bypass this node. */
typedef struct RuntimeLinkedNode {
    u8 pad_00[4];
    void *backlink;
    struct RuntimeLinkedNode *next;
} RuntimeLinkedNode;

#endif
