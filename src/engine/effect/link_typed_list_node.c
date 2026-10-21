#include "common.h"
#include "engine/effect.h"
#include "engine/node.h"

typedef struct S_80044AAC {
    u8 pad00[0x14];
    struct S_80044AAC *prev; /* 0x14 */
    struct S_80044AAC *next; /* 0x18 */
    u16 type;                /* 0x1C */
} S_80044AAC;

extern S_80044AAC *registered_draw_objects[0x20];

/* Unlink the node, then insert it after the anchor or at the head of its global type list. */
void link_typed_list_node(S_80044AAC *anchor, S_80044AAC *node) {
    S_80044AAC *next_node;

    unlink_node(node);

    if (anchor != 0) {
        next_node = anchor->next;
        anchor->next = node;
        node->prev = anchor;
        node->next = next_node;
        if (next_node != 0) {
            next_node->prev = node;
        }
    } else {
        next_node = registered_draw_objects[node->type];
        node->next = next_node;
        node->prev = (S_80044AAC *)&registered_draw_objects[node->type];
        registered_draw_objects[node->type] = node;
        next_node->prev = node;
    }
}
