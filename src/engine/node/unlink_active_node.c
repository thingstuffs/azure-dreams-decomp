#include "common.h"
#include "engine/node.h"



extern ObjectNodeHeader *active_node_list_head;

/* Unlinks a node from its doubly-linked list, clears flag 0x4000, and resets its links. */
void unlink_active_node(ObjectNodeHeader *node) {
    ObjectNodeHeader **prev = node->pprev;
    ObjectNodeHeader *next;

    node->flags &= 0xBFFF;

    if (prev != 0) {
        next = node->next;
        if (next != 0) {
            next->pprev = prev;
        }
        *prev = next;
    } else {
        next = node->next;
        active_node_list_head = next;
        if (next != 0) {
            next->pprev = 0;
        }
    }

    node->next = 0;
    node->pprev = 0;
}
