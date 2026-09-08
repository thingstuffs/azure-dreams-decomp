#include "common.h"

typedef struct S_80044AAC {
    u8 pad00[0x14];
    struct S_80044AAC *prev; /* 0x14 */
    struct S_80044AAC *next; /* 0x18 */
    u16 type;                /* 0x1C */
} S_80044AAC;

extern S_80044AAC *D_800833E0[0x20];

extern void func_80044A50(S_80044AAC *node);

/* Unlink the node, then insert it after the anchor or at the head of its global type list. */
void func_80044AAC(S_80044AAC *anchor, S_80044AAC *node) {
    S_80044AAC *next_node;

    func_80044A50(node);

    if (anchor != 0) {
        next_node = anchor->next;
        anchor->next = node;
        node->prev = anchor;
        node->next = next_node;
        if (next_node != 0) {
            next_node->prev = node;
        }
    } else {
        next_node = D_800833E0[node->type];
        node->next = next_node;
        node->prev = (S_80044AAC *)&D_800833E0[node->type];
        D_800833E0[node->type] = node;
        next_node->prev = node;
    }
}
