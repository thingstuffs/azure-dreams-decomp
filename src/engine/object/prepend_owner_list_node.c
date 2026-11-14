#include "common.h"
#include "m2c_compat.h"

#include "records/Rec_func_80034F58_arg0.h"
#include "engine/object.h"
#include "engine/object/runtime_linked_node.h"


/* Insert a node at the front of the owner's doubly linked list. */
void prepend_owner_list_node(void *owner_arg, void *node_data) {
    Rec_func_80034F58_arg0 *owner = owner_arg;
    RuntimeLinkedNode *node = node_data;
    node->backlink = owner_arg + 8;
    node->next = owner->unk_10;
    ((RuntimeLinkedNode *)(owner->unk_10))->backlink = node;
    owner->unk_10 = node;
}
