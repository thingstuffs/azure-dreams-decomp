#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

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
    register u8 *dm ASM_REG("$17");
    void *root;
    void *state;
    u8 *sp;
    u8 *ent;
    register u8 *bank ASM_REG("$21");
    s32 ang;
    register s32 i ASM_REG("$20");
    register s32 zz ASM_REG("$23");
    register s32 mark;
    s32 sp28[16];
    u16 sp68;
    u16 sp70;
    u16 sp78;
    s32 sp80;
    u8 *sp84;
    s32 sp88;
    void *gv;
    register u8 *q ASM_REG("$4");
    register GlobalPage *page ASM_REG("$4");
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

    ASM_KEEP_NV(root);
    DM_U32(0x20) = (u32)((u8 *)gv + 0xB0);
    DM_S32(0xE4) = *(s16 *)((u8 *)arg1 + 2);
    state = arg2;
    DM_S32(0xE8) = *(s16 *)((u8 *)arg1 + 6);
    a10 = *(s16 *)((u8 *)arg1 + 0xA);
    ASM_USE(a10);
    sp84 = (u8 *)&sp28[0];
    ASM_KEEP_NV(sp84);
    DM_S32(0xEC) = a10;
    bank = FIELD(gv, u8 *, 0x8D0);
    FIELD(state, u16, 0x14) = (u16)(FIELD(state, u16, 0x14) | 0x8000);
    sp68 = arg3;
    func_800649A0();
    DM_U32(0x30) = FIELD(state, u16, 0x1C) * 2;
    DM_U32(0x34) = FIELD(state, u16, 0x1E) * 2;
    DM_U32(0x38) = 0x2000;
    DM_U16(0x100) = FIELD(state, u16, 0x16);
    DM_U16(0x104) = FIELD(state, u16, 0x1A);
    DM_U16(0x102) = FIELD(state, u16, 0x18);
    func_80065820(0x1F800100, 0x1F8000D0);
    func_80064AE0(&sp28[0]);
    func_80064840(&sp28[0], 0x1F8000D0, 0x1F800050);
    func_80064BC0(0x1F800050, 0x1F800030);
    func_80064D80(0x1F800050);
    func_80064CF0(0x1F800050);
    ASM_KEEP_NV(dm);
    {
        s32 init_flags;
        sp = FIELD(state, u8 *, 8);
        init_flags = FIELD(state, u16, 0x14);
        ASM_SCHED_BARRIER();
        mark = 0x7D00;
        DM_U16(0x24) = (u16)init_flags;
    }

loop1:
    i = 0;
    if (!(FIELD(sp, u8, 0) & 0x20)) {
        register u8 *rp ASM_REG("$5");
        u8 *sq;
        s32 fq;

        rp = sp84;
        ang = FIELD(root, s16, 0x3A);
        f0 = FIELD(sp, u8, 8);
        v = f0 + FIELD(sp, u8, 0xA);
        sq = FIELD(state, u8 *, 8);
        sp70 = (u16)v;
        fq = FIELD(sq, u8, 2);
        sp78 = (u16)f0;
        {
            register s32 zt ASM_REG("$2");
            zt = fq << 24;
            ASM_KEEP_NV(zt);
            zz = zt >> 24;
        }
        do {
            FIELD(rp, s16, 0x38) = (s16)mark;
            FIELD(rp, s16, 0x30) = (s16)mark;
            FIELD(rp, s16, 0x28) = (s16)mark;
            FIELD(rp, s16, 0x20) = (s16)mark;
            ASM_KEEP_NV(mark);
            i += 1;
            rp += 2;
        } while (i < 2);

loop4:
        i = 0;
        t = sp78;
        ent = bank + 4;
        sp80 = (s32)(s16)t;
loop5:
        sp = FIELD(state, u8 *, 8);
        ASM_USE_G_NV(gp);
        ASM_USE2_NV(root, root);
        ASM_USE2_NV(root, root);
        ASM_USE_G_NV(arg1);
        ASM_USE2_NV(root, root);
        ASM_USE2_NV(root, root);
        ASM_USE2_NV(root, root);
        ASM_USE2_NV(root, root);
        if (i == 0) {
            s32 b0;
            DM_U32(0x08) = sp80;
            b0 = FIELD(sp, u8, 9);
            DM_U32(0x10) = 1;
            DM_U32(0x0C) = b0;
            func_80024248();
        }
        {
            s32 b0;
            register s32 b1 ASM_REG("$3");
            DM_U32(0x08) = sp80;
            b0 = FIELD(sp, u8, 9);
            b1 = FIELD(sp, u8, 0xB);
            DM_U32(0x10) = 1;
            b1 = (u32)b1 >> 1;
            b0 = b0 + b1;
            DM_U32(0x0C) = b0;
        }
        /* --- shared tail of the two arms (retail word 146) --- */
        {
            s32 b2;
            b2 = (u32)FIELD(sp, u8, 0xB) >> 1;
            DM_U32(0x14) = b2;
        }
        ASM_CLOBBER("$4");
        {
            s32 b3;
            b3 = (func_800644B8(ang) * FIELD(root, s16, 0x38)) >> 0x10;
            DM_S16(0x84) = (s16)b3;
            DM_S16(0x74) = (s16)b3;
        }
        {
            s32 b4;
            b4 = FIELD(root, s16, 0x3C);
            ang += b4;
        }
        if (ang >= 0x1001) {
            ang -= 0x1000;
        }
        {
            s32 b5;
            b5 = (func_800644B8(ang) * FIELD(root, s16, 0x38)) >> 0x10;
            DM_S16(0x8C) = (s16)b5;
            DM_S16(0x7C) = (s16)b5;
        }
        {
            s32 b6;
            b6 = FIELD(root, s16, 0x3C);
            ang -= b6;
        }
        if (ang < 0) {
            ang += 0x1000;
        }
        ASM_KEEP_NV(mark);
        ASM_KEEP_NV(mark);
        {
        s32 tc;
        if ((FIELD(sp, u8, 0) ^ DM_U16(0x24)) & 1) {
            s32 e0, e1;
            e0 = -zz;
            e1 = DM_U16(0x10);
            DM_S16(0x80) = (s16)e0;
            DM_S16(0x70) = (s16)e0;
            ASM_USE(zz);
            tc = e0 - e1;
            ASM_TAILSLOT_PIN_TIED(tc);
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
        ASM_KEEP_NV(i);
        {
        s32 xb;
        register s32 xh ASM_REG("$3");
        s32 xr;
        xb = FIELD(sp, u8, 0);
        ASM_USE(xb);
        xh = *(volatile u16 *)(dm + 0x24);
        xr = xb;
        ASM_KEEP(xr);
        xr ^= xh;
        if (xr & 2) {
            if (i == 0) {
                s32 a, b;
                a = FIELD(sp, u8, 3);
                ASM_USE_NV(a);
                b = DM_U16(0x14);
                a = -(s32)(s8)a;
                DM_S16(0x7A) = (s16)a;
                DM_S16(0x72) = (s16)a;
                a = a - b;
                ASM_TAILSLOT_PIN_TIED(a);
                func_800243E4();
            }
            {
                s32 a, b;
                register s32 c ASM_REG("$4");
                a = FIELD(sp, u8, 3);
                ASM_USE_NV(a);
                b = DM_U16(0x14);
                a = -(s32)(s8)a;
                c = b;
                ASM_KEEP_NV(c);
                a = a - b;
                DM_S16(0x7A) = (s16)a;
                DM_S16(0x72) = (s16)a;
                a = a - c;
                ASM_TAILSLOT_PIN_TIED(a);
                func_800243E4();
            }
        }
        }
        if (i == 0) {
            s32 a, b;
            a = FIELD(sp, u8, 3);
            ASM_USE_NV(a);
            b = DM_U16(0x14);
            a = (s8)a;
            DM_S16(0x7A) = (s16)a;
            DM_S16(0x72) = (s16)a;
            a = a + b;
            ASM_TAILSLOT_PIN_TIED(a);
            func_800243E4();
        }
        {
            s32 a, b;
            register s32 c ASM_REG("$4");
            a = FIELD(sp, u8, 3);
            ASM_USE_NV(a);
            b = DM_U16(0x14);
            a = (s8)a;
            c = b;
            ASM_KEEP_NV(c);
            a = a + b;
            DM_S16(0x7A) = (s16)a;
            DM_S16(0x72) = (s16)a;
            a = a + c;
            DM_S16(0x8A) = (s16)a;
            DM_S16(0x82) = (s16)a;
        }
        ASM_SCHED_BARRIER();
        DM_S32(0xC0) = (func_80065590(dm + 0x70, dm + 0x78, dm + 0x80, dm + 0x88,
                                      bank + 8, bank + 0x10, bank + 0x18, bank + 0x20,
                                      dm + 0x90, dm + 0x94)
                        - (s32)(s16)sp68) - 6;
        ASM_SCHED_BARRIER();
        {
            register s32 vv ASM_REG("$2");
            vv = i * 2;
            q = (u8 *)(vv + (s32)sp84);
        }
        if (FIELD(q, s16, 0x20) != mark) {
            FIELD(ent, u16, 4) = FIELD(q, u16, 0x20);
            FIELD(ent, u16, 6) = FIELD(q, u16, 0x30);
            FIELD(ent, u16, 0x14) = FIELD(q, u16, 0x28);
            FIELD(ent, u16, 0x16) = FIELD(q, u16, 0x38);
        }
        FIELD(q, u16, 0x20) = FIELD(ent, u16, 0xC);
        FIELD(q, u16, 0x28) = FIELD(ent, u16, 0x1C);
        FIELD(q, u16, 0x30) = FIELD(ent, u16, 0xE);
        FIELD(q, u16, 0x38) = FIELD(ent, u16, 0x1E);
        if ((u32)DM_S32(0xC0) < 0x1E0U) {
            s32 g0, g1, k0, k1, k2, k3;
            k0 = 0;
            if ((u32)((FIELD(ent, u16, 4) + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (FIELD(ent, u16, 6) + 0x20) & 0xFFFF;
                k0 = (u32)m < 0x121U;
            }
            k1 = 0;
            if ((u32)((FIELD(ent, u16, 0xC) + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (FIELD(ent, u16, 0xE) + 0x20) & 0xFFFF;
                k1 = (u32)m < 0x121U;
            }
            k2 = 0;
            g0 = k0 | k1;
            if ((u32)((FIELD(ent, u16, 0x14) + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (FIELD(ent, u16, 0x16) + 0x20) & 0xFFFF;
                k2 = (u32)m < 0x121U;
            }
            k3 = 0;
            g1 = g0 | k2;
            if ((u32)((FIELD(ent, u16, 0x1C) + 0x20) & 0xFFFF) < 0x181U) {
                s32 m;
                m = (FIELD(ent, u16, 0x1E) + 0x20) & 0xFFFF;
                k3 = (u32)m < 0x121U;
            }
            if ((g1 | k3) != 0) {
                FIELD(ent, s8, -1) = 9;
                FIELD(state, u16, 0x14) = (u16)(FIELD(state, u16, 0x14) & 0x7FFF);
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
                    ta = FIELD(state, u16, 0x12);
                    FIELD(ent, s16, 0xA) = (s16)ta;
                    func_80024650();
                }
                t2 = FIELD(state, u16, 0x12);
                t2 = t2 + FIELD(sp, u16, 6);
                FIELD(ent, s16, 0xA) = (s16)t2;
                /* --- retail word 404 --- */
                t2 = DM_U16(0x0C);
                t2 = t2 + DM_U16(0x08);
                FIELD(ent, s16, 8) = (s16)t2;
                t2 = DM_U16(0x0C);
                t2 = t2 + DM_U16(0x10);
                FIELD(ent, s16, 0x10) = (s16)t2;
                {
                s32 tb, tj;
                tb = FIELD(state, u16, 0x10);
                if (tb != 0) {
                    s32 tc;
                    tj = FIELD(sp, u16, 4) & 0xFF9F;
                    tc = tb + tj;
                    ASM_TAILSLOT_PIN_TIED(tc);
                    func_800246A0();
                }
                tj = FIELD(sp, u16, 4);
                /* --- retail word 424 --- */
                FIELD(ent, u16, 0x12) = (u16)tj;
                }
                t2 = DM_U16(0x14);
                t2 = t2 + DM_U16(0x08);
                FIELD(ent, s16, 0x18) = (s16)t2;
                t2 = DM_U16(0x14);
                v = DM_U16(0x10);
                t = FIELD(ent, s16, 4);
                t2 = t2 + v;
                FIELD(ent, s16, 0x20) = (s16)t2;
                if ((s32)FIELD(ent, s16, 0x1C) < t) {
                    u8 a, b;
                    a = FIELD(ent, u8, 0x10);
                    b = FIELD(ent, u8, 0x20);
                    a = (u8)(a - 1);
                    b = (u8)(b - 1);
                    FIELD(ent, u8, 0x10) = a;
                    FIELD(ent, u8, 0x20) = b;
                }
                {
                s32 tq;
                tq = FIELD(ent, s16, 6);
                if ((s32)FIELD(ent, s16, 0x1E) < tq) {
                    u8 a, b;
                    a = FIELD(ent, u8, 0x19);
                    b = FIELD(ent, u8, 0x21);
                    a = (u8)(a - 1);
                    b = (u8)(b - 1);
                    FIELD(ent, u8, 0x19) = a;
                    FIELD(ent, u8, 0x21) = b;
                }
                }
                v = FIELD(sp, u8, 1);
                FIELD(state, u8, 0xF) = (u8)v;
                {
                s32 v4;
                v4 = DM_U16(0x24);
                if (v4 & 8) {
                    if (v4 & 4) {
                        s32 nv;
                        nv = v | 2;
                        FIELD(state, u8, 0xF) = (u8)nv;
                    } else {
                        s32 nw;
                        nw = v & 0xFD;
                        FIELD(state, u8, 0xF) = (u8)nw;
                    }
                }
                }
                FIELD(ent, s32, 0) = FIELD(state, s32, 0xC);
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
            v6 = FIELD(root, s16, 0x3C);
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

        fp = FIELD(sp, void *, 8);
        if (fp != 0) {
            fp(root, arg1, state, sp);
        }
    }
    {
    s32 e7;
    e7 = (s8)FIELD(sp, u8, 0);
    sp += 0xC;
    if (e7 >= 0) {
        goto loop1;
    }
    }
    func_80064A40();
    FIELD(gp[0], u8 *, 0x8D0) = bank;
}

#ifdef __mips__
__asm__(".size func_818F2800, 2200");
#endif
