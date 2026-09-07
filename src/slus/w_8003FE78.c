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

inline s32 inline_fn(s32 arg0)
{
    return arg0;
}

void *func_8003FE78(s32 a0, S_8003FE78 *a1, s16 a2)
{
    s32 flags = a0 | 0x80;
    S_8003FE78 *old_head;
    s32 *p;
    S_8003FE78 *new_var;

    a0 = (s32)a1;
    new_var = a1;
    func_8003DB4C((int *)a0, a2);
    old_head = D_80081490.active_head;
    D_80081498.head = new_var;
    new_var->prev = 0;
    new_var->next = old_head;
    if (old_head != 0) {
        old_head->prev = new_var;
    }
    new_var->flags = inline_fn(flags) | 0x4000;
    p = ((s32 *)new_var) + a2;
    if (flags & 6) {
        p -= 0x24 / 4;
        new_var->field_C = p;
    } else if (flags & 0x41) {
        p -= 0x18 / 4;
        new_var->field_C = p;
    }
    if (0x57 & flags) {
        p -= 0x18 / 4;
        new_var->field_8 = p;
    }
    return new_var;
}
