#include "common.h"
#include "engine/node.h"

/* Unlinks the node from its doubly-linked list and clears its links. */
void unlink_node(ObjectNodeHeader *node) {
    ObjectNodeHeader *prev_node;
    ObjectNodeHeader *next_node;

    prev_node = node->draw_prev;
    if (prev_node != 0) {
        next_node = node->chain_next;
        if (next_node != 0) {
            next_node->draw_prev = prev_node;
        }
        if (prev_node >= (ObjectNodeHeader *)registered_draw_objects && prev_node < (ObjectNodeHeader *)((u8 *)registered_draw_objects + 0x80)) {
            *(ObjectNodeHeader **)prev_node = next_node;
        } else {
            prev_node->chain_next = next_node;
        }
        node->chain_next = 0;
        node->draw_prev = 0;
    }
}
