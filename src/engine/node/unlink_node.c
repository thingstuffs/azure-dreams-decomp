#include "common.h"
#include "engine/node.h"

typedef struct S_800833E0 {
    u8 pad00[0x14];
    struct S_800833E0 *prev; /* 0x14 */
    struct S_800833E0 *next; /* 0x18 */
    u16 type;                /* 0x1C */
} S_800833E0;

extern S_800833E0 *registered_draw_objects[0x20];

/* Unlinks the node from its doubly-linked list and clears its links. */
void unlink_node(S_800833E0 *node) {
    S_800833E0 *prev_node;
    S_800833E0 *next_node;

    prev_node = node->prev;
    if (prev_node != 0) {
        next_node = node->next;
        if (next_node != 0) {
            next_node->prev = prev_node;
        }
        if (prev_node >= (S_800833E0 *)registered_draw_objects && prev_node < (S_800833E0 *)((u8 *)registered_draw_objects + 0x80)) {
            *(S_800833E0 **)prev_node = next_node;
        } else {
            prev_node->next = next_node;
        }
        node->next = 0;
        node->prev = 0;
    }
}
