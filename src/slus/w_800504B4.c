#include "common.h"

/* Decays each of a0->arr[1..6]'s sub-object counter field (offset 2) by 0x100 while positive, else clamps it to 0; if a0->arr[6]'s counter has reached exactly 0, installs func_80050494 as a0's vtable-like function pointer (offset 0); then tail-calls func_80050308(a0). */
typedef union S_800504B4_Val {
    s16 s;
    u16 u;
} S_800504B4_Val;

typedef struct S_800504B4_Sub {
    s8 pad0[2];
    S_800504B4_Val val;
} S_800504B4_Sub;

typedef struct S_800504B4_Elem {
    s8 pad0[8];
    S_800504B4_Sub *sub;
} S_800504B4_Elem;

typedef struct S_800504B4 {
    void (*func)(void *);
    s8 pad0[0x64];
    S_800504B4_Elem **arr;
} S_800504B4;

extern void func_80050494(void *a0);
extern void func_80050308(void *a0);

void func_800504B4(S_800504B4 *a0)
{
    s32 i;
    for (i = 1; i < 7; i++) {
        S_800504B4_Elem *e = a0->arr[i];
        S_800504B4_Sub *s = e->sub;
        if (s->val.s > 0) {
            s->val.u = s->val.u - 0x100;
        } else {
            s->val.s = 0;
        }
    }
    if (a0->arr[6]->sub->val.s == 0) {
        a0->func = func_80050494;
    }
    func_80050308(a0);
}
