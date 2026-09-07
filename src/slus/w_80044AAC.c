#include "common.h"

/* Unlink a1 from its current list, then either insert it as the new head-of-children
 * of a0 (when a0 is non-NULL), or insert it as the new head of the global
 * type-indexed list D_800833E0[a1->type] (when a0 is NULL). */
typedef struct S_80044AAC {
    u8 pad00[0x14];
    struct S_80044AAC *prev; /* 0x14 */
    struct S_80044AAC *next; /* 0x18 */
    u16 type;                /* 0x1C */
} S_80044AAC;

extern S_80044AAC *D_800833E0[0x20];

extern void func_80044A50(S_80044AAC *node);

void func_80044AAC(S_80044AAC *a0, S_80044AAC *a1) {
    S_80044AAC *v1;

    func_80044A50(a1);

    if (a0 != 0) {
        v1 = a0->next;
        a0->next = a1;
        a1->prev = a0;
        a1->next = v1;
        if (v1 != 0) {
            v1->prev = a1;
        }
    } else {
        v1 = D_800833E0[a1->type];
        a1->next = v1;
        a1->prev = (S_80044AAC *)&D_800833E0[a1->type];
        D_800833E0[a1->type] = a1;
        v1->prev = a1;
    }
}
