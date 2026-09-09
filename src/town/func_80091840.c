#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

extern Node D_800CFCB4[];

/* Insert a nonnull node immediately after the list head. */
s32 func_8008EFA0(Node *node) {
    u32 page = 0x800D0000;

    if (node != NULL) {
        Node *head;
        head = D_800CFCB4;
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        return 1;
    }
    return 0;
}
