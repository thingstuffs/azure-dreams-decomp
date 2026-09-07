#include "common.h"

/* Singly-linked list node headed by D_80081498 (shared shape with
   func_80040418/func_800401FC/func_8004B4A8): next ptr @0x0, a 32-bit
   id/value field @0x10, and a 16-bit flags field @0x1E. */
typedef struct S_80081498 {
    struct S_80081498 *next; /* 0x00 */
    u8 pad4[0x10 - 0x4];
    s32 field_10;            /* 0x10 */
    u8 pad14[0x1E - 0x14];
    u16 field_1E;             /* 0x1E */
} S_80081498;

extern struct {
    S_80081498 *head;
    int pad[2];
} D_80081498;

extern int D_800814A0;

/* Walks the global singly-linked list headed by D_80081498 looking for
   every node whose field_10 equals a0; for each match, sets bit 0x8000 in
   that node's field_1E AND in the global flags word D_800814A0 (no early
   exit - the whole list is always walked). */
void func_800403BC(s32 a0)
{
    S_80081498 *node = D_80081498.head;

    while (node != 0) {
        if (node->field_10 == a0) {
            node->field_1E |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        node = node->next;
    }
}
