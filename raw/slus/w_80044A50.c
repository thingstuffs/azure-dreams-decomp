#include "common.h"

/* Unlink a0 from its current doubly-linked list: fix up a0->prev's forward link
 * (either the D_800833E0[] array slot if a0->prev points into that head-pointer
 * array, or the sibling node's `next` field), and a0->next's `prev` link, then
 * clear a0's own next/prev. */
typedef struct S_800833E0 {
    u8 pad00[0x14];
    struct S_800833E0 *prev; /* 0x14 */
    struct S_800833E0 *next; /* 0x18 */
    u16 type;                /* 0x1C */
} S_800833E0;

extern S_800833E0 *D_800833E0[0x20];

void func_80044A50(S_800833E0 *a0) {
    S_800833E0 *v1;
    S_800833E0 *a1;

    v1 = a0->prev;
    if (v1 != 0) {
        a1 = a0->next;
        if (a1 != 0) {
            a1->prev = v1;
        }
        if (v1 >= (S_800833E0 *)D_800833E0 && v1 < (S_800833E0 *)((u8 *)D_800833E0 + 0x80)) {
            *(S_800833E0 **)v1 = a1;
        } else {
            v1->next = a1;
        }
        a0->next = 0;
        a0->prev = 0;
    }
}
