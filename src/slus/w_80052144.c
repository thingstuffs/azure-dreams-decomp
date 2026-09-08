#include "common.h"

typedef struct Child {
    u8 pad00[0x1E];
    u16 flags;
} Child;

typedef struct Controller {
    s16 state;
    s16 timer;
    s16 attached;
    s16 finished;
    s16 *script;
    Child *child0;
    Child *child1;
    Child *child2;
    Child *child3;
    void *group;
} Controller;

typedef struct Shared83160 {
    u8 pad00[0x10];
    s32 flags10;
} Shared83160;

typedef struct Shared82E60 {
    u8 pad00[0x16];
    u16 flags16;
} Shared82E60;

extern Shared83160 D_80083160;
extern Shared82E60 D_80082E60;
extern s32 D_800814A0;


extern void *jtbl_8002EFDC[];
extern void func_800530C4(void *);
extern s16 func_80053DA8(s32);
extern s32 func_80053EF0(s32);
extern void func_80051528(void *);
extern void func_800517AC(void *);
extern void func_800530A4(void *);
extern void func_80051CA4(void *);
extern void func_80051F38(void *);
extern void func_80041094(s32, s32, s32, s32, s32);

void func_80052144(Controller *s)
{
    s32 idx;
    void **tbl;
    register u8 *page ASM_REG("$3") = (u8 *)0x80080000;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register Shared83160 *g ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    static void *const keepalive[] = {
        &&L_case_0, &&L_case_1, &&L_case_2, &&L_case_3,
        &&L_case_4, &&L_default
    };
    (void)keepalive;

    s->timer++;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    g = (Shared83160 *)(page + 0x3160);

    if (s->state < 4 && (g->flags10 & 0x40)) {
        if (s->child0 != 0) {
            s->child0->flags |= 0x8000;
            s->child0 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->child1 != 0) {
            s->child1->flags |= 0x8000;
            s->child1 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->child2 != 0) {
            s->child2->flags |= 0x8000;
            s->child2 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->child3 != 0) {
            s->child3->flags |= 0x8000;
            s->child3 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->group != 0) {
            func_800530C4(s->group);
        }
        func_80053DA8(0xB4);
        s->timer = 0;
        s->state = 4;
    }

    idx = s->state;
    if ((u32)idx >= 5) {
        goto L_default;
    }
    {
        u8 *pgt = (u8 *)0x80030000;
        ASM_KEEP_NV(pgt);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        tbl = (void **)(pgt - 0x1024);
        ASM_KEEP_NV(tbl);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }
    goto *tbl[idx];

L_case_0:
        if (func_80053EF0(4) != 1) {
            return;
        }
        func_80051528(s->child0);
        func_800517AC(s->child1);
        func_800530A4(s->group);
        s->timer = 0;
        s->state++;
        return;

L_case_1:
        if (s->child2 != 0) {
            if (s->script[0] != s->timer) {
                return;
            }
            func_80051CA4(s->child2);
            s->script = (s16 *)((u8 *)s->script + 0x10);
            if (s->script[0] != 0) {
                return;
            }
            s->state++;
            return;
        }
        s->state++;
        return;

L_case_2:
        if (s->timer != 0x1C09) {
            return;
        }
        func_80051528(s->child0);
        func_800517AC(s->child1);
        s->state++;
        return;

L_case_3:
        if (s->timer != 0x1CCF) {
            return;
        }
        func_80051F38(s->child3);
        s->timer = 0;
        s->state++;
        return;

L_case_4:
        if (s->attached != s->finished) {
            return;
        }
#line 900 "x"
        {
            register u8 *pg2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            Shared82E60 *g2;
            s32 z;
            s32 six;
            register s32 z2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            six = 6;
            z = 0;
            ASM_KEEP_NV(six);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            z2 = z;
            ASM_KEEP_NV(z2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            pg2 = (u8 *)0x80080000;
            ASM_KEEP_NV(pg2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            g2 = (Shared82E60 *)(pg2 + 0x2E60);
            ASM_KEEP_NV(g2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            g2->flags16 |= 0x8000;
            func_80041094(six, z, z2, z, g2->flags16 ^ 1);
        }
#line 1000 "x"
        ((u16 *)s)[-1] |= 0x8000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        D_800814A0 |= 0x8000;
        return;

L_default:
        if (s->child0 != 0) {
            s->child0->flags |= 0x8000;
            s->child0 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->child1 != 0) {
            s->child1->flags |= 0x8000;
            s->child1 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->child2 != 0) {
            s->child2->flags |= 0x8000;
            s->child2 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->child3 != 0) {
            s->child3->flags |= 0x8000;
            s->child3 = 0;
            D_800814A0 |= 0x8000;
            s->finished++;
        }
        if (s->group != 0) {
            func_800530C4(s->group);
        }
        if (s->attached != s->finished) {
            return;
        }
        func_80053DA8(0xB4);
#line 900 "x"
        {
            register u8 *pg2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            Shared82E60 *g2;
            s32 z;
            s32 six;
            register s32 z2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            six = 6;
            z = 0; ASM_USE_NV(z); /* cross-jump boundary; MUST stay on this line -- see NOTES.md */
            ASM_KEEP_NV(six);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            z2 = z;
            ASM_KEEP_NV(z2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            pg2 = (u8 *)0x80080000;
            ASM_KEEP_NV(pg2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            g2 = (Shared82E60 *)(pg2 + 0x2E60);
            ASM_KEEP_NV(g2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            g2->flags16 |= 0x8000;
            func_80041094(six, z, z2, z, g2->flags16 ^ 1);
        }
#line 1000 "x"
        ((u16 *)s)[-1] |= 0x8000;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        D_800814A0 |= 0x8000;
        return;
}
