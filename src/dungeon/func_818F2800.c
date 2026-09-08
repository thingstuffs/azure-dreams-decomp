#include "common.h"

typedef struct S_BODY_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_BODY_0;   /* gv in BODY */

typedef struct S_BODY_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_BODY_1;   /* state in BODY */

typedef struct S_BODY_2 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
    u16 unk_04;
    u16 unk_06;
    union { struct { u8 v; } at00; struct { void * v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_08;   /* overlapping accesses */
} S_BODY_2;   /* sp in BODY */

typedef struct S_BODY_3 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
} S_BODY_3;   /* root in BODY */

typedef struct S_BODY_4 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_BODY_4;   /* sq in BODY */

typedef struct S_BODY_5 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x6];
    s16 unk_28;
    u8 pad_2A[0x6];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_BODY_5;   /* rp in BODY */

typedef struct S_BODY_6 {
    u8 pad_00[0x20];
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    u8 pad_22[0x6];
    u16 unk_28;
    u8 pad_2A[0x6];
    u16 unk_30;
    u8 pad_32[0x6];
    u16 unk_38;
} S_BODY_6;   /* q in BODY */

typedef struct S_BODY_7_pre {
    s8 unk_00;
} S_BODY_7_pre;   /* the 0x1 bytes before ent in BODY, addressed as ent[-1] */

typedef struct S_BODY_7 {
    s32 unk_00;
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
    union { struct { s16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_20;   /* overlapping accesses */
} S_BODY_7;   /* ent in BODY */

typedef struct S_BODY_8 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_BODY_8;   /* gp[0] in BODY */



#define DM_U8(o)  (*(u8  *)(dm + (o)))
#define DM_S8(o)  (*(s8  *)(dm + (o)))
#define DM_U16(o) (*(u16 *)(dm + (o)))
#define DM_S16(o) (*(s16 *)(dm + (o)))
#define DM_U32(o) (*(u32 *)(dm + (o)))
#define DM_S32(o) (*(s32 *)(dm + (o)))

extern void func_80024248(void) __attribute__((noreturn));
extern void func_8002431C(void) __attribute__((noreturn));
extern void func_800243E4(void) __attribute__((noreturn));
extern void func_80024650(void) __attribute__((noreturn));
extern void func_800246A0(void) __attribute__((noreturn));
extern void func_80024838(void) __attribute__((noreturn));

extern s32 func_800644B8(s32);
extern void func_80064840();
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0();
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065590();
extern void func_80065820();

typedef struct {
    u8 pad[0x3160];
    u8 *table[3];
} GlobalPage;

extern GlobalPage D_80080000;
__asm__(".set D_80080000, 0x80080000");

extern void *D_80083160[];

#ifdef __mips__
extern void func_80024FA4(void);
extern void func_80025090(void);
extern void func_80025150(void);
extern void func_80025418(void);
extern void func_80025798(void);
extern void func_800257CC(void);
extern void func_80025874(void);
extern void func_800258B0(void);
extern void func_80025948(void);
extern void func_800258E4(void);

/* The carved retail range starts with ten words of local table data followed
 * by nine callback addresses, immediately ahead of the executable body. */
static const u32 func_818F2800_prefix[]
    __asm__("func_818F2800")
    __attribute__((section(".text.func_818F2800"), aligned(4))) = {
    (u32)func_80024FA4,
    0x00000020, 0x00200020, 0x00200000, 0x0020FFE0,
    0x0000FFE0, 0xFFE0FFE0, 0xFFE00000, 0xFFE00020, 0x00000000,
};

static void (*const func_818F2800_table[])(void)
    __attribute__((section(".text.func_818F2800"), aligned(4))) = {
    func_80025090, func_80025150, func_80025418,
    func_80025798, func_800257CC, func_80025874,
    func_800258B0, func_80025948, func_800258E4,
};
#endif

#ifdef __mips__
#define BODY func_818F284C
#define BODY_SECTION __attribute__((section(".text.func_818F2800")))
#else
#define BODY func_818F2800
#define BODY_SECTION
#endif

void BODY(void *arg0, void *arg1, void *arg2, u16 arg3) BODY_SECTION;
void BODY(void *arg0, void *arg1, void *arg2, u16 arg3)
{
    register u8 *dm ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_BODY_3 *root;
    S_BODY_1 *state;
    u8 *sp;
    u8 *ent;
    register u8 *bank ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 ang;
    register s32 i ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 zz ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 mark;
    s32 sp28[16];
    u16 sp68;
    u16 sp70;
    u16 sp78;
    s32 sp80;
    u8 *sp84;
    s32 sp88;
    void *gv;
    register u8 *q ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register GlobalPage *page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 t;
    s32 t2;
    s32 d;
    s32 d2;
    s32 v;
    s32 w;
    s32 f0, f1, f2, f3;
    void **gp;
    s32 a10;

    root = arg0;
    gp = D_80083160;
    page = &D_80080000;
    gv = page->table[0];
    dm = (u8 *)0x1F800000;

    ASM_KEEP_NV(root);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    DM_U32(0x20) = (u32)((u8 *)gv + 0xB0);
    DM_S32(0xE4) = *(s16 *)((u8 *)arg1 + 2);
    state = arg2;
    DM_S32(0xE8) = *(s16 *)((u8 *)arg1 + 6);
    a10 = *(s16 *)((u8 *)arg1 + 0xA);
    ASM_USE(a10);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    sp84 = (u8 *)&sp28[0];
    ASM_KEEP_NV(sp84);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    DM_S32(0xEC) = a10;
    bank = ((S_BODY_0 *)gv)->unk_8D0;
    state->unk_14 = (u16)(state->unk_14 | 0x8000);
    sp68 = arg3;
    func_800649A0();
    DM_U32(0x30) = state->unk_1C * 2;
    DM_U32(0x34) = state->unk_1E * 2;
    DM_U32(0x38) = 0x2000;
    DM_U16(0x100) = state->unk_16;
    DM_U16(0x104) = state->unk_1A;
    DM_U16(0x102) = state->unk_18;
    func_80065820(0x1F800100, 0x1F8000D0);
    func_80064AE0(&sp28[0]);
    func_80064840(&sp28[0], 0x1F8000D0, 0x1F800050);
    func_80064BC0(0x1F800050, 0x1F800030);
    func_80064D80(0x1F800050);
    func_80064CF0(0x1F800050);
    ASM_KEEP_NV(dm);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        s32 init_flags;
        sp = state->unk_08;
        init_flags = state->unk_14;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        mark = 0x7D00;
        DM_U16(0x24) = (u16)init_flags;
    }

loop1:
    i = 0;
    if (!(((S_BODY_2 *)sp)->unk_00 & 0x20)) {
        register u8 *rp ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        u8 *sq;
        s32 fq;

        rp = sp84;
        ang = root->unk_3A;
        f0 = ((S_BODY_2 *)sp)->unk_08.at00.v;
        v = f0 + ((S_BODY_2 *)sp)->unk_08.at02.v;
        sq = state->unk_08;
        sp70 = (u16)v;
        fq = ((S_BODY_4 *)sq)->unk_02;
        sp78 = (u16)f0;
        {
            register s32 zt ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            zt = fq << 24;
            ASM_KEEP_NV(zt);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            zz = zt >> 24;
        }
        do {
            ((S_BODY_5 *)rp)->unk_38 = (s16)mark;
            ((S_BODY_5 *)rp)->unk_30 = (s16)mark;
            ((S_BODY_5 *)rp)->unk_28 = (s16)mark;
            ((S_BODY_5 *)rp)->unk_20 = (s16)mark;
            ASM_KEEP_NV(mark);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            i += 1;
            rp += 2;
        } while (i < 2);

loop4:
        i = 0;
        t = sp78;
        ent = bank + 4;
        sp80 = (s32)(s16)t;
loop5:
        sp = state->unk_08;
        ASM_USE_G_NV(gp);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(root, root);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(root, root);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE_G_NV(arg1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(root, root);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(root, root);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(root, root);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_USE2_NV(root, root);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        if (i == 0) {
            s32 b0;
            DM_U32(0x08) = sp80;
            b0 = ((S_BODY_2 *)sp)->unk_08.at01.v;
            DM_U32(0x10) = 1;
            DM_U32(0x0C) = b0;
            func_80024248();
        }
        {
            s32 b0;
            register s32 b1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            DM_U32(0x08) = sp80;
            b0 = ((S_BODY_2 *)sp)->unk_08.at01.v;
            b1 = ((S_BODY_2 *)sp)->unk_08.at03.v;
            DM_U32(0x10) = 1;
            b1 = (u32)b1 >> 1;
            b0 = b0 + b1;
            DM_U32(0x0C) = b0;
        }
        /* --- shared tail of the two arms (retail word 146) --- */
        {
            s32 b2;
            b2 = (u32)((S_BODY_2 *)sp)->unk_08.at03.v >> 1;
            DM_U32(0x14) = b2;
        }
        ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        {
            s32 b3;
            b3 = (func_800644B8(ang) * root->unk_38) >> 0x10;
            DM_S16(0x84) = (s16)b3;
            DM_S16(0x74) = (s16)b3;
        }
        {
            s32 b4;
            b4 = root->unk_3C;
            ang += b4;
        }
        if (ang >= 0x1001) {
            ang -= 0x1000;
        }
        {
            s32 b5;
            b5 = (func_800644B8(ang) * root->unk_38) >> 0x10;
            DM_S16(0x8C) = (s16)b5;
            DM_S16(0x7C) = (s16)b5;
        }
        {
            s32 b6;
            b6 = root->unk_3C;
            ang -= b6;
        }
        if (ang < 0) {
            ang += 0x1000;
        }
        ASM_KEEP_NV(mark);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(mark);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        {
        s32 tc;
        if ((((S_BODY_2 *)sp)->unk_00 ^ DM_U16(0x24)) & 1) {
            s32 e0, e1;
            e0 = -zz;
            e1 = DM_U16(0x10);
            DM_S16(0x80) = (s16)e0;
            DM_S16(0x70) = (s16)e0;
            ASM_USE(zz);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            tc = e0 - e1;
            ASM_TAILSLOT_PIN_TIED(tc);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_8002431C();
        }
        {
            s32 e2;
            e2 = DM_U16(0x10);
            DM_S16(0x80) = (s16)zz;
            DM_S16(0x70) = (s16)zz;
            tc = zz + e2;
        }
        DM_S16(0x88) = (s16)tc;
        DM_S16(0x78) = (s16)tc;
        }
        ASM_KEEP_NV(i);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
        s32 xb;
        register s32 xh ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 xr;
        xb = ((S_BODY_2 *)sp)->unk_00;
        ASM_USE(xb);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        xh = *(volatile u16 *)(dm + 0x24);
        xr = xb;
        ASM_KEEP(xr);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        xr ^= xh;
        if (xr & 2) {
            if (i == 0) {
                s32 a, b;
                a = ((S_BODY_2 *)sp)->unk_03;
                ASM_USE_NV(a);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                b = DM_U16(0x14);
                a = -(s32)(s8)a;
                DM_S16(0x7A) = (s16)a;
                DM_S16(0x72) = (s16)a;
                a = a - b;
                ASM_TAILSLOT_PIN_TIED(a);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_800243E4();
            }
            {
                s32 a, b;
                register s32 c ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                a = ((S_BODY_2 *)sp)->unk_03;
                ASM_USE_NV(a);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                b = DM_U16(0x14);
                a = -(s32)(s8)a;
                c = b;
                ASM_KEEP_NV(c);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                a = a - b;
                DM_S16(0x7A) = (s16)a;
                DM_S16(0x72) = (s16)a;
                a = a - c;
                ASM_TAILSLOT_PIN_TIED(a);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_800243E4();
            }
        }
        }
        if (i == 0) {
            s32 a, b;
            a = ((S_BODY_2 *)sp)->unk_03;
            ASM_USE_NV(a);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            b = DM_U16(0x14);
            a = (s8)a;
            DM_S16(0x7A) = (s16)a;
            DM_S16(0x72) = (s16)a;
            a = a + b;
            ASM_TAILSLOT_PIN_TIED(a);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            func_800243E4();
        }
        {
            s32 a, b;
            register s32 c ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            a = ((S_BODY_2 *)sp)->unk_03;
            ASM_USE_NV(a);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            b = DM_U16(0x14);
            a = (s8)a;
            c = b;
            ASM_KEEP_NV(c);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            a = a + b;
            DM_S16(0x7A) = (s16)a;
            DM_S16(0x72) = (s16)a;
            a = a + c;
            DM_S16(0x8A) = (s16)a;
            DM_S16(0x82) = (s16)a;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        DM_S32(0xC0) = (func_80065590(dm + 0x70, dm + 0x78, dm + 0x80, dm + 0x88,
                                      bank + 8, bank + 0x10, bank + 0x18, bank + 0x20,
                                      dm + 0x90, dm + 0x94)
                        - (s32)(s16)sp68) - 6;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 vv ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            vv = i * 2;
            q = (u8 *)(vv + (s32)sp84);
        }
        if (((S_BODY_6 *)q)->unk_20.s != mark) {
            ((S_BODY_7 *)ent)->unk_04.u = ((S_BODY_6 *)q)->unk_20.u;
            ((S_BODY_7 *)ent)->unk_06.u = ((S_BODY_6 *)q)->unk_30;
            ((S_BODY_7 *)ent)->unk_14 = ((S_BODY_6 *)q)->unk_28;
            ((S_BODY_7 *)ent)->unk_16 = ((S_BODY_6 *)q)->unk_38;
        }
        ((S_BODY_6 *)q)->unk_20.u = ((S_BODY_7 *)ent)->unk_0C;
        ((S_BODY_6 *)q)->unk_28 = ((S_BODY_7 *)ent)->unk_1C.u;
        ((S_BODY_6 *)q)->unk_30 = ((S_BODY_7 *)ent)->unk_0E;
        ((S_BODY_6 *)q)->unk_38 = ((S_BODY_7 *)ent)->unk_1E.u;
        if ((u32)DM_S32(0xC0) < 0x1E0U) {
            s32 g0, g1, k0, k1, k2, k3;
            k0 = 0;
            if ((u32)((((S_BODY_7 *)ent)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (((S_BODY_7 *)ent)->unk_06.u + 0x20) & 0xFFFF;
                k0 = (u32)m < 0x121U;
            }
            k1 = 0;
            if ((u32)((((S_BODY_7 *)ent)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (((S_BODY_7 *)ent)->unk_0E + 0x20) & 0xFFFF;
                k1 = (u32)m < 0x121U;
            }
            k2 = 0;
            g0 = k0 | k1;
            if ((u32)((((S_BODY_7 *)ent)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (((S_BODY_7 *)ent)->unk_16 + 0x20) & 0xFFFF;
                k2 = (u32)m < 0x121U;
            }
            k3 = 0;
            g1 = g0 | k2;
            if ((u32)((((S_BODY_7 *)ent)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (((S_BODY_7 *)ent)->unk_1E.u + 0x20) & 0xFFFF;
                k3 = (u32)m < 0x121U;
            }
            if ((g1 | k3) != 0) {
                ((S_BODY_7_pre *)ent)[-1].unk_00 = 9;
                state->unk_14 = (u16)(state->unk_14 & 0x7FFF);
                {
                    s32 vv, ww;
                    vv = DM_U32(0x10) + DM_U32(0x08);
                    DM_U32(0x10) = vv;
                    if (vv & 0x100) {
                        DM_U32(0x10) = vv - 1;
                    }
                    ww = DM_U32(0x14) + DM_U32(0x0C);
                    DM_U32(0x14) = ww;
                    if (ww & 0x100) {
                        DM_U32(0x14) = ww - 1;
                    }
                }
                DM_U32(0x0C) <<= 8;
                DM_U32(0x14) <<= 8;
                if (DM_U16(0x24) & 0x100) {
                    s32 ta;
                    ta = state->unk_12;
                    ((S_BODY_7 *)ent)->unk_0A = (s16)ta;
                    func_80024650();
                }
                t2 = state->unk_12;
                t2 = t2 + ((S_BODY_2 *)sp)->unk_06;
                ((S_BODY_7 *)ent)->unk_0A = (s16)t2;
                /* --- retail word 404 --- */
                t2 = DM_U16(0x0C);
                t2 = t2 + DM_U16(0x08);
                ((S_BODY_7 *)ent)->unk_08 = (s16)t2;
                t2 = DM_U16(0x0C);
                t2 = t2 + DM_U16(0x10);
                ((S_BODY_7 *)ent)->unk_10.s16 = (s16)t2;
                {
                s32 tb, tj;
                tb = state->unk_10;
                if (tb != 0) {
                    s32 tc;
                    tj = ((S_BODY_2 *)sp)->unk_04 & 0xFF9F;
                    tc = tb + tj;
                    ASM_TAILSLOT_PIN_TIED(tc);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_800246A0();
                }
                tj = ((S_BODY_2 *)sp)->unk_04;
                /* --- retail word 424 --- */
                ((S_BODY_7 *)ent)->unk_12 = (u16)tj;
                }
                t2 = DM_U16(0x14);
                t2 = t2 + DM_U16(0x08);
                ((S_BODY_7 *)ent)->unk_18.at00.v = (s16)t2;
                t2 = DM_U16(0x14);
                v = DM_U16(0x10);
                t = ((S_BODY_7 *)ent)->unk_04.s;
                t2 = t2 + v;
                ((S_BODY_7 *)ent)->unk_20.at00.v = (s16)t2;
                if ((s32)((S_BODY_7 *)ent)->unk_1C.s < t) {
                    u8 a, b;
                    a = ((S_BODY_7 *)ent)->unk_10.u8;
                    b = ((S_BODY_7 *)ent)->unk_20.at00u.v;
                    a = (u8)(a - 1);
                    b = (u8)(b - 1);
                    ((S_BODY_7 *)ent)->unk_10.u8 = a;
                    ((S_BODY_7 *)ent)->unk_20.at00u.v = b;
                }
                {
                s32 tq;
                tq = ((S_BODY_7 *)ent)->unk_06.s;
                if ((s32)((S_BODY_7 *)ent)->unk_1E.s < tq) {
                    u8 a, b;
                    a = ((S_BODY_7 *)ent)->unk_18.at01.v;
                    b = ((S_BODY_7 *)ent)->unk_20.at01.v;
                    a = (u8)(a - 1);
                    b = (u8)(b - 1);
                    ((S_BODY_7 *)ent)->unk_18.at01.v = a;
                    ((S_BODY_7 *)ent)->unk_20.at01.v = b;
                }
                }
                v = ((S_BODY_2 *)sp)->unk_01;
                state->unk_0C.at03.v = (u8)v;
                {
                s32 v4;
                v4 = DM_U16(0x24);
                if (v4 & 8) {
                    if (v4 & 4) {
                        s32 nv;
                        nv = v | 2;
                        state->unk_0C.at03.v = (u8)nv;
                    } else {
                        s32 nw;
                        nw = v & 0xFD;
                        state->unk_0C.at03.v = (u8)nw;
                    }
                }
                }
                ((S_BODY_7 *)ent)->unk_00 = state->unk_0C.at00.v;
                ent += 0x28;
                *(u32 *)bank = (*(u32 *)bank & 0xFF000000)
                             | (((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] & 0xFFFFFF);
                ((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] =
                    (((u32 *)((u8 *)DM_U32(0x20)))[DM_S32(0xC0)] & 0xFF000000)
                    | ((s32)bank & 0xFFFFFF);
                bank += 0x28;
            }
        }
        i += 1;
        if (i < 2) {
            goto loop5;
        }
        {
            s32 v6;
            v6 = root->unk_3C;
            ang += v6;
        }
        if (ang >= 0x1001) {
            ang -= 0x1000;
        }
        sp78 = (u16)(sp78 + 1);
        {
            s32 tt;
            tt = (s32)(s16)sp78;
            zz += 1;
            if (tt != (s32)sp70) {
                goto loop4;
            }
        }
        func_80024838();
    }
    {
        void (*fp)(void *, void *, void *, void *);

        fp = ((S_BODY_2 *)sp)->unk_08.at00u.v;
        if (fp != 0) {
            fp(root, arg1, state, sp);
        }
    }
    {
    s32 e7;
    e7 = (s8)((S_BODY_2 *)sp)->unk_00;
    sp += 0xC;
    if (e7 >= 0) {
        goto loop1;
    }
    }
    func_80064A40();
    ((S_BODY_8 *)(gp[0]))->unk_8D0 = bank;
}

#ifdef __mips__
__asm__(".size func_818F2800, 2200");
#endif
