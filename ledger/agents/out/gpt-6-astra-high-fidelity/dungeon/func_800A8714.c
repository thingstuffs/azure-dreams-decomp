#include "common.h"
#ifndef NULL
#define NULL 0
#endif

/* ---- globals (declared array-style so every access stays %hi/%lo, never $gp) ---- */
extern u16 D_80013714[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80082E80[];
extern u16 D_8008347E[];
extern void *D_800814A8[];
extern s32 D_800E296C[];
typedef struct D_800E2970Entry {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} D_800E2970Entry;
extern D_800E2970Entry D_800E2970[];
typedef struct CFlags46 { u8 pad_00[0x46]; u16 f46; } CFlags46;
extern u8 D_800E3548[];
extern u8 *D_800E3D7C[];
extern void *D_80089088[];

/* ---- ordinary callees ---- */
extern s32 func_80042900();
extern s32 func_80098B38();
extern s32 func_8009A350();
extern u8 *func_8009B25C();
extern s32 func_8009CD58();
extern s32 func_8009FD40();
extern s32 func_800A0134();
extern u8 *func_800A02AC();
extern u8 *func_800A03C4();
extern u8 *func_800A05A4();
extern s32 func_800A0818();
extern s32 func_800A0E6C();
extern s32 func_800A19E4();
extern s32 func_800A2C34();
extern s32 func_800A2CAC();
extern s32 func_800A2CB8();
extern s32 func_800A3518();
extern s32 func_800A3544();
extern s32 func_800A35A4();
extern s32 func_800A365C();
extern s32 func_800A36B4();
extern s32 func_800A384C();
extern u8 *func_800A3D18();
extern s32 func_800A404C();
extern s32 func_800A40AC();
extern s32 func_800A41F0();
extern s32 func_800A45D8();
extern s32 func_800A6E8C();
extern s32 func_800A70E4();
extern s32 func_800A9A0C();
extern s32 func_800AA53C();
extern s32 func_800ADD20();
extern s32 func_800BCB04();
extern s32 func_800C7F68();

/* direction-vector neighbour probe (repeated 8x in retail) */
#define STEPVEC(res)                                                            \
    do {                                                                        \
        u16 dv_ = (*(u16 *)(c + 0x2A) >> 9) & 7;                                \
        sp1E = dv_;                                                             \
        res = func_8009B25C(c,                                                  \
            (u16)(p[0x24] + *(u16 *)((dv_ * 2) + (u8 *)D_8006CCD8)),            \
            (u16)(p[0x25] + *(u16 *)((dv_ * 2) + (u8 *)D_8006CCE8)),            \
            *(s16 *)(c + 0x88));                                                \
    } while (0)

s32 func_800ADE74(s32 arg0, u8 *pArg, u8 *cArg, s32 arg3, u16 arg4, volatile s32 arg5)
{
    register u8 *p ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u8 *c ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 cv_ ASM_REG("$2"); /* MATCH: both entries feed the shared neighbour guard in v0. */
    s32 a3keep;
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    u16 sp1E;
    s16 sp20;
    s32 var_fp;
    s32 r;
    s32 t;
    s32 rj;
    s32 ta, tb, tc, td, te, tf, tg, th, tr;
    s32 ua, ub, uc, ud, ue, uf;
    s32 s2c;
    s32 par;
    s32 s4o;
    s32 nbv;
    u8 nb;
    u8 *eA;
    u8 *eB;
    u8 *eC;
    u8 *eD;
    u8 *eE;
    u8 *eF;
    u8 *o;
    u8 *tn;
    u8 *s1v;
    u8 *pp;
    u16 nvx;
    u8 *tv;
    u8 *t0;

    p = pArg;
    ASM_USE_NV(p);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    c = cArg;
    var_fp = 2;
    a3keep = arg3;
    ((CFlags46 *)c)->f46 |= 0x4000;
    if (D_80013714[0] & 8) {
        func_800A9A0C(c);
        return -1;
    }
    if (c[0x25] == 0) {
        var_fp = 0;
        goto Lret_fp;
    }
    if ((func_800A2CAC(c) << 16) != 0) {
        if ((func_800A6E8C(p, 0x60C, &sp18, &sp1A) << 16) != 0) {
            if (c[0x13] != 0x22) {
                if ((func_800A2C34(c) << 16) != 0) {
                    return -1;
                }
                if (sp18 == p[0x24] && sp1A == p[0x25]) {
                    s16 t70 = func_800A70E4(sp18, sp1A, *(s16 *)(c + 0x88));
                    if (t70 >= 0) {
                        s32 hp = *(u16 *)(c + 0x24);
                        if (0x10000 < (s32)hp) {
                            hp = 0xFFFF;
                        }
                        *(u16 *)(c + 0x24) = hp;
                        if (c[0x25] != 0) {
                            *(s32 *)(c + 0x1C) &= ~8;
                        }
                        {
                            u8 lim = c[0x66];
                            if (lim < c[0x25]) {
                                c[0x25] = lim;
                                c[0x24] = 0xFF;
                            }
                        }
                        func_80098B38((t70 * 4) + (u8 *)D_800E3548);
                    }
                    return 0;
                }
                *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], sp18, sp1A, &sp1C);
                *(u16 *)(c + 0x46) = 0x800B;
                return 2;
            }
        }
    }
    /* Lmain (0x800A88E0) */
    func_800A19E4(p, c, (s16)a3keep, (s16)arg4, arg5);
    if ((*(s32 *)(c + 0x1C) & 0x2410) != 0x2000) {
        goto L90b0;
    }
    {
        u8 *d = D_800E3D7C[0];
        nb = c[0x12];
        if ((*(s32 *)(d + 0x1C) & 0x220) || (func_80042900(d, 0xA) << 16) != 0) {
            if (*(s32 *)(c + 0x1C) & 0x20000) {
                if (nb != 0) {
                    nb = 1;
                }
            }
        }
        nbv = nb;
    }
    if (nbv == 1) {
        goto Lcase1;
    }
    if (nbv < 2) {
        if (nbv == 0) {
            goto Lcase0;
        }
        goto L9094;
    }
    if (nbv == 2) {
        goto Lcase2;
    }
    if (nbv == 4) {
        goto Lcase4;
    }
    goto L9094;

Lcase0: /* 0x800A89A8 */
    if ((func_800A2C34(c) << 16) != 0) {
        return -1;
    }
    if ((func_80042900(c, 6) << 16) == 0) {
        s32 r1 = func_800A3544(c, 0x1E);
        sp1C = r1;
        if ((r1 << 16) >= 0) {
            if (*(s32 *)(c + 0x1C) & 0x20000) {
                eA = D_80082E80;
                ta = func_8009FD40(p, eA);
                ua = func_800A35A4(c, sp1C);
                if ((ta << 16) < (ua << 16)) {
                    if ((func_800A3518(D_800E3D7C[0]) << 16) != 0) {
                        s32 rv_;
                        register void *hv_ ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        *(u16 *)(c + 0x46) = (*(u16 *)&sp1C + 1) | 0x8000;
                        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], eA[0x24], eA[0x25], &sp1C);
                        hv_ = D_800814A8[0];
                        ASM_KEEP(hv_);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        rv_ = 4;
                        *(void **)(c + 0x60) = hv_;
                        return rv_;
                    }
                }
            }
            s2c = 0;
Lc0loop:
            par = D_8008347E[0] & 1;
            do {
                s4o = par * 4;
                t0 = *(void **)((s4o + (s32)D_800814A8[0]) + 0xAC);
                if (t0 != NULL) {
                    s1v = *(void **)(t0 - 0x14);
                    tb = func_8009FD40(p, s1v);
                    ub = func_800A35A4(c, sp1C);
                    if ((tb << 16) < (ub << 16)) {
                        if ((func_800A3518(*(void **)((s4o + (s32)D_800814A8[0]) + 0xAC)) << 16) != 0) {
                            {
                            { s32 pg_, nx_;
                            nvx = *(u16 *)&sp1C;
                            pg_ = (s32)D_800814A8[0];
                            nx_ = nvx + 1;
                            nx_ |= 0x8000;
                            pp = (u8 *)(s4o + pg_);
                            *(u16 *)(c + 0x46) = nx_;
                            }
                            if (c != *(u8 **)(pp + 0xAC)) {
                                *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], s1v[0x24], s1v[0x25], &sp1C);
                            }
                            *(void **)(c + 0x60) = *(void **)((s4o + (s32)D_800814A8[0]) + 0xAC);
                            return 4;
                            }
                        }
                    }
                }
                s2c++;
                par ^= 1;
            } while (s2c < 2);
        }
    }
    /* 0x800A8B30 */
    tv = func_800A3D18(p, c, 4);
    *(void **)(c + 0x60) = tv;
    if (tv == NULL) {
        goto L9094;
    }
    {
        s32 ret_;
        register s32 car_ ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 rv_;
        ret_ = func_800A384C(c, tv, &sp1E, 0);
        sp20 = ret_;
        *(u16 *)(c + 0x2A) = *(u16 *)&sp1E;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        car_ = ret_;
        if ((car_ << 16) < 0) {
            goto Laa190;
        }
        rj = car_ | 0x8000;
        goto Lstore1;
    }

Lcase1: /* 0x800A8B80 */
    if ((func_800A2C34(c) << 16) != 0) {
        return -1;
    }
    if ((func_80042900(c, 6) << 16) == 0) {
        s32 r1 = func_800A3544(c, 0x1E);
        sp1C = r1;
        if ((r1 << 16) >= 0) {
            if (*(s32 *)(c + 0x1C) & 0x20000) {
                eB = D_80082E80;
                tc = func_8009FD40(p, eB);
                uc = func_800A35A4(c, sp1C);
                if ((tc << 16) < (uc << 16)) {
                    if ((func_800A3518(D_800814A8[0]) << 16) != 0) {
                        void *hv_;
                        register s32 r0818 ASM_REG("$2"); /* MATCH: retain the direction result in v0 until its store. */
                        *(u16 *)(c + 0x46) = (*(u16 *)&sp1C + 1) | 0x8000;
                        r0818 = func_800A0818(p[0x24], p[0x25], eB[0x24], eB[0x25], &sp1C);
                        hv_ = D_800814A8[0];
                        ASM_KEEP(hv_);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        *(u16 *)(c + 0x2A) = r0818;
                        *(void **)(c + 0x60) = hv_;
                        return 4;
                    }
                }
            }
            s2c = 0;
Lc1loop:
            par = D_8008347E[0] & 1;
            do {
                s4o = par * 4;
                t0 = *(void **)((s4o + (s32)D_800814A8[0]) + 0xAC);
                if (t0 != NULL) {
                    s1v = *(void **)(t0 - 0x14);
                    td = func_8009FD40(p, s1v);
                    ud = func_800A35A4(c, sp1C);
                    if ((td << 16) < (ud << 16)) {
                        if ((func_800A3518(*(void **)((s4o + (s32)D_800814A8[0]) + 0xAC)) << 16) != 0) {
                            {
                            { s32 pg_, nx_;
                            nvx = *(u16 *)&sp1C;
                            pg_ = (s32)D_800814A8[0];
                            nx_ = nvx + 1;
                            nx_ |= 0x8000;
                            pp = (u8 *)(s4o + pg_);
                            *(u16 *)(c + 0x46) = nx_;
                            }
                            if (c != *(u8 **)(pp + 0xAC)) {
                                *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], s1v[0x24], s1v[0x25], &sp1C);
                            }
                            *(void **)(c + 0x60) = *(void **)((s4o + (s32)D_800814A8[0]) + 0xAC);
                            return 4;
                            }
                        }
                    }
                }
                s2c++;
                par ^= 1;
            } while (s2c < 2);
        }
    }
    /* 0x800A8D00 */
    tv = func_800A3D18(p, c, -3);
    *(void **)(c + 0x60) = tv;
    if (tv == NULL) {
        goto L9094;
    }
    {
        s32 ret_;
        register s32 car_ ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 rv_;
        ret_ = func_800A384C(c, tv, &sp1E, 0);
        sp20 = ret_;
        *(u16 *)(c + 0x2A) = *(u16 *)&sp1E;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        car_ = ret_;
        if ((s16)car_ < 4) {
            goto Laa190;
        }
        rj = car_ | 0x8000;
        goto Lstore1;
    }

Lcase2: /* 0x800A8D58 */
    if ((func_80042900(c, 6) << 16) == 0) {
        s32 r3 = func_800A3544(c, 0x1E);
        sp1C = r3;
        if ((r3 << 16) < 0) {
            goto L8f48;
        }
        if (*(s32 *)(c + 0x1C) & 0x20000) {
            eC = D_80082E80;
            te = func_8009FD40(p, eC);
            ue = func_800A35A4(c, sp1C);
            if ((te << 16) < (ue << 16)) {
                if ((func_800A3518(D_800814A8[0]) << 16) != 0) {
                    if ((func_800A2C34(c) << 16) != 0) {
                        return -1;
                    }
                    {
                        void *hv_;
                        register s32 r0818 ASM_REG("$2"); /* MATCH: retain the direction result in v0 until its store. */
                        *(u16 *)(c + 0x46) = (*(u16 *)&sp1C + 1) | 0x8000;
                        r0818 = func_800A0818(p[0x24], p[0x25], eC[0x24], eC[0x25], &sp1C);
                        hv_ = D_800814A8[0];
                        ASM_KEEP(hv_);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        *(u16 *)(c + 0x2A) = r0818;
                        *(void **)(c + 0x60) = hv_;
                        return 4;
                    }
                }
            }
        }
        s2c = 0;
Lc2loop:
        par = D_8008347E[0] & 1;
        do {
            s4o = par * 4;
            t0 = *(void **)((s4o + (s32)D_800814A8[0]) + 0xAC);
            if (t0 != NULL) {
                s1v = *(void **)(t0 - 0x14);
                tf = func_8009FD40(p, s1v);
                uf = func_800A35A4(c, sp1C);
                if ((tf << 16) < (uf << 16)) {
                    if ((func_800A3518(*(void **)((s4o + (s32)D_800814A8[0]) + 0xAC)) << 16) != 0) {
                        if ((func_800A2C34(c) << 16) != 0) {
                            return -1;
                        }
L8ed8: /* shared success exit of the three parity loops */
                        { s32 pg_, nx_;
                        nvx = *(u16 *)&sp1C;
                        pg_ = (s32)D_800814A8[0];
                        nx_ = nvx + 1;
                        nx_ |= 0x8000;
                        pp = (u8 *)(s4o + pg_);
                        *(u16 *)(c + 0x46) = nx_;
                        }
                        if (c != *(u8 **)(pp + 0xAC)) {
                            *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], s1v[0x24], s1v[0x25], &sp1C);
                        }
                        *(void **)(c + 0x60) = *(void **)((s4o + (s32)D_800814A8[0]) + 0xAC);
                        return 4;
                    }
                }
            }
            s2c++;
            par ^= 1;
        } while (s2c < 2);
        goto L8f48;
    }
    goto L900c;

L8f48:
    if (*(s32 *)(c + 0x1C) & 0x20000) {
        if ((func_800A404C() << 16) == 0) {
            u8 *g = D_800814A8[0];
            if (g[0x9A] == 0x11) {
                u8 *h = *(u8 **)(g + 0x60);
                if (h != NULL) {
                    if (!(*(s32 *)(h + 0x14) & 0x2000)) {
                        {
                            s32 ret_;
                            register s32 car_ ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            ret_ = func_800A40AC(c, (u16)func_8009CD58(h, 7, 0));
                            sp20 = ret_;
                            car_ = ret_;
                            if ((car_ << 16) < 0) {
                                goto L900c;
                            }
                            ret_ = car_ | 0x8000;
                            *(u16 *)(c + 0x46) = ret_;
                            *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], D_80082E80[0x24], D_80082E80[0x25], &sp20);
                            return 3;
                        }
                    }
                }
            }
        }
    }
L900c:
    if ((func_800A2C34(c) << 16) == 0) {
        goto L9094;
    }
    return -1;

Lcase4: /* 0x800A9028 */
    if ((func_800A2C34(c) << 16) != 0) {
        return -1;
    }
    tv = func_800A03C4(c, p[0x24], p[0x25]);
    var_fp = 0;
    *(void **)(c + 0x60) = tv;
    if (tv == NULL) {
        goto L9094;
    }
    ASM_KEEP(var_fp);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    {
        s32 r384c_;
        u16 t1e;
        r384c_ = func_800A384C(c, tv, &sp1E, 0);
        sp20 = r384c_;
        if ((r384c_ << 16) < 0) {
            goto L9094;
        }
        t1e = sp1E;
        *(u16 *)(c + 0x46) = r384c_ | 0x8000;
        *(u16 *)(c + 0x2A) = t1e;
        return 1;
    }

L9094:
    if ((func_800A2C34(c) << 16) == 0) {
        goto Lret_fp;
    }
    return -1;

L90b0:
    if ((func_800A2C34(c) << 16) != 0) {
        return -1;
    }
    if (*(s32 *)(c + 0x1C) & 0x10) {
        goto Lret_fp;
    }
    {
        s8 t26 = *(s8 *)(p + 0x26);
        if (t26 >= 0) {
            if (D_800E2970[t26].flags & 2) {
                goto Lret_fp;
            }
        }
    }
    /* 0x800A9110 */
    if ((func_80042900(c, 6) << 16) == 0) {
        s32 r4 = func_800A3544(c, 0x1E);
        sp1C = r4;
        if ((r4 << 16) >= 0) {
            if ((func_800A3518(c) << 16) != 0) {
                nvx = *(u16 *)&sp1C;
                *(void **)(c + 0x60) = c;
                *(u16 *)(c + 0x46) = (nvx + 1) | 0x8000;
                return 4;
            }
        }
    }
    /* 0x800A916C: big state dispatch */
    {
        u32 jt_idx = (u32)(c[0x13] - 9);
        static void *const jt_keep[] = {
            &&Lcase9, &&Lcase10, &&Ldef, &&Ldef, &&Ldef, &&Ldef,
            &&Ldef, &&Ldef, &&Ldef, &&Ldef, &&Ldef, &&Ldef,
            &&Lcase21, &&Lcase22, &&Lcase23, &&Lcase24, &&Lcase25,
            &&Lcase26, &&Lcase27, &&Lcase28, &&Lcase29, &&Ldef, &&Ldef,
            &&Lcase32, &&Ldef, &&Lcase34, &&Lcase35, &&Lcase36,
            &&Lcase37, &&Lcase38, &&Lcase39, &&Lcase40, &&Lcase41,
            &&Lcase42, &&Lcase43, &&Lcase44
        };
        (void)jt_keep;
        if (jt_idx >= 36) {
            goto Ldef;
        }
        goto *D_80089088[jt_idx];
    }

Lcase25: /* 0x800A91A0 */
        func_800ADD20(c, 0x10);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        STEPVEC(o);
        if (o[0x13] != 0) {
            goto Ldef;
        }
        if ((func_800A3518(c) << 16) == 0) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x800A;
        return 6;

Lcase22: /* 0x800A9240 */
        if (c[0x48] != 0xF) {
            goto Ldef;
        }
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Ldef;
        }
        eD = D_80082E80;
        if ((s16)func_8009FD40(eD, p) >= 0xB) {
            goto Ldef;
        }
        if (func_800A365C(p, eD) == 0) {
            goto Ldef;
        }
        if (func_800A36B4(c, D_800E3D7C[0]) == 0) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x8008;
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], eD[0x24], eD[0x25], &sp20);
        return 1;

Lcase44: /* 0x800A92DC */
        func_800ADD20(c, 4);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Ldef;
        }
        eE = D_80082E80;
        tg = func_8009FD40(eE, p);
        if ((u32)((tg - 2) & 0xFFFF) >= 7) {
            goto Ldef;
        }
        if (func_800A365C(p, eE) == 0) {
            goto Ldef;
        }
        {
            s32 d0 = (s16)func_800A0134(c, D_800E3D7C[0]);
            if (d0 < 0) {
                d0 = -d0;
            }
            if (d0 >= 0x21) {
                goto Ldef;
            }
        }
        tn = func_800A05A4(c, p[0x24], p[0x25], *(s16 *)(c + 0x2A), (s16)tg);
        if ((func_800A2CB8(c, tn) << 16) == 0) {
            goto Ldef;
        }
        if (func_800A36B4(c, tn) == 0) {
            goto Ldef;
        }
        if (c[0xAE] != 0) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x8009;
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], eE[0x24], eE[0x25], &sp20);
        return 5;

Lcase43: /* 0x800A93F4 */
        func_800ADD20(c, 0x20);
        {
            u16 f = *(u16 *)(c + 0x98);
            if (!(f & 0x100)) {
                goto Ldef;
            }
            if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
                goto Ldef;
            }
            if (f & 0x8000) {
                goto Ldef;
            }
        }
        *(u16 *)(c + 0x46) = 0x8009;
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], D_80082E80[0x24], D_80082E80[0x25], &sp20);
        return 5;

Lcase34: /* 0x800A9460 */
        func_800ADD20(c, 0x20);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Ldef;
        }
        if ((s8)p[0x26] < 0) {
            goto Ldef;
        }
        s2c = 0;
        do {
            t0 = *(void **)(((u8 *)D_800E3D7C[0] + s2c * 4) + 0xAC);
            if (t0 != NULL) {
                if ((func_800A2CAC(t0) << 16) != 0) {
                    goto Laa2d4;
                }
            }
            s2c++;
        } while (s2c < 2);
        goto Ldef;

Lcase41: /* 0x800A94F0 */
        func_800ADD20(c, 0x10);
        s2c = 0;
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        do {
            tn = *(u8 **)(((u8 *)D_800E3D7C[0] + s2c * 4) + 0xAC);
            if (tn != NULL) {
                s32 d0 = (s16)func_800A0134(c, tn);
                if (d0 < 0) {
                    d0 = -d0;
                }
                if (d0 < 0x21) {
                    if ((func_800A41F0(tn) << 16) != 0) {
                        s1v = *(void **)(tn - 0x14);
                        if ((s16)func_8009FD40(s1v, p) == 1) {
                            if (func_800C7F68(tn) == 0) {
                                goto Laa300;
                            }
                        }
                    }
                }
            }
            s2c++;
        } while (s2c < 2);
        goto Ldef;

Lcase40: /* 0x800A95B8 */
        func_800ADD20(c, 0x40);
        {
            u16 f = *(u16 *)(c + 0x98);
            if (f & 0x100) {
                *(u16 *)(c + 0x98) = f | 0x8000;
                goto Ldef;
            }
            *(u16 *)(c + 0x98) = f & 0x7FFF;
            goto Ldef;
        }

Lcase26: /* 0x800A95EC */
        func_800ADD20(c, 2);
        {
            u16 f = *(u16 *)(c + 0x98);
            *(u16 *)(c + 0x98) = f & 0x7FFF;
            if (!(f & 0x100)) {
                goto Ldef;
            }
        }
        STEPVEC(o);
        tn = o;
        if (tn == NULL) {
            goto Ldef;
        }
        if ((func_800A2CB8(c, tn) << 16) == 0) {
            goto Ldef;
        }
        if ((func_80042900(tn, 1) << 16) != 0) {
            goto Ldef;
        }
        *(u16 *)(c + 0x98) |= 0x8000;
        goto Ldef;

Lcase35: /* 0x800A96B0 */
        func_800ADD20(c, 4);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Ldef;
        }
        if (*(s16 *)(c + 0xA6) != 0) {
            goto Ldef;
        }
        if (D_800E296C[0] & 4) {
            goto Ldef;
        }
        goto Laa2ac;

Lcase38: /* 0x800A9710 */
        func_800ADD20(c, 2);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        STEPVEC(o);
        tn = o;
        if (tn == NULL) {
            goto Ldef;
        }
        cv_ = func_800A2CB8(c, tn) << 16;
Lneighbour_check:
        if (cv_ == 0) {
            goto Ldef;
        }
        if ((func_80042900(tn, 4) << 16) != 0) {
            goto Ldef;
        }
        goto Laa2ac;

Lcase39: /* 0x800A97C0 */
        func_800ADD20(c, 0x10);
        {
            u16 f = *(u16 *)(c + 0x98);
            *(u16 *)(c + 0x98) = f & 0x7FFF;
            if (!(f & 0x100)) {
                goto Ldef;
            }
        }
        STEPVEC(o);
        tn = o;
        if (tn == NULL) {
            goto Ldef;
        }
        if ((func_800A2CB8(c, tn) << 16) == 0) {
            goto Ldef;
        }
        if ((func_80042900(tn, 2) << 16) != 0) {
            goto Ldef;
        }
        {
            *(u16 *)(c + 0x46) = 0x8009;
            *(u16 *)(c + 0x98) |= 0x8000;
            return 5;
        }

Lcase32: /* 0x800A988C */
        if (c[0x49] == 0) {
            func_800ADD20(c, 2);
            if (!(*(u16 *)(c + 0x98) & 0x100)) {
                goto Ldef;
            }
            STEPVEC(o);
            if (o != D_800E3D7C[0]) {
                goto Ldef;
            }
            goto Laa2ac;
        }
        if (*(s32 *)(c + 0x1C) & 0x410) {
            goto Ldef;
        }
        func_800AA53C(c);
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            return 2;
        }
        if ((s8)p[0x26] >= 0) {
            func_800A0E6C(p, *(s8 *)(c + 0x9C), c, c + 0x98);
            goto Laa190;
        }
        eF = D_80082E80;
        if ((s16)func_8009FD40(p, eF) != 1) {
            goto Laa190;
        }
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], eF[0x24], eF[0x25], c + 0x98) + 0x800;
        goto Laa190;

Lcase36: /* 0x800A99D0 */
        {
            u16 f = *(u16 *)(c + 0x98);
            *(u16 *)(c + 0x98) = f & 0x7FFF;
        }
        if (c[0x49] != 0) {
            goto Ldef;
        }
        if ((func_800A6E8C(p, 0x12, &sp18, &sp1A) << 16) == 0) {
            goto Ldef;
        }
        r = func_800A0818(p[0x24], p[0x25], sp18, sp1A, c + 0x98);
        {
            s32 xa = *(u16 *)&sp18;
            s32 ya = *(u16 *)&sp1A;
            s32 f2 = *(u16 *)(c + 0x98);
            s32 dx, av, dxs;
            *(u16 *)(c + 0x2A) = r;
            f2 |= 0x8000;
            ASM_KEEP_NV(f2);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            *(u16 *)(c + 0xA8) = xa;
            xa <<= 16;
            xa >>= 16;
            *(u16 *)(c + 0xAA) = ya;
            ya <<= 16;
            ya >>= 16;
            *(u16 *)(c + 0x98) = f2;
            dx = p[0x24];
            dx -= xa;
            ASM_KEEP_NV(dx);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            if (dx < 0) {
                dx = -dx;
            }
            ASM_KEEP_NV(dx);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            sp18 = dx;
            th = dx;
            ASM_KEEP_NV(th);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            dxs = dx << 16;
            tr = p[0x25] - ya;
            av = tr;
            if (tr < 0) {
                ASM_SET(av);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                av = -av;
            }
            sp1A = av;
            dx = dxs < (av << 16);
            if (dx) {
                th = av;
            }
            if ((s16)th == 1) {
                goto Laa2ac;
            }
            goto Laa190;
        }

Lcase37: /* 0x800A9AB0 */
        func_800ADD20(c, 0x20);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x8009;
        *(u16 *)(c + 0x46) = 0x8009;
        return 5;

Lcase24: /* 0x800A9AD8 */
        if ((s16)func_8009FD40(p, D_80082E80) < 2) {
            goto L9b34;
        }
        if (c[0xB5] != 0) {
            goto L9b44;
        }
        func_800ADD20(c, 8);
        if (*(u16 *)(c + 0x98) & 0x100) {
            *(u16 *)(c + 0x46) = 0x800A;
            return 6;
        }
L9b34:
        if (c[0xB5] == 0) {
            goto Ldef;
        }
L9b44:
        o = func_8009B25C(c, p[0x24], p[0x25], *(s16 *)(c + 0x88));
        if (o == NULL) {
            goto Ldef;
        }
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Laa190;
        }
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], D_80082E80[0x24], D_80082E80[0x25], c + 0x98);
        goto Laa190;

Lcase42: /* 0x800A9BA4 */
        func_800ADD20(c, 4);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Ldef;
        }
        {
            u8 *e2 = D_80082E80;
            u16 dist;
            if (func_800A365C(p, e2) == 0) {
                goto Ldef;
            }
            th = func_8009FD40(e2, p);
            ASM_KEEP_NV(th);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if ((u32)((th - 2) & 0xFFFF) >= 7) {
                goto Ldef;
            }
            dist = *(u16 *)(c + 0x88);
            s2c = 0;
            sp1E = ((u32)func_800A0818(p[0x24], p[0x25], e2[0x24], e2[0x25], &sp20) >> 9) & 7;
            sp18 = p[0x24];
            sp1A = p[0x25];
            if ((th << 16) > 0) {
                u16 *cx = D_8006CCD8;
                u16 *cy = D_8006CCE8;
                do {
                    s32 nx, ny;
                    s32 di = *(s16 *)&sp1E;
                    s32 vx = cx[di];
                    s32 vy = cy[di];
                    nx = *(u16 *)&sp18 + vx;
                    ny = *(u16 *)&sp1A + vy;
                    sp18 = nx;
                    sp1A = ny;
                    if ((func_800A45D8((nx << 6) & 0xFFC0, (ny << 6) & 0xFFC0, (s16)(dist + 0x20), nx) << 16) != 0) {
                        t = (s16)th;
                        break;
                    }
                    {
                        s16 nr = func_800BCB04(((sp18 << 6) + 0x20) & 0xFFE0, ((sp1A << 6) + 0x20) & 0xFFE0, (s16)(dist - 0x20));
                        if (nr < (s16)dist) {
                            break;
                        }
                        if (nr - (s16)dist >= 0x21) {
                            break;
                        }
                        s2c++;
                        dist = nr;
                    }
                    t = (s16)th;
                } while (s2c < t);
            }
            if (s2c != (s16)th) {
                goto Ldef;
            }
            goto Ldir_return;
        }

Lcase27: /* 0x800A9D4C */
        func_800ADD20(c, 4);
        s2c = 0;
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        do {
            tn = *(u8 **)(((u8 *)D_800E3D7C[0] + s2c * 4) + 0xAC);
            if (tn != NULL) {
                s32 d0 = (s16)func_800A0134(c, tn);
                if (d0 < 0) {
                    d0 = -d0;
                }
                if (d0 < 0x21) {
                    if ((func_800A41F0(tn) << 16) != 0) {
                        if ((func_80042900(tn, 0xC) << 16) == 0) {
                            s1v = *(void **)(tn - 0x14);
                            if ((s16)func_8009FD40(s1v, p) == 1) {
                                goto Laa30c;
                            }
                        }
                    }
                }
            }
            s2c++;
        } while (s2c < 2);
        goto Ldef;

Lcase9: /* 0x800A9E1C */
Lcase10:
        tn = func_800A02AC(c, p[0x24], p[0x25]);
        if (tn == NULL) {
            goto Ldef;
        }
        if ((u32)(tn[0x13] - 0x33) >= 4) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x8009;
        s1v = *(void **)(tn - 0x14);
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], s1v[0x24], s1v[0x25], &sp20);
        return 5;

Lcase23: /* 0x800A9E60 */
        func_800ADD20(c, 0x10);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        STEPVEC(o);
        tn = o;
        if (tn == NULL) {
            goto Ldef;
        }
        if (!(*(s32 *)(tn + 0x14) & 0x4000)) {
            goto Ldef;
        }
        if (tn == D_800E3D7C[0]) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x8009;
        *(u16 *)(c + 0x46) = 0x8009;
        return 5;

Lcase28: /* 0x800A9F0C */
        if (!(*(s32 *)(c + 0x1C) & 0x20000)) {
            goto Ldef;
        }
        func_800ADD20(c, 0x20);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        {
            s16 *sp20p = &sp20;
            u8 *e3 = D_80082E80;
            u16 dir2;
            dir2 = ((u32)func_800A0818(p[0x24], p[0x25], e3[0x24], e3[0x25], sp20p) >> 9) & 7;
            sp1E = dir2;
            if ((func_8009A350(p[0x24], p[0x25], dir2, sp20p) << 16) == 0) {
                goto Ldef;
            }
            if (sp20 & 0xB712) {
                goto Ldef;
            }
            if ((s16)func_8009FD40(e3, p) != 2) {
                goto Ldef;
            }
        }
Ldir_return:
        {
            s32 rv_;
            s32 cw_;
            s32 d9;
            rv_ = 5;
            d9 = sp1E;
            cw_ = 0x8009;
            *(u16 *)(c + 0x46) = cw_;
            *(u16 *)(c + 0x2A) = d9 << 9;
            return rv_;
        }

Lcase29: /* 0x800A9FD8 */
        func_800ADD20(c, 8);
        if (!(*(u16 *)(c + 0x98) & 0x100)) {
            goto Ldef;
        }
        STEPVEC(o);
        tn = o;
        if (tn == NULL) {
            goto Ldef;
        }
        if (!(*(s32 *)(tn + 0x14) & 0x4000)) {
            goto Ldef;
        }
        {
            cv_ = tn[0x13];
            goto Lneighbour_check;
        }

Lcase21: /* 0x800AA078 */
        if (c[0xA7] == 0) {
            goto Ldef;
        }
        if (c[0xA8] != 0) {
            goto Ldef;
        }
        STEPVEC(o);
        tn = o;
        if (tn == NULL) {
            goto Ldef;
        }
        if (tn != D_800E3D7C[0]) {
            goto Ldef;
        }
        *(u16 *)(c + 0x46) = 0x8009;
        *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], D_80082E80[0x24], D_80082E80[0x25], &sp20);
        return 5;

Ldef: /* 0x800AA13C: shared "wander" tail */
    tv = func_800A3D18(p, c, 2);
    *(void **)(c + 0x60) = tv;
    if (tv != NULL) {
        r = func_800A384C(c, tv, &sp1E, 1);
        sp20 = r;
        *(u16 *)(c + 0x2A) = *(u16 *)&sp1E;
        if ((r << 16) < 0) {
            goto Laa190;
        }
        rj = r | 0x8000;
Lstore1:
        *(u16 *)(c + 0x46) = rj;
        return 1;
    }
    goto Laa1a0;

Laa190:
    *(u16 *)(c + 0x46) = 0x800B;
    return 2;

Laa1a0:
    {
        u8 kind = c[0x13];
        if (kind != 0x1E) {
            goto Laa2bc;
        }
        if (*(s32 *)(c + 0x14) & 0x20000000) {
            goto Laa2bc;
        }
        {
            u16 d3 = (*(u16 *)(c + 0x2A) >> 9) & 7;
            sp1E = d3;
            sp18 = p[0x24] + *(u16 *)((d3 * 2) + (u8 *)D_8006CCD8);
            sp1A = p[0x25] + *(u16 *)((d3 * 2) + (u8 *)D_8006CCE8);
        }
        tn = NULL;
        if (c[0xAC] == 0) {
            tn = func_8009B25C(c, *(u16 *)&sp18, *(u16 *)&sp1A, *(s16 *)(c + 0x88));
            if (tn != NULL) {
                u8 k = tn[0x13];
                if ((u32)(k - 1) >= 0x2D || k == kind) {
                    tn = NULL;
                }
            }
        }
        if (c[0xAC] < 2) {
            if (tn == NULL) {
                tn = (u8 *)((s16)func_800A70E4(sp18, sp1A, *(s16 *)(c + 0x88)) + 1);
            } else {
                goto Laa2ac;
            }
        }
        if (tn == NULL) {
            goto Laa2bc;
        }
    }
Laa2ac:
    *(u16 *)(c + 0x46) = 0x8009;
    return 5;

Laa2bc:
    if ((s8)p[0x26] < 0) {
        goto Lret_fp;
    }
    return 2;

Laa2d4:
    *(u16 *)(c + 0x46) = 0x8009;
    *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], D_80082E80[0x24], D_80082E80[0x25], &sp20);
    return 5;

Laa300:
    *(u16 *)(c + 0x46) = 0x8009;
    *(void **)(c + 0xA8) = tn;
    *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], s1v[0x24], s1v[0x25], &sp20);
    return 5;

Laa30c:
    *(u16 *)(c + 0x46) = 0x8009;
    *(u16 *)(c + 0x2A) = func_800A0818(p[0x24], p[0x25], s1v[0x24], s1v[0x25], &sp20);
    return 5;

Lret_fp:
    tr = var_fp << 16;
    ASM_KEEP(tr);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    return (u32)tr >> 16;
}
