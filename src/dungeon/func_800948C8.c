#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    /* 0x00 */ char pad0[0x58];
    /* 0x58 */ struct Node *prev;
    /* 0x5C */ struct Node *next;
    /* 0x60 */ char pad60[0x18];
    /* 0x78 */ struct Node *unk78;
    /* 0x7C */ struct Node *unk7C;
} Node;

extern Node *D_800E3DE8;

void func_8009A028(Node *arg0) {
    Node *prev;
    Node *next;

    if (D_800E3DE8 == (Node *)((s8 *)arg0 - 0x20)) {
        D_800E3DE8 = arg0->next;
    }

    prev = arg0->prev;
    next = arg0->next;
    if ((prev != NULL) && (next != NULL)) {
        prev->unk7C = next;
        next->unk78 = prev;
        arg0->next = NULL;
        arg0->prev = NULL;
    }
}
