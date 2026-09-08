#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    struct Node *prev;
    struct Node *next;
} Node;

extern Node D_800CFCB4[];

s32 func_8008EFA0(Node *arg0) {
    u32 page = 0x800D0000;

    if (arg0 != NULL) {
        Node *head;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        head = (Node *)(page - 0x34C);
        arg0->prev = head;
        arg0->next = head->next;
        head->next->prev = arg0;
        head->next = arg0;
        return 1;
    }
    return 0;
}
