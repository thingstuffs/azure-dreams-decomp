#include "common.h"

extern void func_80064840();
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800654B0();
extern void func_80065820();
extern void func_8006658C();
extern void func_800666F4();

extern u8 D_8006CD30[];
extern u8 D_80083160[];
typedef struct { u8 b0, b1, b2, b3; } Ent4;
typedef struct { u8 b0, b1; u16 h2, h4; u8 *p8; } Ent12;
extern Ent4 D_800E3548[];
extern Ent12 D_800E36C8[];

#define U8(p, o)  (*(u8  *)((u8 *)(p) + (o)))
#define S8(p, o)  (*(s8  *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

typedef struct {
    s32 vx, vy, vz, pad;
} Vec4;

s32 func_800A7CC4(s32 arg0, s32 arg1, void *arg2) {
    s32 i;
    u8 *sp;
    u8 *gp;
    u8 *ctx;
    u8 *ent;
    u8 *prim;
    u8 *pc;
    u8 *w;
    register u8 *q ASM_REG("$18");   /* MATCH pin: retail immediate-load split depends on it */
    s32 n0, n1, n2, n5;
    u8 n3, n4;
    s32 xa, xb, ya, yb;
    register s32 xa2 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    s32 xb2;
    s32 ya2;
    s32 yb2;
    s32 bx, by, yc, sb, sb2;
    u8 ub, ub2;
    s32 c0, c1, c2, c3;
    s32 lastx;
    struct { u16 a, b, c; } sv;
    Vec4 vec;
    u8 *p1, *p2, *p3, *q4C, *q50, *q54, *q58, *q5C, *q60;
    u8 *e94;
    u8 *pp, *ff, *tbl;
    u8 *cd;
    u8 *c7;
    u8 *c4;
    u8 *dpage;
    s32 off90, off94;
    register u8 *a0v ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *a1v ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 calc104;
    s32 calc102;

    dpage = (u8 *)0x80070000;
    off90 = 0x90;
    off94 = 0x94;
    i = 0;
    c7 = (u8 *)0x1F8000D0;
    c4 = (u8 *)0x1F800050;
    p1 = (u8 *)0x1F800070;
    p2 = (u8 *)0x1F800078;
    p3 = (u8 *)0x1F800080;
    sp = (u8 *)0x1F800000;
    gp = D_80083160;
    ctx = *(u8 **)D_80083160;
    prim = *(u8 **)(ctx + 0x8D0);
    U32(sp, 0x20) = (u32)(ctx + 0xB0);
    U32(sp, 0xE4) = 0;
    U32(sp, 0xE8) = 0;
    U32(sp, 0xEC) = 0;
    U16(sp, 0x8C) = 0;
    U16(sp, 0x84) = 0;
    U16(sp, 0x7C) = 0;
    U16(sp, 0x74) = 0;
    sv.a = U16(gp, 196);
    sv.b = U16(gp, 198);
    sv.c = U16(gp, 200);

    do {
        if (((Ent4 *)((i * 4) + (s32)D_800E3548))->b1 != 0) {
            tbl = (u8 *)D_800E36C8;
            ent = tbl + i * 12;
            U16(sp, 0) = (U8(ent, 0) << 6) + 0x20;
            U16(sp, 2) = (U8(ent, 1) << 6) + 0x20;
            cd = D_8006CD30;
            n0 = U16(ent, 4);
            U16(sp, 4) = n0;
            w = *(u8 **)(ent + 8);
            U16(ent, 2) = n0;
            n1 = func_80065420(sp, sp + 0xB8, sp + off90, sp + off94);
            pp = (u8 *)0;
            ff = (u8 *)0;
            U32(sp, 0xC0) = n1;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            n5 = n1;
            ASM_KEEP_NV(n5);   /* MATCH pin: retail delay-slot fill depends on it */
            ASM_KEEP_DEP_NV(n5, n1 * 4);   /* MATCH pin: retail schedule: same instructions, different order without it */
            ASM_KEEP_MEMDEP_NV(n5, a0v, U32(cd, 0x1C));   /* MATCH pin: retail schedule: same instructions, different order without it */
            U32(cd, 0x1C) = n1 * 4;
            n5 -= 2;
            U32(sp, 0xC0) = n5;
            if ((u32)n5 < 0x1E0) {
                func_800649A0();
                a0v = sp + 0x100;
                a1v = c7;
                q4C = sp + 0x88;
                q50 = sp + 0xF0;
                q54 = sp + 0xF4;
                q58 = sp + 0xF8;
                q5C = sp + 0xFC;
                q60 = sp + 0x90;
                e94 = sp + 0x94;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                U16(sp, 0xB8) = U16(sp, 0xB8) - 0xA0;
                U16(sp, 0xBA) = U16(sp, 0xBA) - 0x78;
                q = w + 4;
                pc = prim + 7;
                U16(sp, 0x100) = U16(arg2, 0x16);
                ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                calc104 = U16(arg2, 0x1A);
                calc104 -= sv.b;
                U16(sp, 0x104) = U16(gp, 184) + calc104;
                calc102 = sv.c;
                calc102 += 0x100;
                calc102 &= 0x1FF;
                n2 = U16(arg2, 0x18);
                n2 -= 0x100;
                calc102 += n2;
                U16(sp, 0x102) = calc102;
                func_80065820(a0v, a1v);
                func_80064840(cd, c7, c4);
                func_80064D80(c4);
                func_80064CF0(c4);
                for (;;) {
                    if (!(U8(w, 0) & 0x20)) {
                        xa = U8(q, 4);
                        U32(sp, 8) = xa;
                        xb = U8(q, 6);
                        U32(sp, 0x10) = xb;
                        if (xa + xb >= 0x100) {
                            U32(sp, 0x10) = xb - 1;
                        }
                        ya = U8(q, 5);
                        U32(sp, 0xC) = ya;
                        yb = U8(q, 7);
                        U32(sp, 0x14) = yb;
                        if (ya + yb >= 0x100) {
                            U32(sp, 0x14) = yb - 1;
                        }
                        ub = *(volatile u8 *)(q - 2);
                        sb = (s8)ub;
                        S16(sp, 0x80) = sb;
                        S16(sp, 0x70) = sb;
                        bx = sb + U16(sp, 0x10);
                        S16(sp, 0x88) = bx;
                        S16(sp, 0x78) = bx;
                        ub2 = *(volatile u8 *)(q - 1);
                        sb2 = (s8)ub2;
                        S16(sp, 0x7A) = sb2;
                        S16(sp, 0x72) = sb2;
                        by = sb2 + U16(sp, 0x14);
                        S16(sp, 0x8A) = by;
                        S16(sp, 0x82) = by;
                        func_800654B0(p1, p2, p3, q4C, q50, q54, q58, q5C, q60, e94);
                        U16(pc, 1) = U16(sp, 0xF0) + U16(sp, 0xB8);
                        U16(pc, 3) = U16(sp, 0xF2) + U16(sp, 0xBA);
                        U16(pc, 9) = U16(sp, 0xF4) + U16(sp, 0xB8);
                        U16(pc, 0xB) = U16(sp, 0xF6) + U16(sp, 0xBA);
                        U16(pc, 0x11) = U16(sp, 0xF8) + U16(sp, 0xB8);
                        U16(pc, 0x13) = U16(sp, 0xFA) + U16(sp, 0xBA);
                        U16(pc, 0x19) = U16(sp, 0xFC) + U16(sp, 0xB8);
                        lastx = U16(sp, 0xFE) + U16(sp, 0xBA);
                        U16(pc, 0x1B) = lastx;
                        c0 = 0;
                        if ((u16)(U16(pc, 1) + 0x20) < 0x181) {
                            c0 = (u16)(U16(pc, 3) + 0x20) < 0x121;
                        }
                        c1 = 0;
                        if ((u16)(U16(pc, 9) + 0x20) < 0x181) {
                            c1 = (u16)(U16(pc, 0xB) + 0x20) < 0x121;
                        }
                        c2 = 0;
                        c0 = c0 | c1;
                        if ((u16)(U16(pc, 0x11) + 0x20) < 0x181) {
                            c2 = (u16)(U16(pc, 0x13) + 0x20) < 0x121;
                        }
                        c3 = 0;
                        c0 |= c2;
                        c2 = c0;
                        if ((u16)(U16(pc, 0x19) + 0x20) < 0x181) {
                            c3 = (u16)(lastx + 0x20) < 0x121;
                        }
                        if ((c2 | c3) != 0) {
                            xb2 = U32(sp, 0x10);
                            xa2 = U32(sp, 8);
                            yb2 = U32(sp, 0x14);
                            ya2 = U32(sp, 0xC);
                            xb2 = xb2 + xa2;
                            yb2 = yb2 + ya2;
                            U32(sp, 0x10) = xb2;
                            ASM_SET(yc);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                            yc = ya2;
                            ASM_KEEP_NV(yc);   /* MATCH pin: retail delay-slot fill depends on it */
                            yb2 = yb2 << 8;
                            yc = yc << 8;
                            U32(sp, 0x14) = yb2;
                            U32(sp, 0xC) = yc;
                            yc += xa2;
                            yc += U16(q, 2) << 16;
                            S32(pc, 5) = yc;
                            S32(pc, 0xD) = U32(sp, 0xC) + U32(sp, 0x10) + (S16(q, 0) << 16);
                            S16(pc, 0x15) = U32(sp, 0x14) + U32(sp, 8);
                            S16(pc, 0x1D) = U32(sp, 0x14) + U32(sp, 0x10);
                            if ((s16)U16(sp, 0x50) >= 0x1800) {
                                U8(pc, 0xD) = U8(pc, 0x1D)--;
                            }
                            if ((s16)U16(sp, 0x58) >= 0x1800) {
                                U8(pc, 0x16) = U8(pc, 0x1E)--;
                            }
                            if (S16(pc, 1) > S16(pc, 0x19)) {
                                U8(pc, 0xD) = U8(pc, 0xD) - 1;
                                U8(pc, 0x1D) = U8(pc, 0x1D) - 1;
                            }
                            if (S16(pc, 3) > S16(pc, 0x1B)) {
                                U8(pc, 0x16) = U8(pc, 0x16) - 1;
                                U8(pc, 0x1E) = U8(pc, 0x1E) - 1;
                            }
                            S32(pc, -3) = S32(arg2, 0xC);
                            func_800666F4(prim);
                            a1v = prim;
                            pc += 40;
                            ASM_KEEP(pc);   /* MATCH pin: retail immediate-load split depends on it */
                            func_8006658C(U32(sp, 0x20) + U32(sp, 0xC0) * 4, a1v);
                            prim += 40;
                            func_800649A0();
                            vec.vz = (s32)(s16)(*(volatile u16 *)(sp + 4)) - 4;
                            vec.vz = ((vec.vz - (s32)(s16)(*(volatile u16 *)(sp + 4))) << 5) + 0x1000;
                            if (vec.vz < 0) {
                                vec.vz = 0;
                            }
                            U16(sp, 0x102) = 0;
                            vec.vx = vec.vz;
                            vec.vy = vec.vz / 2;
                            U16(sp, 0x100) = -sv.a;
                            U16(sp, 0x104) = U16(gp, 184) - sv.b;
                            func_80065820(sp + 0x100, c7);
                            ASM_USE_G_NV(cd);   /* MATCH pin: retail immediate-load split depends on it */
                            func_80064840(dpage - 0x32D0, c7, c4);
                            func_80064BC0(c4, &vec);
                            func_80064D80(c4);
                            func_80064CF0(c4);
                            U16(sp, 0x70) = U16(sp, 0x70) + 6;
                            U16(sp, 0x78) = U16(sp, 0x78) + 6;
                            func_800654B0(p1, p2, p3, q4C, q50, q54, q58, q5C, q60, e94);
                            U16(pc, 1) = U16(sp, 0xF0) + U16(sp, 0xB8);
                            U16(pc, 3) = U16(sp, 0xF2) + U16(sp, 0xBA);
                            U16(pc, 9) = U16(sp, 0xF4) + U16(sp, 0xB8);
                            U16(pc, 0xB) = U16(sp, 0xF6) + U16(sp, 0xBA);
                            U16(pc, 0x11) = U16(sp, 0xF8) + U16(sp, 0xB8);
                            U16(pc, 0x13) = U16(sp, 0xFA) + U16(sp, 0xBA);
                            U16(pc, 0x19) = U16(sp, 0xFC) + U16(sp, 0xB8);
                            U16(pc, 0x1B) = U16(sp, 0xFE) + U16(sp, 0xBA);
                            S32(pc, 5) = U32(sp, 0xC) + U32(sp, 8) + 0x7FC00000;
                            S32(pc, 0xD) = U32(sp, 0xC) + U32(sp, 0x10) + (S16(q, 0) << 16);
                            S16(pc, 0x15) = U32(sp, 0x14) + U32(sp, 8);
                            S16(pc, 0x1D) = U32(sp, 0x14) + U32(sp, 0x10);
                            if (S16(pc, 1) > S16(pc, 0x19)) {
                                U8(pc, 0xD) = U8(pc, 0xD) - 1;
                                U8(pc, 0x1D) = U8(pc, 0x1D) - 1;
                            }
                            if (S16(pc, 3) > S16(pc, 0x1B)) {
                                U8(pc, 0x16) = U8(pc, 0x16) - 1;
                                U8(pc, 0x1E) = U8(pc, 0x1E) - 1;
                            }
                            S32(pc, -3) = S32(arg2, 0xC);
                            func_800666F4(prim);
                            U8(pc, 0) = U8(pc, 0) | 2;
                            pc += 40;
                            func_8006658C(U32(sp, 0x20) + U32(sp, 0xC0) * 4, prim);
                            prim += 40;
                            func_80064A40();
                        }
                    }
                    q += 12;
                    if (S8(w, 0) < 0) {
                        break;
                    }
                    w += 12;
                }
                func_80064A40();
            }
        }
        i += 1;
    } while (i < 64);
    *(u8 **)(*(u8 **)gp + 0x8D0) = prim;
    return 0;
}
