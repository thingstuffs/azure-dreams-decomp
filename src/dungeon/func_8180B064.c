#include "common.h"

#define U8(b, o)  (*(u8  *)((u8 *)(b) + (o)))
#define S16(b, o) (*(s16 *)((u8 *)(b) + (o)))
#define U16(b, o) (*(u16 *)((u8 *)(b) + (o)))
#define S32(b, o) (*(s32 *)((u8 *)(b) + (o)))
#define PTR(b, o) (*(u8 **)((u8 *)(b) + (o)))

typedef struct {
    u16 i0;
    u16 i1;
    u16 i2;
    u16 i3;
    s32 a;
    s32 b;
    u16 tex;
    u16 u2;
    u16 u3;
    u16 flags;
} Face;

typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 pad;
} Vert;

typedef struct {
    u16 idx;
    u16 bias;
    u16 pad;
} Cell;

extern Cell D_80027120[];
extern s16 D_8002713A[];
extern s8 D_80083160[];
extern s8 D_8008333C[];

extern void func_800649A0();
extern void func_80064B90();
extern void func_80065820();
extern void func_80064BC0();
extern void func_80064CF0();
extern void func_80064D80();
extern s32 func_80065420();
extern s32 func_800656C0();
extern void func_80065034();
extern void func_8006658C();
extern void func_800453E0();
extern void func_80045CC4();
extern void func_80026F1C();
extern void func_80064A40();

s32 func_80026864(void *arg0, void *arg1, void *arg2)
{
    s16 sp30[4];
    s16 sp38[4];
    u8 *base12;
    s32 j;
    s32 i;
    s32 k;
    u8 *gd;
    Vert *base;
    u8 *g160;
    u8 *g120;
    u8 *scratch;
    u8 *arena;
    u8 *arena2;
    u8 *prim;
    Face *rec;
    u8 *tmp;
    u8 *obj;
    u8 *cur;
    u8 *ent;
    u8 *ent2;
    u8 *obj2;
    u8 *img;
    u32 p0;
    u32 p1;
    u32 p2;
    u32 p3;
    u32 q0;
    u32 q1;
    u32 q2;
    u32 q3;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 x;
    s32 y;
    s32 n;
    s32 idx2;
    s32 v;
    u32 sel;
    u32 nB;
    u32 nC;
    u32 nD;
    u32 aA;
    u32 aB;
    u32 aC;
    u32 aD;
    s32 yA;
    s32 yB;
    s32 yD;
    u32 zA;
    u32 zB;
    u32 zD;
    u32 e0;
    u32 e1;
    u32 e2;
    u32 e3;
    u32 zC;
    u32 b0;
    s32 d0;

    gd = (u8 *)&D_8008333C[0];
    base = (Vert *)PTR(gd, 8);
    base12 = PTR(gd, 12);
    func_800649A0();
    y = -0x60;
    scratch = (u8 *)0x1F800000;
    S32(scratch, 0x30) = U16(arg2, 0x1C);
    S32(scratch, 0x34) = U16(arg2, 0x1E);
    S32(scratch, 0x38) = (s32) (U16(arg2, 0x1C) + U16(arg2, 0x1E)) >> 1;
    g160 = (u8 *)&D_80083160[0];
    g120 = (u8 *)&D_80027120[0];
    S32(scratch, 0x40) = S16(arg1, 2);
    S32(scratch, 0x44) = S16(arg1, 6);
    S32(scratch, 0x48) = S16(arg1, 0xA);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80065820((u8 *)arg2 + 0x16, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064CF0(scratch + 0x50);
    func_80064D80(scratch + 0x50);
    arena = *(u8 **)g160;
    S32(scratch, 0x20) = (s32) (arena + 0xB0);
    prim = PTR(arena, 0x8D0);
    S32(scratch, 0x70) = 0;
    S16(scratch, 0x74) = 0;
    S32(scratch, 0xC4) = func_80065420(scratch + 0x70, scratch + 0xF0, scratch + 0x90, scratch + 0x94) - 0x27;
    i = 0;
    k = 0;
    do {
        x = -0x60;
        j = 0;
        do {
            sel = ((Cell *)((u8 *)&D_80027120[0] + k * 6))->idx;
            if (sel != 0) {
                rec = ((Face **) PTR(gd, 4))[sel];
                for (;;) {
                    ASM_SET(aC);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    aA = rec->i0 * 8 + (u32)base;
                    p0 = ((Vert *)aA)->x;
                    p0 = p0 + x;
                    p0 = p0 & 0xFFFF;
                    yA = ((Vert *)aA)->y;
                    zA = (y + yA) << 0x10;
                    p0 = p0 | zA;
                    S32(scratch, 0x70) = p0;
                    nC = U16((u8 *)rec, 4);
                    nD = U16((u8 *)rec, 6);
                    q0 = U16((u8 *)rec, 0);
                    nB = rec->i1;
                    aB = nB * 8 + (u32)base;
                    p1 = U16((u8 *)aB, 0);
                    aB = S16((u8 *)aB, 2);
                    nC = nC << 3;
                    nC = nC + (u32)base;
                    nD = nD << 3;
                    nD = nD + (u32)base;
                    ASM_USE2_NV(nD, nD);   /* MATCH pin: retail register colouring depends on it */
                    ASM_USE_NV(nD);   /* MATCH pin: retail register colouring depends on it */
                    q0 = q0 << 3;
                    q0 = q0 + (u32)base;
                    p1 = p1 + x;
                    p1 = p1 & 0xFFFF;
                    ASM_USE2_NV(p1, p1);   /* MATCH pin: retail register colouring depends on it */
                    ASM_USE2_NV(p1, p1);   /* MATCH pin: retail register colouring depends on it */
                    zB = (y + aB) << 0x10;
                    p1 = p1 | zB;
                    p2 = U16((u8 *)nC, 0);
                    aC = S16((u8 *)nC, 2);
                    p3 = U16((u8 *)nD, 0);
                    ASM_KEEP_NV(q0);   /* MATCH pin: keeps a statement from moving across a call/branch */
                    w0 = U16((u8 *)q0, 4);
                    b0 = ((Cell *)((u8 *)&D_80027120[0] + k * 6))->bias;
                    w0 = w0 - b0;
                    ASM_USE2_NV(w0, w0);   /* MATCH pin: load-bearing for the whole function shape */
                    ASM_USE2_NV(w0, w0);   /* MATCH pin: load-bearing for the whole function shape */
                    nD = S16((u8 *)nD, 2);
                    p2 = p2 + x;
                    p2 = p2 & 0xFFFF;
                    zC = y + aC;
                    zC = zC << 0x10;
                    p2 = p2 | zC;
                    p3 = p3 + x;
                    p3 = p3 & 0xFFFF;
                    ASM_USE_NV(zC);   /* MATCH pin: load-bearing for the whole function shape */
                    S16(scratch, 0x74) = w0;
                    q1 = U16((u8 *)rec, 2);
                    e1 = q1 * 8 + (u32)base;
                    ASM_KEEP_DEP_NV(e1, zB);   /* MATCH pin: keeps a constant in a register as retail does */
                    zD = (y + nD) << 0x10;
                    w1 = U16((u8 *)e1, 4);
                    S32(scratch, 0x78) = p1;
                    w1 = w1 - ((Cell *)((u8 *)&D_80027120[0] + k * 6))->bias;
                    S16(scratch, 0x7C) = w1;
                    q2 = U16((u8 *)rec, 4);
                    e2 = q2 * 8 + (u32)base;
                    w2 = U16((u8 *)e2, 4);
                    S32(scratch, 0x80) = p2;
                    w2 = w2 - ((Cell *)((u8 *)&D_80027120[0] + k * 6))->bias;
                    S16(scratch, 0x84) = w2;
                    q3 = U16((u8 *)rec, 6);
                    e3 = q3 * 8 + (u32)base;
                    p3 = p3 | zD;
                    S32(scratch, 0x88) = p3;
                    w3 = U16((u8 *)e3, 4);
                    w3 = w3 - ((Cell *)((u8 *)&D_80027120[0] + k * 6))->bias;
                    S16(scratch, 0x8C) = w3;
                    n = func_800656C0(scratch + 0x70, scratch + 0x78, scratch + 0x80, scratch + 0x88,
                                      prim + 8, prim + 0x10, prim + 0x18, prim + 0x20,
                                      scratch + 0x90, scratch + 0xC0, scratch + 0x94);
                    S32(scratch, 0x114) = n;
                    if (n > 0) {
                        v = S32(scratch, 0xC0) - S32(scratch, 0xC4);
                        S32(scratch, 0xC0) = v;
                        if ((u32) (v - 1) < 0x1DF) {
                            func_80065034(base12 + rec->tex * 8, g160 + 0xA8, prim + 4);
                            S32(prim, 0xC) = rec->a;
                            S32(prim, 0x14) = rec->b;
                            U16(prim, 0x1C) = rec->u2;
                            U16(prim, 0x24) = rec->u3;
                            if (U8(arg2, 0xC) != 0x80) {
                                U8(prim, 4) = (U8(prim, 4) * U8(arg2, 0xC)) >> 7;
                                U8(prim, 5) = (U8(prim, 5) * U8(arg2, 0xD)) >> 7;
                                U8(prim, 6) = (U8(prim, 6) * U8(arg2, 0xE)) >> 7;
                            }
                            U8(prim, 3) = 9;
                            func_8006658C(S32(scratch, 0x20) + S32(scratch, 0xC0) * 4, prim);
                            prim += 0x28;
                        }
                    }
                    if ((rec->flags & 0x80FF) == 0x8001) {
                        break;
                    }
                    rec += 1;
                }
            }
            ((Cell *)((u8 *)g120 + k * 6))->bias = 0;
            x += 0x40;
            j += 1;
            k += 1;
        } while (j < 3);
        y += 0x40;
        i += 1;
    } while (i < 3);

    arena2 = *(u8 **)g160;
    PTR(arena2, 0x8D0) = prim;
    sp30[0] = U16(g160, 0xC4);
    sp30[1] = U16(g160, 0xC6);
    sp30[2] = U16(g160, 0xC8);
    sp38[0] = U16(g160, 0xB4);
    sp38[1] = U16(g160, 0xB6);
    sp38[2] = U16(g160, 0xB8);
    U16(g160, 0xB4) = 0;
    U16(g160, 0xB6) = 0;
    U16(g160, 0xB8) = 0;
    U16(g160, 0xC4) = U16(arg2, 0x16);
    U16(g160, 0xC6) = U16(arg2, 0x18);
    U16(g160, 0xC8) = U16(arg2, 0x1A);

    if (PTR(arg0, 8) != 0) {
        S32(scratch, 0x13C) = 0;
        obj = PTR(arg0, 8);
        func_800453E0(obj + 0x20, S32(obj, 8), S32(obj, 0xC), (s16) U16(scratch, 0xC4));
        ent = PTR(arg0, 8);
        D_8002713A[0] = -2;
        func_80026F1C(S32(ent, 8), S32(ent, 0xC), -2, S32(scratch, 0xC4));
    }
    idx2 = 0;
    cur = arg0;
    ASM_USE_NV(base);   /* MATCH pin: retail register colouring depends on it */
    do {
        ASM_KEEP_NV(cur);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        if (PTR(cur, 0xC) != 0) {
            S32(scratch, 0x13C) = 0;
            obj2 = PTR(cur, 0xC);
            func_800453E0(obj2 + 0x20, S32(obj2, 8), S32(obj2, 0xC), (s16) U16(scratch, 0xC4));
            ent2 = PTR(cur, 0xC);
            func_80026F1C(S32(ent2, 8), S32(ent2, 0xC), 0, S32(scratch, 0xC4));
        }
        idx2 += 1;
        cur += 4;
    } while (idx2 < 2);

    img = PTR(arg0, 0x14);
    if (img != 0) {
        tmp = PTR(img, 0xC);
        if (!(U16(tmp, 0x14) & 0x80)) {
            func_80045CC4(img + 0x20, S32(img, 8), tmp, (s16) U16(scratch, 0xC4));
        }
    }
    U16(g160, 0xB4) = sp38[0];
    U16(g160, 0xB6) = sp38[1];
    U16(g160, 0xB8) = sp38[2];
    U16(g160, 0xC4) = sp30[0];
    U16(g160, 0xC6) = sp30[1];
    U16(g160, 0xC8) = sp30[2];
    func_80064A40();
    return 0;
}


