#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

void func_8017405C(void *a, s32 b, void *c, void *d)
{
    s16 idx;
    s16 hit = 0;
    s32 dir;
    register s32 tx ASM_REG("$16");
    register s32 ty ASM_REG("$17");
    u16 stat;
    s32 flags;

    stat = D_80083462;

    if ((stat & 0x4000) || FIELD(d, s8, 0x71) >= 0) {
        if (FIELD(d, s8, 0x71) >= 0 || func_80174BCC(a, b, c, d) == 0) {
            func_800A9A0C(d);
        } else {
            FIELD(d, u16, 0x46) = 0xC008;
        }
        return;
    }
    if (!(stat & 0x2000)) {
        return;
    }

    func_800A19E4(c, d, 3, 6, (u8 *)a + 0x9C);
    ASM_KEEP(hit);
    flags = FIELD(d, s32, 0x1C);
    if (flags & 0x410) {
        if (flags & 0x400) {
            register void *e ASM_REG("$3") = func_800A02AC(d, FIELD(c, u8, 0x24), FIELD(c, u8, 0x25));
            ASM_KEEP(e);
            if (e != 0) {
                void *e2 = FIELD(e, void *, -0x14);
                FIELD(d, u16, 0x2A) = func_800A0818(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                                                    FIELD(e2, u8, 0x24), FIELD(e2, u8, 0x25),
                                                    (u8 *)a + 0x98);
                FIELD(d, u8, 0x71) &= 0x7F;
                return;
            }
            {
                register s32 t14 ASM_REG("$2") = FIELD(d, s32, 0x14);
                ASM_KEEP(t14);
                if (t14 >= 0) {
                    FIELD(d, s32, 0x14) = t14 | 0x80000000;
                    FIELD(d, u16, 0x2A) += (func_800A6D30() & 7) << 9;
                }
            }
            goto loop_entry;
        }
        if (func_800A04F0(d, FIELD(c, u8, 0x24), FIELD(c, u8, 0x25), FIELD(d, s16, 0x2A)) == 0) {
            goto loop_entry;
        }
        goto clear71;
    }
    if (flags & 0x2000) {
        if (FIELD(d, u16, 0x46) & 0x8000) {
            goto loop_entry;
        }
        if (!(flags & 0x20000)) {
            goto call_e6c;
        }
        {
            void **root_page = &D_800814A8;
            void *root;
            register u8 *e80 ASM_REG("$5");
            register unsigned long xmix ASM_REG("$4");
            register unsigned long k ASM_REG("$3");
            register s32 ex ASM_REG("$6");
            register s32 ey ASM_REG("$5");
            register s32 yoff ASM_REG("$2");
            u8 cx;
            ASM_SCHED_BARRIER();
            e80 = D_80082E80;
            xmix = (unsigned long)D_8006CCD8;
            root = *root_page;
            ASM_SCHED_BARRIER();
            k = FIELD(d, u8, 0x45);
            ex = e80[0x24];
            k += (s16)FIELD(root, u16, 0x2A) >> 9;
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
            cx = FIELD(c, u8, 0x24);
            tx = ex + (s32)xmix;
            ASM_KEEP(tx);
            ty = ey + yoff;
            if (cx == (u16)tx && FIELD(c, u8, 0x25) == (u16)ty) {
                goto clear71;
            }
        }
        {
            void *pp = (u8 *)a + 0x98;
            u16 r = func_800A0818(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25), (s16)tx, (s16)ty, pp);
            FIELD(d, u16, 0x2A) = r;
            if (func_8009A66C((s16)r, c, d, 0x20) > 0) {
                goto loop_entry;
            }
            {
                u8 *e80b = (u8 *)&D_80082EA4 - 0x24;
                FIELD(d, u16, 0x2A) = func_800A0818(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                                                    e80b[0x24], e80b[0x25], pp);
            }
        }
        goto loop_entry;
    }
    {
        s32 m = FIELD(c, s8, 0x26);
        if (m >= 0 && (D_800E2970[m].flags & 2)) {
call_e6c:
            func_800A0E6C(c, FIELD(a, s8, 0x9C), d, (u8 *)a + 0x98);
            goto loop_entry;
        }
    }
    if (!(FIELD(d, u16, 0x46) & 0x8000)) {
        register void *e ASM_REG("$3") = func_800A04F0(d, FIELD(c, u8, 0x24), FIELD(c, u8, 0x25), FIELD(d, s16, 0x2A));
        ASM_KEEP(e);
        if (e != 0 && (FIELD(e, s32, 0x1C) & 0x2000) && func_800A0134(e, d) < 0x81) {
            if (func_8009A540((((s16)FIELD(d, u16, 0x2A) >> 9) & 0xFFFF),
                              FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                              (s16)(FIELD(d, u16, 0x88) - 0x20)) != 0) {
                goto clear71;
            }
        }
    }
    if (FIELD(d, s32, 0x1C) & 0x20000) {
        register void *pa ASM_REG("$4");
        void *pb;
        FIELD(a, u8, 0xA6) = 0;
        pa = FIELD(D_800814A8, void *, 0xAC);
        ASM_KEEP(pa);
        if (pa != 0) {
            pb = FIELD(D_800814A8, void *, 0xB0);
            if (pb != 0) {
                goto masters;
            }
        }
        {
            u8 *e80 = D_80082E80;
            s32 delta;
            s32 t;
            ASM_KEEP(e80);
            delta = func_800A07D0(e80[0x24], e80[0x25],
                                  FIELD(c, u8, 0x24), FIELD(c, u8, 0x25));
            t = (FIELD(D_800814A8, u16, 0x2A) + delta) & 0xFFF;
            if (t > 0x400 && t < 0xC00) {
                FIELD(d, u8, 0x45) = 3;
            } else if (t == 0x400 || t == 0xC00) {
                FIELD(d, u8, 0x45) = 1;
            } else {
                FIELD(d, u8, 0x45) = 2;
            }
        }
        {
            void **root_page = &D_800814A8;
            void *root;
            register u8 *e80 = D_80082E80;
            register unsigned long xmix ASM_REG("$7");
            register unsigned long k ASM_REG("$3");
            register s32 xsum ASM_REG("$6");
            register u16 tx2 ASM_REG("$16");
            register u16 ty2 ASM_REG("$17");
            s32 cx2;
            s32 cy2;
            ASM_SCHED_BARRIER();
            xmix = (unsigned long)D_8006CCD8;
            root = *root_page;
            cx2 = FIELD(c, u8, 0x24);
            cy2 = FIELD(c, u8, 0x25);
            k = (FIELD(d, u8, 0x45) + ((s16)FIELD(root, u16, 0x2A) >> 9)) & 7;
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
            FIELD(d, u16, 0x2A) = func_800A0818(cx2, cy2,
                                                xsum, (s32)xmix, (u8 *)a + 0x98);
            {
                register s32 curx ASM_REG("$3") = FIELD(c, u8, 0x24);
                register s32 wantx ASM_REG("$2") = (u16)tx2;
                if (curx != wantx) {
                    goto loop_entry;
                }
            }
            {
                register s32 cury ASM_REG("$3") = FIELD(c, u8, 0x25);
                register s32 wanty ASM_REG("$2") = (u16)ty2;
                if (cury != wanty) {
                    goto loop_entry;
                }
            }
        }
        goto clear71;
masters:
        {
            register void *p2 ASM_REG("$18") = FIELD(pa, void *, -0x14);
            register void *p1 ASM_REG("$17") = FIELD(pb, void *, -0x14);
            s16 r1 = func_8009FD40(p2, c);
            if (r1 < func_8009FD40(p1, c)) {
                FIELD(d, u16, 0x2A) = func_800A0818(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                                                    FIELD(p2, u8, 0x24), FIELD(p2, u8, 0x25),
                                                    (u8 *)a + 0x98);
                ASM_KEEP(p2);
                if (func_8009FD7C(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                                  FIELD(p2, u8, 0x24), FIELD(p2, u8, 0x25)) == 0) {
                    goto loop_entry;
                }
                goto clear71;
            }
            FIELD(d, u16, 0x2A) = func_800A0818(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                                                FIELD(p1, u8, 0x24), FIELD(p1, u8, 0x25),
                                                (u8 *)a + 0x98);
            if (func_8009FD7C(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                              FIELD(p2, u8, 0x24), FIELD(p2, u8, 0x25)) == 0) {
                goto loop_entry;
            }
            ASM_KEEP(p2);
            goto clear71;
        }
    }
    if (FIELD(a, u8, 0xA6) != 0) {
        goto loop_entry;
    }
    FIELD(a, u8, 0xA6) = 1;
    FIELD(a, s16, 0xA4) = ((func_800A6D30() & 3) << 10) + 0x200;

loop_entry:
    idx = 0;
    {
        s16 *tbl = D_8006CD00;
loop_head:
        {
            if (FIELD(a, u8, 0xA6) != 0) {
                register s32 bb ASM_REG("$3") = FIELD(a, s16, 0xA4);
                if (FIELD(a, u16, 0x98) & 2) {
                    dir = bb - tbl[idx];
                } else {
                    dir = bb + tbl[idx];
                }
            } else {
                register s32 bb ASM_REG("$3") = FIELD(d, s16, 0x2A);
                if (FIELD(a, u16, 0x98) & 2) {
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
                    if (FIELD(a, u8, 0xA6) != 0) {
                        goto clear71;
                    }
                }
                FIELD(d, u16, 0x2A) = dir;
                FIELD((u8 *)d + (FIELD(d, u8, 0x71) & 0x7F), u8, 0x74) = FIELD(c, u8, 0x24);
                FIELD((u8 *)d + (FIELD(d, u8, 0x71) & 0x7F), u8, 0x7C) = FIELD(c, u8, 0x25);
                FIELD(d, u8, 0x71) = FIELD(d, u8, 0x71) + 1;
                func_8009A3D0(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                              (FIELD(d, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
                {
                    s32 j;
                    register u8 *bt1 ASM_REG("$3") = (u8 *)D_8006CCD8;
                    ASM_KEEP(bt1);
                    j = (FIELD(d, u16, 0x2A) >> 8) & 0xE;
                    FIELD(c, u8, 0x24) = FIELD(c, u8, 0x24) +
                                         *(u8 *)((unsigned long)j + (unsigned long)bt1);
                    ASM_SCHED_BARRIER();
                    {
                        u8 *bt2 = (u8 *)D_8006CCE8;
                        ASM_KEEP(bt2);
                        FIELD(c, u8, 0x25) = FIELD(c, u8, 0x25) +
                                             *(u8 *)((unsigned long)j + (unsigned long)bt2);
                    }
                }
                func_8009A21C(FIELD(c, u8, 0x24), FIELD(c, u8, 0x25),
                              (FIELD(d, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
                goto loop_done;
            }
            if (idx == 0 && D_80082EA4 != FIELD(c, u16, 0x24)) {
                ASM_SCHED_BARRIER();
                if (func_8009A180(d, FIELD(D_800814A8, u8 *, 0x58) + 0x20) != 0) {
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
        FIELD(d, u8, 0x71) &= 0x7F;
        FIELD(d, u16, 0x46) &= 0x7FFF;
        func_800A9A0C(d);
        return;
    }
    {
        u16 *cnt = D_80083460;
        FIELD(d, u16, 0x46) &= 0x7FFF;
        FIELD(a, s8, 0x9C) = FIELD(c, u8, 0x26);
        FIELD(d, u8, 0x6D) = FIELD(d, u8, 0x6D) - 1;
        cnt[4] = cnt[4] + 1;
    }
    if (FIELD(d, s8, 0x6D) != 0) {
        goto do_bcb;
    }
clear71:
    FIELD(d, u8, 0x71) &= 0x7F;
    return;
do_bcb:
    idx = func_800BCB04((FIELD(c, u8, 0x24) << 6) | 0x20,
                        (FIELD(c, u8, 0x25) << 6) | 0x20,
                        (s16)(FIELD(d, u16, 0x88) - 0x20));
    if (idx < 0x200) {
        FIELD(d, u16, 0x88) = idx;
    }
    return;
}
