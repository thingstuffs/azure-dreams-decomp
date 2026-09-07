#include "common.h"

#include "common.h"

#ifdef NON_MATCHING
#define LEGACY_KEEP(var) ((void)0)
#else
#define LEGACY_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

typedef struct S_800477F4_Sub {
    u16 f0;
    s16 typeB;
    struct S_800477F4_Sub *next;
} S_800477F4_Sub;

typedef struct S_800477F4_Node {
    u8 pad0[2];
    s16 typeA;
    u8 pad4[4];
    S_800477F4_Sub step;
} S_800477F4_Node;

typedef struct S_800477F4_Actor {
    void *cur;
    u8 f4;
    u8 f5;
    u8 pad6[2];
    s32 f8;
    u8 padC[8];
    u16 flags;
} S_800477F4_Actor;

extern u8 D_80080A84[16];

void func_800477F4(S_800477F4_Actor *a0)
{
    u16 v0;
    register s32 a1 ASM_REG("$5");
    register S_800477F4_Node *v1 ASM_REG("$3");
    register S_800477F4_Sub *a2 ASM_REG("$6");

    v0 = a0->flags;
    a1 = v0 & 0xCFFF;
    if (v0 & 0x800) {
        goto END;
    }

    {
        u8 b = a0->f5 - 1;
        a0->f5 = b;
        if ((s8)b > 0) {
            goto END;
        }
    }

    v1 = (S_800477F4_Node *)a0->cur;
    a2 = &v1->step;
    if (v1->typeA == 0) {
        goto END;
    }
    LEGACY_KEEP(a2);

    {
        s16 typeB = *(s16 *)((char *)a2 + 2);
        if (typeB == 0) {
            a1 |= 0x5000;
            goto STORE;
        }
        if (typeB == 1) {
            a2 = a2->next;
            a1 |= 0x2000;
            a0->f4 = 0;
            goto SHARED;
        }
    }

    a0->f4 = a0->f4 + 1;

SHARED:
    a0->f5 = a2->f0 / D_80080A84[0];
    a1 |= 0x1000;
    a0->f8 = (s32)a2->next;

STORE:
    a0->cur = a2;

END:
    a0->flags = a1;
}
