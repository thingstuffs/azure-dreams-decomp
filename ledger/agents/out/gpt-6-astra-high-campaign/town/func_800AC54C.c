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

/* Returns the node matching a negative key with flag 0x400 clear, or NULL. */
void *func_800A9CAC(s32 target_key)
{
    S_80081498 *node;
    S_80081498 *next;
    s32 key;
    void *result;

    node = D_80081498.head;
    result = 0;
    if (node == 0) {
        return result;
    }
loop:
    key = node->field_10;
    next = node->next;
    if (key >= 0) {
        goto cont;
    }
    if (node->field_1E & 0x400) {
        goto cont;
    }
    if (key == target_key) {
        return node;
    }
cont:
    node = next;
    result = 0;
    if (node != 0) {
        goto loop;
    }
    return result;
}
