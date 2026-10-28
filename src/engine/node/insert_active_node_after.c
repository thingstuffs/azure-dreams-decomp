#include "common.h"
#include "engine/node.h"



extern struct {
    ObjectNodeHeader *head;
    int pad[2];
} active_node_list_head;

/* Inserts node after anchor, sets flag 0x4000, and leaves prev null when anchor is the global head. */
void insert_active_node_after(ObjectNodeHeader *anchor, ObjectNodeHeader *node)
{
    ObjectNodeHeader *next_node;

    node->flags |= 0x4000;

    next_node = anchor->next;
    anchor->next = node;
    if (next_node != 0) {
        next_node->pprev = &node->next;
        node->next = next_node;
    } else {
        node->next = 0;
    }

    if (anchor == active_node_list_head.head) {
        node->pprev = 0;
    } else {
        node->pprev = &anchor->next;
    }
}
