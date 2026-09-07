#include "common.h"

/* Doubly-linked list node: next at 0x0, prev at 0x4, flags at 0x1E */
typedef struct S_8003FFF0 {
    struct S_8003FFF0 *next;      /* 0x00 */
    struct S_8003FFF0 *prev;      /* 0x04 */
    u8 pad[0x1E - 0x08];
    u16 flags;                    /* 0x1E */
} S_8003FFF0;

extern S_8003FFF0 *D_80081498[4];

/* Unlinks a node from its doubly-linked list (or the global list head), clearing a flag bit. */
void func_8003FFF0(S_8003FFF0 *node) {
    S_8003FFF0 *prev = node->prev;
    S_8003FFF0 *next;

    node->flags &= 0xBFFF;

    if (prev != 0) {
        next = node->next;
        if (next != 0) {
            next->prev = prev;
        }
        prev->next = next;
    } else {
        next = node->next;
        D_80081498[0] = next;
        if (next != 0) {
            next->prev = 0;
        }
    }

    node->next = 0;
    node->prev = 0;
}
