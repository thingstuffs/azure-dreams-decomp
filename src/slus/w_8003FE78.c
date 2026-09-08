#include "common.h"

typedef struct S_8003FE78 {
    struct S_8003FE78 *next;
    struct S_8003FE78 *prev;
    s32 *field_8;
    s32 *field_C;
    u8 pad[0x1E - 0x10];
    u16 flags;
} S_8003FE78;

extern struct {
    S_8003FE78 *head;
    int pad[2];
} D_80081498;

extern struct {
    int pad[2];
    S_8003FE78 *active_head;
    int force_large;
} D_80081490;

extern void func_8003DB4C(int *p, int n);

inline s32 inline_fn(s32 value)
{
    return value;
}

/* Initializes a node, links it at the active list head, and assigns optional tail storage. */
void *func_8003FE78(s32 flags_or_addr, S_8003FE78 *buffer, s16 word_count)
{
    s32 flags = flags_or_addr | 0x80;
    S_8003FE78 *old_head;
    s32 *tail;
    S_8003FE78 *node;

    flags_or_addr = (s32)buffer;
    node = buffer;
    func_8003DB4C((int *)flags_or_addr, word_count);
    old_head = D_80081490.active_head;
    D_80081498.head = node;
    node->prev = 0;
    node->next = old_head;
    if (old_head != 0) {
        old_head->prev = node;
    }
    node->flags = inline_fn(flags) | 0x4000;
    tail = ((s32 *)node) + word_count;
    if (flags & 6) {
        tail -= 0x24 / 4;
        node->field_C = tail;
    } else if (flags & 0x41) {
        tail -= 0x18 / 4;
        node->field_C = tail;
    }
    if (0x57 & flags) {
        tail -= 0x18 / 4;
        node->field_8 = tail;
    }
    return node;
}
