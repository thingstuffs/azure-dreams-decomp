/*
 * laneF v01: fresh forward derivation of func_8002263C (func_8095563C).
 * Divergence from the optimised lineage: each diagonal arm's band value is a
 * single variable `d` assigned once per condition (retail: t0 in all 8 sites),
 * instead of per-condition one-shot temps. Everything else follows the retail
 * stream shape re-derived from work/town_100_20260812/fable_r5_8095563c/retail.dis.
 */
#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 link;
    s16 kind;
} Zone;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Box;

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
    s32 dx;
    s32 dy;
} Actor;

extern Zone D_80024020[];
extern Box D_800240E0[];
extern void *D_80020180[];

#define Z(F) (D_80024020[*pi].F)
#define ZKM(F) (D_80024020[km].F)
#define ZI(F) (D_80024020[idx].F)

#define PUSH(DA3, DA2)               \
    adx = p->dx;                     \
    ady = p->dy;                     \
    if (adx < 0) {                   \
        adx = -adx;                  \
    }                                \
    if (ady < 0) {                   \
        ady = -ady;                  \
    }                                \
    if (ady < adx) {                 \
        *oy += (DA3);                \
    } else {                         \
        *ox += (DA2);                \
    }                                \
    goto bump3;

s32 func_8002263C(Actor *p, s16 *pi, s32 *ox, s32 *oy) {
    register Box *q ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 i ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 idx;
    s32 k;
    register s32 km ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 adx;
    s32 ady;
    s32 d0;
    s32 px;
    s32 py;
    s32 ex;
    s32 ey;
    s32 ew;
    s32 d1;
    s32 d2;
    s32 nx;
    s32 kk;
    s32 hpx;
    s32 hex;
    s32 hew;
    s32 hd;
    static void *const keepalive[] = {&&Lc2, &&Lc3, &&Lc4, &&Lc5, &&Lr0};

    (void)keepalive;
    idx = 0;
    i = *pi + 1;
    while (i >= *pi - 1) {
        idx = (i + 16) % 16;
        if (p->x < ZI(x)) {
            goto next1;
        }
        if (p->y < ZI(y)) {
            goto next1;
        }
        if (ZI(x) + ZI(w) < p->x) {
            goto next1;
        }
        if (ZI(y) + ZI(h) < p->y) {
            goto next1;
        }
        goto found;
    next1:
        i--;
    }
check:
    if (idx >= 0) {
        goto miss;
    }

    k = Z(link);
    if (k < 0) {
        goto dispatch;
    }
    if (p->z < -32) {
        goto dispatch;
    }
    {
        register s32 k8 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        u8 *bb;
        Box *qq;
        bb = (u8 *)D_800240E0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        k8 = k << 3;
        qq = (Box *)(bb + k8);
        ASM_KEEP_NV(qq);   /* MATCH pin: load-bearing for the whole function shape */
        q = qq;
    }
    ASM_KEEP(q);   /* MATCH pin: load-bearing for the whole function shape */
    {
        s32 pxe;
        s32 exe;
        s32 pye;
        s32 eye;
        pxe = p->x;
        exe = q->x;
        if (pxe < exe) {
            goto dispatch;
        }
        pye = p->y;
        eye = q->y;
        if (pye < eye) {
            goto dispatch;
        }
        if (exe + q->w < pxe) {
            goto dispatch;
        }
        if (eye + q->h < pye) {
            goto dispatch;
        }
    }
    if (Z(kind) != 0) {
        goto horiz;
    }

    *oy -= p->dy;
    d0 = p->dy;
    if (d0 > 0) {
        p->y = q->y;
        goto ret2;
    }
    if (d0 < 0) {
        p->y = q->y + q->h;
        goto ret2;
    }
    {
        s32 vpy;
        s32 vey;
        s32 veh;
        s32 vd;
        vpy = p->y;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        vey = q->y;
        veh = q->h;
        vd = vpy - vey;
        if (vd < 0) {
            vd = -vd;
        }
        vey = vey + veh;
        vey = vey - vpy;
        if (vey < 0) {
            vey = -vey;
        }
        vd = vd < vey;
        vey = (u16)q->y;
        veh = (u16)q->h;
        if (vd) {
            p->y = vey;
            goto ret2;
        }
        vey = vey + veh;
        p->y = vey;
    }
    goto ret2;

horiz:
    *ox -= p->dx;
    d0 = p->dx;
    if (d0 > 0) {
        hex = (u16)q->x;
        p->x = hex;
        goto ret2;
    }
    if (d0 < 0) {
        hex = (u16)q->x;
        hd = (u16)q->w;
        hex = hex + hd;
        goto storex;
    }
    hpx = p->x;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    hex = q->x;
    hew = q->w;
    hd = hpx - hex;
    if (hd < 0) {
        hd = -hd;
    }
    hex = hex + hew;
    hex = hex - hpx;
    if (hex < 0) {
        hex = -hex;
    }
    hd = hd < hex;
    hex = (u16)q->x;
    hew = (u16)q->w;
    if (hd) {
        goto storex;
    }
    hex = hex + hew;
storex:
    ASM_KEEP(hex);   /* MATCH pin: retail delay-slot fill depends on it */
    p->x = hex;
    goto ret2;

dispatch:
    kk = Z(kind);
    if ((u32)kk >= 6) {
        goto bump3;
    }
    goto *D_80020180[kk];
found:
        *pi = idx;
        idx = -1;
        goto check;

Lc2:
    {
        register s32 d12 ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
        register s32 zy2 ASM_REG("$11");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 zh2 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 s2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 zx2;
        s32 py2;
        s32 px2;
        s32 t2v;
        s32 nxa;
        py2 = p->y;
        zy2 = Z(y);
        zx2 = Z(x);
        px2 = p->x;
        t2v = zy2 + 0x100;
        d12 = zx2 + t2v;
        nxa = -px2;
        s2 = nxa + d12;
        s2 = py2 - s2;
        t2v = zy2 - 0x70;
        if (s2 < 0) {
            PUSH(0x80000, 0x80000)
        }
        s2 = Z(w);
        zh2 = Z(h);
        s2 = zx2 + s2;
        s2 = s2 + t2v;
        d12 = s2 + zh2;
        s2 = nxa + d12;
        s2 = py2 - s2;
        if (s2 > 0) {
            PUSH(-0x100000, -0x100000)
        }
    }
        return 0;

Lc3:
    {
        register s32 s3 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 d13 ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
        register s32 pi3 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 zx3 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 zy3;
        s32 py3;
        s32 px3;
        u8 *zb3;
        zb3 = (u8 *)D_80024020;
        pi3 = *pi;
        ASM_KEEP(pi3);   /* MATCH pin: retail register colouring depends on it */
        px3 = p->x;
        py3 = p->y;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        zx3 = ((Zone *)zb3)[pi3].x;
        s3 = ((Zone *)zb3)[pi3].w;
        zy3 = ((Zone *)zb3)[pi3].y;
        s3 = zx3 + s3;
        s3 = s3 - 0x100;
        d13 = zy3 - s3;
        s3 = px3 + d13;
        s3 = py3 - s3;
        zx3 = zx3 + 0x70;
        if (s3 < 0) {
            PUSH(0x80000, -0x80000)
        }
        s3 = ((Zone *)zb3)[pi3].h;
        s3 = zy3 + s3;
        d13 = s3 - zx3;
        s3 = px3 + d13;
        s3 = py3 - s3;
        if (s3 > 0) {
            PUSH(-0x100000, 0x100000)
        }
    }
        return 0;

Lc4:
    {
        register s32 s4 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 d14 ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
        register s32 pi4 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 zy4 ASM_REG("$11");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 zx4 ASM_REG("$10");   /* MATCH pin: retail register colouring depends on it */
        register s32 t4v ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 py4;
        s32 px4;
        u8 *zb4;
        zb4 = (u8 *)D_80024020;
        pi4 = *pi;
        ASM_KEEP(pi4);   /* MATCH pin: retail register colouring depends on it */
        px4 = p->x;
        py4 = p->y;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        zy4 = ((Zone *)zb4)[pi4].y;
        s4 = ((Zone *)zb4)[pi4].h;
        zx4 = ((Zone *)zb4)[pi4].x;
        s4 = zy4 + s4;
        t4v = zx4 + 0x100;
        d14 = s4 - t4v;
        s4 = px4 + d14;
        s4 = py4 - s4;
        t4v = zy4 + 0x70;
        if (s4 > 0) {
            PUSH(-0x100000, 0x100000)
        }
        s4 = ((Zone *)zb4)[pi4].w;
        s4 = zx4 + s4;
        d14 = t4v - s4;
        s4 = px4 + d14;
        s4 = py4 - s4;
        if (s4 < 0) {
            PUSH(0x200000, -0x200000)
        }
    }
        return 0;

Lc5:
    {
        register s32 s5 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        register s32 d15 ASM_REG("$8");   /* MATCH pin: retail delay-slot fill depends on it */
        register s32 zw5 ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
        s32 zy5;
        s32 zx5;
        s32 nx5;
        s32 py5;
        s32 t5v;
        zy5 = Z(y);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        zw5 = Z(w);
        zx5 = Z(x);
        s5 = zy5 + zw5;
        t5v = zx5 - 0x100;
        s5 = s5 + t5v;
        d15 = s5 + zw5;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        nx5 = p->x;
        py5 = p->y;
        nx5 = -nx5;
        s5 = nx5 + d15;
        s5 = py5 - s5;
        if (s5 > 0) {
            PUSH(-0x100000, -0x100000)
        }
        s5 = zy5 + zx5;
        d15 = s5 + 0x70;
        s5 = nx5 + d15;
        s5 = py5 - s5;
        if (s5 < 0) {
            PUSH(0x200000, 0x200000)
        }
    }
        return 0;

Lr0:
    return 0;
bump3:
    *ox -= p->dx * 3;
    *oy -= p->dy * 3;
    return 1;

miss:
    km = *pi;
    if (ZKM(kind) != 1) {
        s32 pxm = p->x;
        s32 exm = ZKM(x);
        if (pxm < exm) {
            p->x = ZKM(x) + 8;
        } else if (exm + ZKM(w) < pxm) {
            p->x = ZKM(x) + ZKM(w) - 8;
        }
        *ox -= p->dx * 3;
    }
    if (ZKM(kind) != 0) {
        s32 pym = p->y;
        s32 eym = ZKM(y);
        if (pym < eym) {
            p->y = ZKM(y) + 8;
        } else if (eym + ZKM(h) < pym) {
            p->y = ZKM(y) + ZKM(h) - 8;
        }
        *oy -= p->dy * 3;
    }
    {
        register s32 g3 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        s32 piT;
        ASM_UNDEF(g3);   /* MATCH pin: retail delay-slot fill depends on it */
        piT = *pi;
        ASM_USE(g3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        i = piT + 1;
    }
    while (i >= *pi - 1) {
        idx = (i + 16) % 16;
        if (p->x < ZI(x)) {
            goto next2;
        }
        if (p->y < ZI(y)) {
            goto next2;
        }
        if (ZI(x) + ZI(w) < p->x) {
            goto next2;
        }
        if (ZI(y) + ZI(h) < p->y) {
            goto next2;
        }
        *pi = idx;
    next2:
        i--;
    }
ret2:
    return 2;
}
