#include "common.h"

/* Links node a1 into the doubly-linked list anchored at a0 (a0's "next" field, offset 0x00, may be a real node or the sentinel D_80081498), inserting a1 as a0's new immediate successor. Sets flag bit 0x4000 on a1. a1's prev field is left NULL if a0 is currently the global list head, otherwise it is set to a0. */
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

void func_80040060(S_80040060 *a0, S_80040060 *a1)
{
    S_80040060 *old;

    a1->flags |= 0x4000;

    old = a0->next;
    a0->next = a1;
    if (old != 0) {
        old->prev = a1;
        a1->next = old;
    } else {
        a1->next = 0;
    }

    if (a0 == D_80081498.head) {
        a1->prev = 0;
    } else {
        a1->prev = a0;
    }
}
