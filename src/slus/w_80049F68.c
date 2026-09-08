#include "common.h"

typedef struct S_8002E5D8
{
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} S_8002E5D8;

typedef struct S_8002E5E8
{
    s32 f0;
    s32 f4;
    s32 f8;
} S_8002E5E8;

typedef struct S_80049F68_Link
{
    s32 unk0;
    void *self;
    void *parent;
    struct S_80049F68_Link *next;
} S_80049F68_Link;

typedef struct S_80049F68_Elem
{
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    S_80049F68_Link link;
} S_80049F68_Elem;

typedef struct S_80049F68_Obj
{
    u8 pad00[0x20];
    S_80049F68_Elem elem[4];
    s32 unkA0;
    s32 unkA4;
    s32 unkA8;
} S_80049F68_Obj;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;
extern u8 D_80080B30;
extern u8 D_80080B2C[16];

void func_80049F68(S_80049F68_Obj *arg0_)
{
    register S_80049F68_Obj *arg0 ASM_REG("$4") = arg0_;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 i ASM_REG("$7");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register s32 off ASM_REG("$6");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register u8 *walk ASM_REG("$5");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register S_8002E5D8 *src ASM_REG("$8");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    void *parent;
    s32 new_var3;
    void *selfp;
    S_80049F68_Link *cur;
    S_80049F68_Link *next;
    u8 b;
    s32 term;

    i = 0;
    src = &D_8002E5D8;
    parent = &arg0->unkA0;
    arg0->unkA0 = D_8002E5E8.f0;
    ASM_KEEP(src);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    arg0->unkA4 = D_8002E5E8.f4;
    arg0->unkA8 = D_8002E5E8.f8;
    off = 0x20;
    walk = (u8 *)arg0;
    do {
        *((s32 *)(walk + 0x20)) = D_8002E5D8.f0;
        selfp = ((u8 *)arg0) + off;
        *((s32 *)(walk + 0x24)) = src->f4;
        off += 0x20;
        *((s32 *)(walk + 0x28)) = src->f8;
        new_var3 = src->fC;
        i += 1;
        *((void **)(walk + 0x34)) = selfp;
        *((void **)(walk + 0x38)) = parent;
        *((s32 *)(walk + 0x2C)) = new_var3;
        walk += 0x20;
    } while (i < 4);

    cur = &arg0->elem[0].link;
    term = 4;
    if (D_80080B30 != term) {
        s32 expected;
        register u8 *p ASM_REG("$5");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */

        expected = term;
        p = &D_80080B2C[4];
        do {
            b = *(p++);
            next = &arg0->elem[b].link;
            cur->next = next;
            cur = next;
        } while (*p != expected);
    }
    cur->next = 0;
}
