#include "common.h"

/* Singly-linked list node headed by D_80081498 (shared shape with
   func_80040418/func_800401FC/func_8004B4A8/func_800403BC): next ptr @0x0,
   a 32-bit id/value field @0x10, and a 16-bit flags field @0x1E. */
typedef struct S_80081498 {
    struct S_80081498 *next; /* 0x00 */
    u8 pad4[0x10 - 0x4];
    s32 field_10;             /* 0x10 */
    u8 pad14[0x1E - 0x14];
    u16 field_1E;             /* 0x1E */
} S_80081498;

extern struct {
    S_80081498 *head;
    int pad[2];
} D_80081498;

/* Walks the global singly-linked list headed by D_80081498 looking for a
   node whose field_10 is negative, does not have flag bit 0x400 set, and
   whose field_10 equals a0. Returns that node, or NULL if none matches. */
void *func_800A9CAC(s32 a0)
{
    S_80081498 *v1;
    S_80081498 *next;
    s32 key;
    void *v0;

    v1 = D_80081498.head;
    v0 = 0;
    if (v1 == 0) {
        return v0;
    }
loop:
    key = v1->field_10;
    next = v1->next;
    if (key >= 0) {
        goto cont;
    }
    if (v1->field_1E & 0x400) {
        goto cont;
    }
    if (key == a0) {
        return v1;
    }
cont:
    v1 = next;
    v0 = 0;
    if (v1 != 0) {
        goto loop;
    }
    return v0;
}
