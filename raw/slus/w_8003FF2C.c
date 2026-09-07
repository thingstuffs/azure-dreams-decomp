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

/* Zeroes arg2 words at arg1, links arg1 onto the head of the list at *arg3,
 * writes flags derived from arg0 into arg1's 0x1E field, and computes/stores
 * one or two pointers (relative to arg1's tail, arg1 + arg2 words) into
 * fields 0xC/0x8 depending on which bits of (arg0|0x80) are set. Returns arg1. */
S_8003FF2C *func_8003FF2C(s32 arg0, S_8003FF2C *arg1, s16 arg2, S_8003FF2C **arg3)
{
    S_8003FF2C *oldHead;
    S_8003FF2C *tail;
    S_8003FF2C *node;
    s32 cond;

    arg0 = arg0 | 0x80;
    node = arg1;
    func_8003DB4C((int *)node, arg2);
    node->link0 = *arg3;
    *arg3 = node;
    oldHead = node->link0;
    node->link4 = (void *)arg3;
    if (oldHead != NULL) {
        oldHead->link4 = (void *)node;
    }
    node->flags1E = (s16)(arg0 | 0x4000);
    tail = (S_8003FF2C *)((u8 *)node + (arg2 << 2));
    if (arg0 & 6) {
        tail = (S_8003FF2C *)((u8 *)tail - 0x24);
        goto write_fieldC;
    }
    if (arg0 & 0x41) {
        tail = (S_8003FF2C *)((u8 *)tail - 0x18);
write_fieldC:
        node->linkC = tail;
        cond = arg0 & 0x57;
    } else {
        cond = arg0 & 0x57;
    }
    if (cond != 0) {
        tail = (S_8003FF2C *)((u8 *)tail - 0x18);
        node->link8 = tail;
    }
    return node;
}
