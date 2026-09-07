#include "common.h"

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

extern void func_8008F014(void) __attribute__((noreturn));
extern List D_800CFCB4;

s32 func_8008EFE0(Node *node) {
    register s32 dispatch_result ASM_REG("$2");
    register u32 page ASM_REG("$3") = 0x800D0000;
    register Node *head ASM_REG("$4");

    if (node == NULL) {
        dispatch_result = 0;
        ASM_TAILSLOT_PIN(dispatch_result);
        func_8008F014();
    }

    ASM_KEEP(page);
    head = ((List *)(page - 0x34C))->head;
    node->next = (Node *)(page - 0x34C);
    node->prev = head;
    ((List *)(page - 0x34C))->head->next = node;
    ((List *)(page - 0x34C))->head = node;
    return 1;
}
