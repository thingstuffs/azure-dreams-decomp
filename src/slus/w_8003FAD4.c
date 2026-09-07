#include "common.h"

typedef struct S_801EAFE8
{
    struct S_801EAFE8 *next;
    u8 pad[0x124 - 4];
} S_801EAFE8;

extern S_801EAFE8 D_801EAFE8[0x100];

typedef struct S_80081490
{
    void *head;
    s32 pad1;
    s32 pad2;
} S_80081490;

extern S_80081490 D_80081490;

typedef struct S_80081498
{
    void *head;
    s32 pad[2];
} S_80081498;

extern S_80081498 D_80081498;

typedef struct S_80044AAC S_80044AAC;

extern S_80044AAC *D_800833E0[0x20];
extern S_80044AAC *D_80083360[0x20];
extern void func_8003DB4C(s32 *p, s32 n);

void func_8003FAD4(void)
{
    s32 i;
    u32 page;
    S_801EAFE8 *p;
    S_801EAFE8 *cur;
    S_80044AAC **e0_base;
    S_80044AAC **s60_base;
    S_80044AAC **e0;
    S_80044AAC **s60;

    page = 0x801F0000;
    ASM_KEEP_NV(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    p = (S_801EAFE8 *)(page - 20504);

    for (i = 0, cur = p; i < 0x100; i++) {
        func_8003DB4C((s32 *)cur, 0x49);
        cur = (S_801EAFE8 *)(((u8 *)cur) + 0x124);
    }

    for (i = 0xFE; i >= 0; i--) {
        p->next = (S_801EAFE8 *)(((u8 *)p) + 0x124);
        p = p->next;
    }

    i = 0x1F;
    e0_base = D_800833E0;
    e0 = e0_base + 0x1F;
    ASM_KEEP(e0_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s60_base = D_80083360;
    s60 = s60_base + 0x1F;
    ASM_KEEP(s60_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    p->next = 0;
    D_80081498.head = 0;
    D_80081490.head = D_801EAFE8;

    for (; i >= 0; i--) {
        *s60 = 0;
        *e0 = 0;
        e0--;
        s60--;
    }
}
