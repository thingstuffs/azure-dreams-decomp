#include "common.h"

typedef struct S_80040060 {
    struct S_80040060 *next;  /* 0x00 */
    struct S_80040060 *prev;  /* 0x04 */
    u8 pad[0x1E - 0x08];
    u16 flags;                /* 0x1E */
} S_80040060;

extern struct {
    S_80040060 *head;
    int pad[2];
} D_80081498;

/* Inserts node after anchor, sets flag 0x4000, and leaves prev null when anchor is the global head. */
void func_80040060(S_80040060 *anchor, S_80040060 *node)
{
    S_80040060 *next_node;

    node->flags |= 0x4000;

    next_node = anchor->next;
    anchor->next = node;
    if (next_node != 0) {
        next_node->prev = node;
        node->next = next_node;
    } else {
        node->next = 0;
    }

    if (anchor == D_80081498.head) {
        node->prev = 0;
    } else {
        node->prev = anchor;
    }
}
