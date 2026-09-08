#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* Node type used by this "list-insert + zero-init" helper: a next-link
 * at offset 0, a back-link at offset 4 (points either at the address of
 * the head-pointer variable, for the newly-inserted head node, or at the
 * previous head node itself), two payload pointers at 8/0xC computed from
 * the node's own tail (arg1 + arg2 words), and a 16-bit flags field at
 * 0x1E (shared layout convention with func_80040418's Node in code.c). */
typedef struct S_8003FF2C {
    struct S_8003FF2C *link0;   /* 0x00 */
    void *link4;                /* 0x04 */
    void *link8;                /* 0x08 */
    void *linkC;                /* 0x0C */
    u8 pad10[0x1E - 0x10];
    s16 flags1E;                /* 0x1E */
} S_8003FF2C;

extern void func_8003DB4C(int *p, int n);

/* Clears and prepends a node, setting its flags and optional tail payload pointers. */
S_8003FF2C *func_8003FF2C(s32 flags, S_8003FF2C *storage, s16 word_count, S_8003FF2C **list_head)
{
    S_8003FF2C *old_head;
    S_8003FF2C *payload_cursor;
    S_8003FF2C *node;
    s32 payload_flags;

    flags = flags | 0x80;
    node = storage;
    func_8003DB4C((int *)node, word_count);
    node->link0 = *list_head;
    *list_head = node;
    old_head = node->link0;
    node->link4 = (void *)list_head;
    if (old_head != NULL) {
        old_head->link4 = (void *)node;
    }
    node->flags1E = (s16)(flags | 0x4000);
    payload_cursor = (S_8003FF2C *)((u8 *)node + (word_count << 2));
    if (flags & 6) {
        payload_cursor = (S_8003FF2C *)((u8 *)payload_cursor - 0x24);
        goto write_link_c;
    }
    if (flags & 0x41) {
        payload_cursor = (S_8003FF2C *)((u8 *)payload_cursor - 0x18);
write_link_c:
        node->linkC = payload_cursor;
        payload_flags = flags & 0x57;
    } else {
        payload_flags = flags & 0x57;
    }
    if (payload_flags != 0) {
        payload_cursor = (S_8003FF2C *)((u8 *)payload_cursor - 0x18);
        node->link8 = payload_cursor;
    }
    return node;
}
