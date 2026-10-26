#include "common.h"
#include "engine/effect.h"
#include "engine/node.h"

/* Unlink the node, then insert it after the anchor or at the head of its global type list. */
void link_typed_list_node(ObjectNodeHeader *anchor, ObjectNodeHeader *node) {
    ObjectNodeHeader *next_node;

    unlink_node(node);

    if (anchor != 0) {
        next_node = anchor->chain_next;
        anchor->chain_next = node;
        node->draw_prev = anchor;
        node->chain_next = next_node;
        if (next_node != 0) {
            next_node->draw_prev = node;
        }
    } else {
        next_node = registered_draw_objects[node->draw_slot];
        node->chain_next = next_node;
        node->draw_prev = (ObjectNodeHeader *)&registered_draw_objects[node->draw_slot];
        registered_draw_objects[node->draw_slot] = node;
        next_node->draw_prev = node;
    }
}
