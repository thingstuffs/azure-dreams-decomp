#include "common.h"
extern u8 D_800CFCB4[];

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    s32 pad[2];
} List;

/* Insert a non-null node before the global list sentinel. */
s32 func_8008EFE0(Node *node) {
    Node *head;

    if (node != NULL) {
        head = ((List *)D_800CFCB4)->head;
        node->next = (Node *)D_800CFCB4;
        node->prev = head;
        ((List *)D_800CFCB4)->head->next = node;
        ((List *)D_800CFCB4)->head = node;
        return 1;
    }
    return 0;
}
