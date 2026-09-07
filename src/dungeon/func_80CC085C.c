#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017405C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8017405C_0;   /* d in func_8017405C */

typedef struct S_8017405C_1 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_8017405C_1;   /* c in func_8017405C */

typedef struct S_8017405C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_2_pre;   /* the 0x14 bytes before e in func_8017405C, addressed as e[-1] */

typedef struct S_8017405C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8017405C_2;   /* e in func_8017405C */

typedef struct S_8017405C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_3;   /* e2 in func_8017405C */

typedef struct S_8017405C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8017405C_4;   /* root in func_8017405C */



typedef struct S_8017405C_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_7_pre;   /* the 0x14 bytes before pa in func_8017405C, addressed as pa[-1] */

typedef struct S_8017405C_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017405C_8_pre;   /* the 0x14 bytes before pb in func_8017405C, addressed as pb[-1] */

typedef struct S_8017405C_9 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_9;   /* p2 in func_8017405C */

typedef struct S_8017405C_10 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017405C_10;   /* p1 in func_8017405C */

typedef struct S_8017405C_11 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8017405C_11;   /* (u8 *)d + (((S_8017405C_0 *)d)->unk_71.u & 0x7F) in func_8017405C */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonModeRecord;

extern void func_800A9A0C(void *);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern void *func_800A02AC(void *, s32, s32);
extern u16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A6D30(void);
extern void *func_800A04F0(void *, s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern void func_800A0E6C(void *, s32, void *, void *);
extern s16 func_800A0134(void *, void *);
extern s16 func_8009A540(s32, s32, s32, s32);
extern s32 func_800A07D0(s32, s32, s32, s32);
extern s16 func_8009FD40(void *, void *);
extern s16 func_8009FD7C(s32, s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009A21C(s32, s32, s32);
extern s16 func_8009A180(void *, void *);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 func_80174BCC(void *, s32, void *, void *);

extern u16 D_80083462;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u16 D_80082EA4;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_8006CD00[];
extern DungeonModeRecord D_800E2970[];
extern u16 D_80083460[];

void func_8017405C(void *a, s32 b, S_8017405C_1 *c, void *d)
{
    s16 idx;
    s16 hit = 0;
    s32 dir;
    register s32 tx ASM_REG("$16");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 ty ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    u16 stat;
    s32 flags;

    stat = D_80083462;

    if ((stat & 0x4000) || ((S_8017405C_0 *)d)->unk_71.s >= 0) {
        if (((S_8017405C_0 *)d)->unk_71.s >= 0 || func_80174BCC(a, b, c, d) == 0) {
            func_800A9A0C(d);
        } else {
            ((S_8017405C_0 *)d)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(stat & 0x2000)) {
        return;
    }

    func_800A19E4(c, d, 3, 6, (u8 *)a + 0x9C);
    ASM_KEEP(hit);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    flags = ((S_8017405C_0 *)d)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            register void *e ASM_REG("$3") = func_800A02AC(d, c->unk_24.at00.v, c->unk_24.at01.v);   /* MATCH pin: retail delay-slot fill depends on it */
            if (e != 0) {
                S_8017405C_3 *e2 = ((S_8017405C_2_pre *)e)[-1].unk_00;
                ((S_8017405C_0 *)d)->unk_2A.u = func_800A0818(c->unk_24.at00.v, c->unk_24.at01.v,
                                                    e2->unk_24, e2->unk_25,
                                                    (u8 *)a + 0x98);
                ((S_8017405C_0 *)d)->unk_71.u &= 0x7F;
                return;
            }
            {
                register s32 t14 ASM_REG("$2") = ((S_8017405C_0 *)d)->unk_14;   /* MATCH pin: load-bearing for the whole function shape */
                if (t14 >= 0) {
                    ((S_8017405C_0 *)d)->unk_14 = t14 | 0x80000000;
                    ((S_8017405C_0 *)d)->unk_2A.u += (func_800A6D30() & 7) << 9;
                }
            }
            goto loop_entry;
        }
        if (func_800A04F0(d, c->unk_24.at00.v, c->unk_24.at01.v, ((S_8017405C_0 *)d)->unk_2A.s) == 0) {
            goto loop_entry;
        }
        goto clear71;
    }
    if (flags & 0x2000) {
        if (((S_8017405C_0 *)d)->unk_46 & 0x8000) {
            goto loop_entry;
        }
        if (!(flags & 0x20000)) {
            goto call_e6c;
        }
        {
            void **root_page = &D_800814A8;
            void *root;
            register u8 *e80 ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register unsigned long xmix ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
            unsigned long k;
            register s32 ex ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 ey ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 yoff ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
            u8 cx;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            e80 = D_80082E80;
            xmix = (unsigned long)D_8006CCD8;
            root = *root_page;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            k = ((S_8017405C_0 *)d)->unk_45;
            ex = e80[0x24];
            k += (s16)((S_8017405C_4 *)root)->unk_2A >> 9;
            ey = e80[0x25];
            k &= 7;
            k <<= 1;
            xmix += k;
            {
                u16 *t2 = D_8006CCE8;
                k += (unsigned long)t2;
                xmix = *(u16 *)xmix;
                yoff = *(u16 *)k;
            }
            cx = c->unk_24.at00.v;
            tx = ex + (s32)xmix;
            ty = ey + yoff;
            if (cx == (u16)tx && c->unk_24.at01.v == (u16)ty) {
                goto clear71;
            }
        }
        {
            void *pp = (u8 *)a + 0x98;
            u16 r = func_800A0818(c->unk_24.at00.v, c->unk_24.at01.v, (s16)tx, (s16)ty, pp);
            ((S_8017405C_0 *)d)->unk_2A.u = r;
            if (func_8009A66C((s16)r, c, d, 0x20) > 0) {
                goto loop_entry;
            }
            {
                u8 *e80b = (u8 *)&D_80082EA4 - 0x24;
                ((S_8017405C_0 *)d)->unk_2A.u = func_800A0818(c->unk_24.at00.v, c->unk_24.at01.v,
                                                    e80b[0x24], e80b[0x25], pp);
            }
        }
        goto loop_entry;
    }
    {
        s32 m = c->unk_26.s;
        if (m >= 0 && (D_800E2970[m].flags & 2)) {
call_e6c:
            func_800A0E6C(c, ((Rec_func_800A9E70_arg0 *)a)->unk_9C.as_s8, d, (u8 *)a + 0x98);
            goto loop_entry;
        }
    }
    if (!(((S_8017405C_0 *)d)->unk_46 & 0x8000)) {
        register void *e ASM_REG("$3") = func_800A04F0(d, c->unk_24.at00.v, c->unk_24.at01.v, ((S_8017405C_0 *)d)->unk_2A.s);   /* MATCH pin: retail delay-slot fill depends on it */
        if (e != 0 && (((S_8017405C_2 *)e)->unk_1C & 0x2000) && func_800A0134(e, d) < 0x81) {
            if (func_8009A540((((s16)((S_8017405C_0 *)d)->unk_2A.u >> 9) & 0xFFFF),
                              c->unk_24.at00.v, c->unk_24.at01.v,
                              (s16)(((S_8017405C_0 *)d)->unk_88 - 0x20)) != 0) {
                goto clear71;
            }
        }
    }
    if (((S_8017405C_0 *)d)->unk_1C & 0x20000) {
        void *pa;
        void *pb;
        ((Rec_func_800A9E70_arg0 *)a)->unk_A6 = 0;
        pa = ((Rec_D_800814A8 *)D_800814A8)->unk_AC;
        if (pa != 0) {
            pb = ((Rec_D_800814A8 *)D_800814A8)->unk_B0;
            if (pb != 0) {
                goto masters;
            }
        }
        {
            u8 *e80 = D_80082E80;
            s32 delta;
            s32 t;
            delta = func_800A07D0(e80[0x24], e80[0x25],
                                  c->unk_24.at00.v, c->unk_24.at01.v);
            t = (((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 + delta) & 0xFFF;
            if (t > 0x400 && t < 0xC00) {
                ((S_8017405C_0 *)d)->unk_45 = 3;
            } else if (t == 0x400 || t == 0xC00) {
                ((S_8017405C_0 *)d)->unk_45 = 1;
            } else {
                ((S_8017405C_0 *)d)->unk_45 = 2;
            }
        }
        {
            void **root_page = &D_800814A8;
            void *root;
            register u8 *e80 = D_80082E80;
            register unsigned long xmix ASM_REG("$7");   /* MATCH pin: keeps a constant in a register as retail does */
            unsigned long k;
            s32 xsum;
            register u16 tx2 ASM_REG("$16");   /* MATCH pin: retail delay-slot fill depends on it */
            register u16 ty2 ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
            s32 cx2;
            s32 cy2;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            xmix = (unsigned long)D_8006CCD8;
            root = *root_page;
            cx2 = c->unk_24.at00.v;
            cy2 = c->unk_24.at01.v;
            k = (((S_8017405C_0 *)d)->unk_45 + ((s16)((S_8017405C_4 *)root)->unk_2A >> 9)) & 7;
            xsum = *(volatile u8 *)(e80 + 0x24);
            k <<= 1;
            xmix += k;
            {
                u16 *t2 = D_8006CCE8;
                k += (unsigned long)t2;
                xmix = *(u16 *)xmix;
                k = *(u16 *)k;
            }
            xsum += (s32)xmix;
            tx2 = xsum;
            xsum = (s16)xsum;
            xmix = e80[0x25];
            xmix += k;
            ty2 = (s32)xmix;
            xmix = (s16)(s32)xmix;
            ((S_8017405C_0 *)d)->unk_2A.u = func_800A0818(cx2, cy2,
                                                xsum, (s32)xmix, (u8 *)a + 0x98);
            {
                s32 curx = c->unk_24.at00.v;
                register s32 wantx ASM_REG("$2") = (u16)tx2;   /* MATCH pin: load-bearing for the whole function shape */
                if (curx != wantx) {
                    goto loop_entry;
                }
            }
            {
                s32 cury = c->unk_24.at01.v;
                register s32 wanty ASM_REG("$2") = (u16)ty2;   /* MATCH pin: load-bearing for the whole function shape */
                if (cury != wanty) {
                    goto loop_entry;
                }
            }
        }
        goto clear71;
masters:
        {
            void *p2 = ((S_8017405C_7_pre *)pa)[-1].unk_00;
            register void *p1 ASM_REG("$17") = ((S_8017405C_8_pre *)pb)[-1].unk_00;   /* MATCH pin: load-bearing for the whole function shape */
            s16 r1 = func_8009FD40(p2, c);
            if (r1 < func_8009FD40(p1, c)) {
                ((S_8017405C_0 *)d)->unk_2A.u = func_800A0818(c->unk_24.at00.v, c->unk_24.at01.v,
                                                    ((S_8017405C_9 *)p2)->unk_24, ((S_8017405C_9 *)p2)->unk_25,
                                                    (u8 *)a + 0x98);
                if (func_8009FD7C(c->unk_24.at00.v, c->unk_24.at01.v,
                                  ((S_8017405C_9 *)p2)->unk_24, ((S_8017405C_9 *)p2)->unk_25) == 0) {
                    goto loop_entry;
                }
                goto clear71;
            }
            ((S_8017405C_0 *)d)->unk_2A.u = func_800A0818(c->unk_24.at00.v, c->unk_24.at01.v,
                                                ((S_8017405C_10 *)p1)->unk_24, ((S_8017405C_10 *)p1)->unk_25,
                                                (u8 *)a + 0x98);
            if (func_8009FD7C(c->unk_24.at00.v, c->unk_24.at01.v,
                              ((S_8017405C_9 *)p2)->unk_24, ((S_8017405C_9 *)p2)->unk_25) == 0) {
                goto loop_entry;
            }
            ASM_KEEP(p2);   /* MATCH pin: retail basic-block layout depends on it */
            goto clear71;
        }
    }
    if (((Rec_func_800A9E70_arg0 *)a)->unk_A6 != 0) {
        goto loop_entry;
    }
    ((Rec_func_800A9E70_arg0 *)a)->unk_A6 = 1;
    ((Rec_func_800A9E70_arg0 *)a)->unk_A4 = ((func_800A6D30() & 3) << 10) + 0x200;

loop_entry:
    idx = 0;
    {
        s16 *tbl = D_8006CD00;
loop_head:
        {
            if (((Rec_func_800A9E70_arg0 *)a)->unk_A6 != 0) {
                s32 bb = ((Rec_func_800A9E70_arg0 *)a)->unk_A4;
                if (((Rec_func_800A9E70_arg0 *)a)->unk_98 & 2) {
                    dir = bb - tbl[idx];
                } else {
                    dir = bb + tbl[idx];
                }
            } else {
                register s32 bb ASM_REG("$3") = ((S_8017405C_0 *)d)->unk_2A.s;   /* MATCH pin: retail delay-slot fill depends on it */
                if (((Rec_func_800A9E70_arg0 *)a)->unk_98 & 2) {
                    dir = bb - tbl[idx];
                } else {
                    dir = bb + tbl[idx];
                }
            }
            if (func_8009A66C(dir, c, d, 0x20) > 0) {
                if (idx >= 3) {
                    if (hit != 0) {
                        goto clear71;
                    }
                    if (((Rec_func_800A9E70_arg0 *)a)->unk_A6 != 0) {
                        goto clear71;
                    }
                }
                ((S_8017405C_0 *)d)->unk_2A.u = dir;
                ((S_8017405C_11 *)((u8 *)d + (((S_8017405C_0 *)d)->unk_71.u & 0x7F)))->unk_74 = c->unk_24.at00.v;
                ((S_8017405C_11 *)((u8 *)d + (((S_8017405C_0 *)d)->unk_71.u & 0x7F)))->unk_7C = c->unk_24.at01.v;
                ((S_8017405C_0 *)d)->unk_71.u = ((S_8017405C_0 *)d)->unk_71.u + 1;
                func_8009A3D0(c->unk_24.at00.v, c->unk_24.at01.v,
                              (((S_8017405C_0 *)d)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                {
                    s32 j;
                    register u8 *bt1 ASM_REG("$3") = (u8 *)D_8006CCD8;   /* MATCH pin: retail delay-slot fill depends on it */
                    j = (((S_8017405C_0 *)d)->unk_2A.u >> 8) & 0xE;
                    c->unk_24.at00.v = c->unk_24.at00.v +
                                         *(u8 *)((unsigned long)j + (unsigned long)bt1);
                    {
                        u8 *bt2 = (u8 *)D_8006CCE8;
                        c->unk_24.at01.v = c->unk_24.at01.v +
                                             *(u8 *)((unsigned long)j + (unsigned long)bt2);
                    }
                }
                func_8009A21C(c->unk_24.at00.v, c->unk_24.at01.v,
                              (((S_8017405C_0 *)d)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                goto loop_done;
            }
            if (idx == 0 && D_80082EA4 != c->unk_24.at00u.v) {
                ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
                if (func_8009A180(d, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pu8 + 0x20) != 0) {
                    return;
                }
            }
            idx = idx + 1;
            if (idx < 8) {
                goto loop_head;
            }
        }
    }
loop_done:

    if (idx >= 8) {
        ((S_8017405C_0 *)d)->unk_71.u &= 0x7F;
        ((S_8017405C_0 *)d)->unk_46 &= 0x7FFF;
        func_800A9A0C(d);
        return;
    }
    {
        u16 *cnt = D_80083460;
        ((S_8017405C_0 *)d)->unk_46 &= 0x7FFF;
        ((Rec_func_800A9E70_arg0 *)a)->unk_9C.as_s8 = c->unk_26.u;
        ((S_8017405C_0 *)d)->unk_6D.u = ((S_8017405C_0 *)d)->unk_6D.u - 1;
        cnt[4] = cnt[4] + 1;
    }
    if (((S_8017405C_0 *)d)->unk_6D.s != 0) {
        goto do_bcb;
    }
clear71:
    ((S_8017405C_0 *)d)->unk_71.u &= 0x7F;
    return;
do_bcb:
    idx = func_800BCB04((c->unk_24.at00.v << 6) | 0x20,
                        (c->unk_24.at01.v << 6) | 0x20,
                        (s16)(((S_8017405C_0 *)d)->unk_88 - 0x20));
    if (idx < 0x200) {
        ((S_8017405C_0 *)d)->unk_88 = idx;
    }
    return;
}
