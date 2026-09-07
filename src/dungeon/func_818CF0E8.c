#include "common.h"

typedef struct S_818CF0E8_0_pre {
    u16 unk_00;
} S_818CF0E8_0_pre;   /* the 0x2 bytes before arg0 in func_818CF0E8, addressed as arg0[-1] */

typedef struct S_818CF0E8_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    union { u16 s; s16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x2];
    s16 unk_08;
    u8 pad_0A[0xB];
    u8 unk_15;
    s16 unk_16;
    u8 pad_18[0x14];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u8 pad_40[0xC];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_818CF0E8_0;   /* arg0 in func_818CF0E8 */

typedef struct S_818CF0E8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_818CF0E8_1;   /* arg1 in func_818CF0E8 */

typedef struct S_818CF0E8_2 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_818CF0E8_2;   /* star in func_818CF0E8 */

typedef struct S_818CF0E8_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    s16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_818CF0E8_3;   /* arg2 in func_818CF0E8 */

typedef struct S_818CF0E8_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x50];
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_818CF0E8_4;   /* s3 in func_818CF0E8 */

typedef struct S_818CF0E8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_818CF0E8_5;   /* obj in func_818CF0E8 */

typedef struct S_818CF0E8_6 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    union { struct { void * v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    union { u16 s; volatile u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818CF0E8_6;   /* p in func_818CF0E8 */

typedef struct S_818CF0E8_7 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_818CF0E8_7;   /* env in func_818CF0E8 */

typedef struct S_818CF0E8_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818CF0E8_8_pre;   /* the 0x18 bytes before ((S_818CF0E8_0 *)arg0)->unk_30 in func_818CF0E8, addressed as ((S_818CF0E8_0 *)arg0)->unk_30[-1] */

typedef struct S_818CF0E8_9 {
    u8 pad_00[0x86];
    s16 unk_86;
} S_818CF0E8_9;   /* ((S_818CF0E8_0 *)arg0)->unk_34 in func_818CF0E8 */



typedef struct {
    u16 h[6];
} Vec12;

typedef struct {
    s32 w;
} __attribute__((packed)) UW;

extern s32 func_80069EF8();
extern void func_80024358();
extern s32 func_800A4778();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern s32 func_8009D218();
extern s32 func_800A6D30();
extern void func_800A56E0();
extern void func_800542BC();
extern void func_800C8CD8();

extern void func_80024A58(void) __attribute__((noreturn));
extern void func_80024ACC(void) __attribute__((noreturn));
extern void func_80024B48(void) __attribute__((noreturn));
extern void func_80024B6C(void) __attribute__((noreturn));
extern void func_80024BA4(void) __attribute__((noreturn));
extern void func_80024C30(void) __attribute__((noreturn));
extern void func_80024C54(void) __attribute__((noreturn));
extern void func_80024C8C(void) __attribute__((noreturn));
extern void func_80024CCC(void) __attribute__((noreturn));
extern void func_80024D40(void) __attribute__((noreturn));
extern void func_80024DA0(void) __attribute__((noreturn));
extern void func_80025344(void) __attribute__((noreturn));

extern s16 D_80025924[5];
extern u8 D_80024478[];
extern u8 D_80024578[];
extern u8 D_800245C8[];
extern u8 D_80045340[];
extern Vec12 D_8002590C;
extern Vec12 D_80025918;
extern u8 D_800DE870[];
extern u8 D_800DEC00[];
extern s32 D_800814A0[3];
extern u8 D_800E3D68[];

void func_818CF0E8(void *arg0, S_818CF0E8_1 *arg1, S_818CF0E8_3 *arg2)
{
    u8 *star;
    S_818CF0E8_7 *env;
    void *obj;
    void *p;
    s32 dv;
    s32 av;
    u16 flags;
    s16 cnt;
    s32 r;
    s32 b;

    D_80025924[0] = 1;
    env = ((S_818CF0E8_0 *)arg0)->unk_2C;
    if (((S_818CF0E8_0 *)arg0)->unk_00.s == 0) {
        p = (void *)0;
        do {
            register void *a0v ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 a2v ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
            register s32 a3v ASM_REG("$7");   /* MATCH pin: load-bearing for the whole function shape */
            s32 rv;
            p = (u8 *)p + 1;
            rv = func_80069EF8();
            a0v = (u8 *)arg0 - 0x20;
            a2v = 0xC0C0C0;
            a3v = (rv & 0xFF) | 0x80;
            ASM_USE2(a2v, a3v);   /* MATCH pin: retail schedule: same instructions, different order without it */
            func_80024358(a0v, ((S_818CF0E8_0 *)arg0)->unk_16, a2v, a3v, 0, 0, 0);
        } while ((s32)p < 4);
        if ((func_800A4778(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                           arg1->unk_08.at02.v, ((S_818CF0E8_0 *)arg0)->unk_30) << 0x10) != 0) {
            goto finish;
        }
        if (((S_818CF0E8_0 *)arg0)->unk_08 != 0) {
            star = ((S_818CF0E8_8_pre *)(((S_818CF0E8_0 *)arg0)->unk_30))[-1].unk_00;
            if (arg1->unk_08.at00.v < ((S_818CF0E8_2 *)star)->unk_08.at00.v + (s32)0xFF800000) {
                ((S_818CF0E8_0 *)arg0)->unk_54 /= 2;
            }
            {
            s32 d;
            register s32 aw ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            d = arg1->unk_00.at02u.v;
            d -= ((S_818CF0E8_2 *)star)->unk_02.s;
            aw = d;
            if (d < 0) {
                aw = 0 - aw;
            }
            if (aw < 8) {
                s32 v;
                register s32 a ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 lim ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                lim = 0x40000;
                v = ((S_818CF0E8_0 *)arg0)->unk_4C;
                a = v;
                if (v < 0) {
                    a = 0 - a;
                }
                if (a > lim) {
                    s32 t;
                    t = v / 2;
                    ASM_TAILSLOT_PIN(t);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80024A58();
                    return;
                }
            } else if (((S_818CF0E8_0 *)arg0)->unk_4C == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                ((S_818CF0E8_0 *)arg0)->unk_4C = nv;
            }
            }
            {
            s32 d;
            s32 aw;
            d = arg1->unk_04.at02u.v;
            d -= ((S_818CF0E8_2 *)star)->unk_06.s;
            aw = (d >= 0) ? d : (0 - d);
            if (aw < 8) {
                s32 v;
                register s32 a ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                register s32 lim ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                lim = 0x40000;
                v = ((S_818CF0E8_0 *)arg0)->unk_50;
                a = v;
                if (v < 0) {
                    a = 0 - a;
                }
                if (a > lim) {
                    s32 t;
                    t = v / 2;
                    ASM_TAILSLOT_PIN(t);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80024ACC();
                    return;
                }
            } else if (((S_818CF0E8_0 *)arg0)->unk_50 == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                ((S_818CF0E8_0 *)arg0)->unk_50 = nv;
            }
            }
            {
                register u16 a2v ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
                register u16 a1v ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
                s32 aw;
                s32 d;
                s32 st;
                a2v = arg1->unk_00.at02.v;
                ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                d = arg1->unk_00.at02u.v;
                st = ((S_818CF0E8_2 *)star)->unk_02.s;
                a1v = ((S_818CF0E8_2 *)star)->unk_02.u;
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    s32 t;
                    t = arg1->unk_00.at00.v;
                    t += ((S_818CF0E8_0 *)arg0)->unk_4C;
                    ASM_TAILSLOT_PIN(t);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80024B48();
                    return;
                }
                if (aw >= 4) {
                    arg1->unk_00.at00.v += (((S_818CF0E8_0 *)arg0)->unk_4C * aw) / 192;
                    func_80024B6C();
                    return;
                }
                if (((S_818CF0E8_0 *)arg0)->unk_38 != ((S_818CF0E8_0 *)arg0)->unk_3C) {
                    s32 one;
                    one = 1;
                    ((S_818CF0E8_0 *)arg0)->unk_00.s = one;
                    ((S_818CF0E8_0 *)arg0)->unk_02.s = 0;
                    ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                    if (((S_818CF0E8_0 *)arg0)->unk_38 != ((S_818CF0E8_0 *)arg0)->unk_3C) {
                        s32 v = ((S_818CF0E8_0 *)arg0)->unk_4C;
                        if (v > 0) {
                            register s32 t1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                            register s32 t0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                            t1 = a1v << 0x10;
                            ASM_USE(t1);   /* MATCH pin: retail delay-slot contents depend on it */
                            t0 = a2v << 0x10;
                            ASM_TAILSLOT_PIN(t0);   /* MATCH pin: retail delay-slot fill depends on it */
                            func_80024BA4();
                            return;
                        }
                        if (v < 0) {
                            if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                                ((S_818CF0E8_0 *)arg0)->unk_00.s = 1;
                                ((S_818CF0E8_0 *)arg0)->unk_02.s = 0;
                            }
                        }
                    }
                }
                ASM_USE2(a2v, a1v);   /* MATCH pin: load-bearing for the whole function shape */
            }
            {
                register u16 a2v ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
                register u16 a1v ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
                s32 aw;
                s32 d;
                s32 st;
                a2v = arg1->unk_04.at02.v;
                ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                d = arg1->unk_04.at02u.v;
                st = ((S_818CF0E8_2 *)star)->unk_06.s;
                a1v = ((S_818CF0E8_2 *)star)->unk_06.u;
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    s32 t;
                    t = arg1->unk_04.at00.v;
                    t += ((S_818CF0E8_0 *)arg0)->unk_50;
                    ASM_TAILSLOT_PIN(t);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80024C30();
                    return;
                }
                if (aw >= 4) {
                    arg1->unk_04.at00.v += (((S_818CF0E8_0 *)arg0)->unk_50 * aw) / 192;
                    func_80024C54();
                    return;
                }
                if (((S_818CF0E8_0 *)arg0)->unk_3A != ((S_818CF0E8_0 *)arg0)->unk_3E) {
                    s32 one;
                    one = 1;
                    ((S_818CF0E8_0 *)arg0)->unk_00.s = one;
                    ((S_818CF0E8_0 *)arg0)->unk_02.s = 0;
                    ASM_MEM_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                    if (((S_818CF0E8_0 *)arg0)->unk_3A != ((S_818CF0E8_0 *)arg0)->unk_3E) {
                        s32 v = ((S_818CF0E8_0 *)arg0)->unk_50;
                        if (v > 0) {
                            register s32 t1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
                            register s32 t0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                            t1 = a1v << 0x10;
                            ASM_USE(t1);   /* MATCH pin: retail delay-slot contents depend on it */
                            t0 = a2v << 0x10;
                            ASM_TAILSLOT_PIN(t0);   /* MATCH pin: retail delay-slot fill depends on it */
                            func_80024C8C();
                            return;
                        }
                        if (v < 0) {
                            if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                                ((S_818CF0E8_0 *)arg0)->unk_00.s = 1;
                                ((S_818CF0E8_0 *)arg0)->unk_02.s = 0;
                            }
                        }
                    }
                }
                ASM_USE2(a2v, a1v);   /* MATCH pin: load-bearing for the whole function shape */
            }
            if (((S_818CF0E8_0 *)arg0)->unk_4C != 0) {
                register u16 a2v ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
                register u16 a1v ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
                register s32 t ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                a2v = arg1->unk_00.at02.v;
                a1v = ((S_818CF0E8_2 *)star)->unk_02.u;
                ASM_USE(a1v);   /* MATCH pin: retail delay-slot fill depends on it */
                t = a2v << 0x10;
                ASM_TAILSLOT_PIN(t);   /* MATCH pin: retail delay-slot fill depends on it */
                func_80024CCC();
                return;
            }
            {
                register u16 a2v ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
                register u16 a1v ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
                s32 aw;
                register s32 d ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
                s32 st;
                a2v = arg1->unk_04.at02.v;
                a1v = ((S_818CF0E8_2 *)star)->unk_06.u;
                d = (s16)a2v;
                st = (s16)a1v;
                d -= st;
                aw = d;
                if (d < 0) {
                    aw = 0 - aw;
                }
                if (aw >= 0xC1) {
                    s32 t;
                    ASM_USE2(a2v, a1v);   /* MATCH pin: load-bearing for the whole function shape */
                    t = arg1->unk_08.at00.v;
                    t += ((S_818CF0E8_0 *)arg0)->unk_54;
                    ASM_TAILSLOT_PIN(t);   /* MATCH pin: retail delay-slot fill depends on it */
                    func_80024D40();
                    return;
                }
                if (aw >= 4) {
                    arg1->unk_08.at00.v += (((S_818CF0E8_0 *)arg0)->unk_54 * aw) / 192;
                    func_80024DA0();
                    return;
                }
            }
        } else {
            ((S_818CF0E8_0 *)arg0)->unk_04.s -= 1;
            arg1->unk_00.at00.v += ((S_818CF0E8_0 *)arg0)->unk_4C;
            arg1->unk_04.at00.v += ((S_818CF0E8_0 *)arg0)->unk_50;
            arg1->unk_08.at00.v += ((S_818CF0E8_0 *)arg0)->unk_54;
            if (((S_818CF0E8_0 *)arg0)->unk_04.u <= 0) {
                goto finish;
            }
        }
    }
    if (((S_818CF0E8_0 *)arg0)->unk_00.s == 1) {
        if (((S_818CF0E8_0 *)arg0)->unk_02.s == 0) {
            func_800A56E0(0x300);
            func_800542BC();
        }
        cnt = ((S_818CF0E8_0 *)arg0)->unk_02.u + 1;
        ((S_818CF0E8_0 *)arg0)->unk_02.s = cnt;
        if (cnt >= 0xF) {
            ((S_818CF0E8_0 *)arg0)->unk_02.s = 0;
            ((S_818CF0E8_0 *)arg0)->unk_00.u += 1;
        }
    }
    if (((S_818CF0E8_0 *)arg0)->unk_00.s == 2) {
        ((S_818CF0E8_0 *)arg0)->unk_02.u += 1;
        arg2->unk_1C -= 0x32;
        arg2->unk_1E -= 0x32;
        obj = func_8003FC64(0x212);
        {
            u8 *s3;
            s3 = (u8 *)obj + 0x20;
            if (obj != 0) {
            ((S_818CF0E8_4 *)s3)->unk_02 = 0x34;
            ((S_818CF0E8_5 *)obj)->unk_10 = D_800245C8;
            func_8004491C(obj, D_80045340);
            p = ((S_818CF0E8_5 *)obj)->unk_0C;
            flags = ((S_818CF0E8_6 *)p)->unk_14.s | 0xC;
            ((S_818CF0E8_6 *)p)->unk_10 = 0x60;
            ((S_818CF0E8_6 *)p)->unk_14.s = flags;
            ASM_SET(flags);
            ((S_818CF0E8_6 *)p)->unk_14.u = flags | 2;
            p = ((S_818CF0E8_5 *)obj)->unk_08;
            {
                s32 r2;
                s32 b2;
                r2 = func_80069EF8() & 0x1F;
                b2 = arg1->unk_00.at02.v - 0x10;
                b2 += r2;
                ((S_818CF0E8_6 *)p)->unk_02.s = b2;
            }
            {
                s32 r2;
                s32 b2;
                r2 = func_80069EF8() & 0x1F;
                b2 = arg1->unk_04.at02.v - 0x10;
                b2 += r2;
                ((S_818CF0E8_6 *)p)->unk_06.s = b2;
            }
            ((S_818CF0E8_6 *)p)->unk_08.at02.v = arg1->unk_08.at02u.v;
            ((S_818CF0E8_4 *)s3)->unk_54 = func_80069EF8() + 0x30000;
            ((S_818CF0E8_4 *)s3)->unk_60 = 0x6000;
            p = ((S_818CF0E8_5 *)obj)->unk_0C;
            ((S_818CF0E8_6 *)p)->unk_1C = 0x800;
            ((S_818CF0E8_6 *)p)->unk_1E = 0x800;
            ((S_818CF0E8_6 *)p)->unk_0E = 0x80;
            ((S_818CF0E8_6 *)p)->unk_0D = 0x80;
            ((S_818CF0E8_6 *)p)->unk_0C = 0x80;
            flags = ((S_818CF0E8_6 *)p)->unk_14.u | 0x100;
            ((S_818CF0E8_6 *)p)->unk_12 = 0x7DCF;
            ((S_818CF0E8_6 *)p)->unk_14.s = flags;
            func_8003DB94(p, D_800DE870, 0);
            }
        }
        if ((((S_818CF0E8_0 *)arg0)->unk_02.u & 3) == 1) {
            obj = func_8003FC64(0x212);
            {
            register u8 *s3 ASM_REG("$19");
            s3 = (u8 *)obj + 0x20;
            if (obj != 0) {
                ((S_818CF0E8_4 *)s3)->unk_02 = 0x14;
                ((S_818CF0E8_5 *)obj)->unk_10 = D_80024478;
                func_8004491C(obj, D_80045340);
                p = ((S_818CF0E8_5 *)obj)->unk_0C;
                flags = ((S_818CF0E8_6 *)p)->unk_14.s | 0xC;
                ((S_818CF0E8_6 *)p)->unk_10 = 0;
                ((S_818CF0E8_6 *)p)->unk_14.s = flags;
                p = ((S_818CF0E8_5 *)obj)->unk_08;
                star = ((S_818CF0E8_8_pre *)(((S_818CF0E8_0 *)arg0)->unk_30))[-1].unk_00;
                {
                    s32 r2;
                    s32 b2;
                    r2 = func_80069EF8() & 0x1F;
                    b2 = ((S_818CF0E8_2 *)star)->unk_02.u - 0x10;
                    b2 += r2;
                ((S_818CF0E8_6 *)p)->unk_02.s = b2;
                }
                {
                    s32 r2;
                    s32 b2;
                    r2 = func_80069EF8() & 0x1F;
                    b2 = ((S_818CF0E8_2 *)star)->unk_06.u - 0x10;
                    b2 += r2;
                ((S_818CF0E8_6 *)p)->unk_06.s = b2;
                }
                {
                    s32 r2;
                    s32 b2;
                    r2 = (func_80069EF8() & 0x3F) + 0x20;
                    b2 = ((S_818CF0E8_2 *)star)->unk_08.at02.v;
                    b2 -= r2;
                    ((S_818CF0E8_6 *)p)->unk_08.at02u.v = b2;
                }
                p = ((S_818CF0E8_5 *)obj)->unk_0C;
                ((S_818CF0E8_6 *)p)->unk_1C = 0x800;
                ((S_818CF0E8_6 *)p)->unk_1E = 0x800;
                ((S_818CF0E8_4 *)s3)->unk_54 = func_80069EF8() + (s32)0xFFFE0000;
                ((S_818CF0E8_6 *)p)->unk_0E = 0x80;
                ((S_818CF0E8_6 *)p)->unk_0D = 0x80;
                ((S_818CF0E8_6 *)p)->unk_0C = 0x80;
                flags = ((S_818CF0E8_6 *)p)->unk_14.u | 0x100;
                ((S_818CF0E8_6 *)p)->unk_12 = 0x7DC0;
                ((S_818CF0E8_6 *)p)->unk_14.s = flags;
                func_8003DB94(p, D_800DEC00, 0);
            }
            }
        }
        if (((S_818CF0E8_0 *)arg0)->unk_02.s >= 0x29) {
            ((S_818CF0E8_0 *)arg0)->unk_02.s = 0;
            ((S_818CF0E8_0 *)arg0)->unk_00.u += 1;
            if (func_8009D218(env->unk_60, 2, env) == 0) {
                s32 a2v;
                s32 a1v;
                s32 rr;
                rr = (func_800A6D30() & 3) + 2;
                a2v = (((S_818CF0E8_0 *)arg0)->unk_15 >> 2) + rr;
                a1v = 0x10;
                if (D_800E3D68[0] == 0xFF) {
                    a1v = 0xFF;
                }
                func_800C8CD8(((S_818CF0E8_0 *)arg0)->unk_30, a1v, a2v);
            }
        }
    }
    if (((S_818CF0E8_0 *)arg0)->unk_00.s == 3) {
        ((S_818CF0E8_0 *)arg0)->unk_02.u += 1;
        arg2->unk_1C -= 0x32;
        arg2->unk_1E -= 0x32;
        if (((S_818CF0E8_0 *)arg0)->unk_02.s >= 0x15) {
finish:
            ((S_818CF0E8_9 *)(((S_818CF0E8_0 *)arg0)->unk_34))->unk_86 = 1;
            ((S_818CF0E8_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
            func_80025344();
            return;
        }
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        ((S_818CF0E8_5 *)obj)->unk_22 = 1;
        ((S_818CF0E8_5 *)obj)->unk_10 = D_80024578;
        func_8004491C(obj, D_80045340);
        p = ((S_818CF0E8_5 *)obj)->unk_0C;
        flags = ((S_818CF0E8_6 *)p)->unk_14.s | 0xC;
        ((S_818CF0E8_6 *)p)->unk_10 = 0x60;
        ((S_818CF0E8_6 *)p)->unk_14.s = flags;
        p = ((S_818CF0E8_5 *)obj)->unk_08;
        ((S_818CF0E8_6 *)p)->unk_02.u = arg1->unk_00.at02.v;
        ((S_818CF0E8_6 *)p)->unk_06.u = arg1->unk_04.at02.v;
        ((S_818CF0E8_6 *)p)->unk_08.at02.v = arg1->unk_08.at02u.v;
        p = ((S_818CF0E8_5 *)obj)->unk_0C;
        ((S_818CF0E8_6 *)p)->unk_1E = 0x1000;
        ((S_818CF0E8_6 *)p)->unk_1C = 0x1000;
        ((S_818CF0E8_6 *)p)->unk_06.s = -1;
        ((S_818CF0E8_6 *)p)->unk_0C = arg2->unk_0C;
        ((S_818CF0E8_6 *)p)->unk_0D = arg2->unk_0D;
        ((S_818CF0E8_6 *)p)->unk_0E = arg2->unk_0E;
        ((S_818CF0E8_6 *)p)->unk_1A = func_80069EF8() & 0xFFF;
        ASM_SCHED_BARRIER();
        {
            register u8 *src ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
            register s32 w0 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 w1 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 w2 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
            register s32 hi ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            hi = (s32)0x80020000;
            ASM_KEEP(hi);
            src = (u8 *)(hi + 0x590C);
            w0 = ((UW *)(src + 0))->w;
            w1 = ((UW *)(src + 4))->w;
            w2 = ((UW *)(src + 8))->w;
            ((UW *)((u8 *)obj + 0x40))->w = w0;
            ((UW *)((u8 *)obj + 0x44))->w = w1;
            ((UW *)((u8 *)obj + 0x48))->w = w2;
        }
        ASM_SCHED_BARRIER();
        ((S_818CF0E8_6 *)p)->unk_08.at00.v = (u8 *)obj + 0x40;
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        ((S_818CF0E8_5 *)obj)->unk_22 = 1;
        ((S_818CF0E8_5 *)obj)->unk_10 = D_80024578;
        func_8004491C(obj, D_80045340);
        p = ((S_818CF0E8_5 *)obj)->unk_0C;
        flags = ((S_818CF0E8_6 *)p)->unk_14.s | 0xC;
        ((S_818CF0E8_6 *)p)->unk_10 = 0x60;
        ((S_818CF0E8_6 *)p)->unk_14.s = flags;
        p = ((S_818CF0E8_5 *)obj)->unk_08;
        ((S_818CF0E8_6 *)p)->unk_02.u = arg1->unk_00.at02.v;
        ((S_818CF0E8_6 *)p)->unk_06.u = arg1->unk_04.at02.v;
        ((S_818CF0E8_6 *)p)->unk_08.at02.v = arg1->unk_08.at02u.v;
        p = ((S_818CF0E8_5 *)obj)->unk_0C;
        ((S_818CF0E8_6 *)p)->unk_1E = 0x1000;
        ((S_818CF0E8_6 *)p)->unk_1C = 0x1000;
        ((S_818CF0E8_6 *)p)->unk_06.s = -2;
        ((S_818CF0E8_6 *)p)->unk_0C = arg2->unk_0C;
        ((S_818CF0E8_6 *)p)->unk_0D = arg2->unk_0D;
        ((S_818CF0E8_6 *)p)->unk_0E = arg2->unk_0E;
        ((S_818CF0E8_6 *)p)->unk_1A = func_80069EF8() & 0xFFF;
        ASM_SCHED_BARRIER();
        {
            register u8 *src ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
            register s32 w0 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
            register s32 w1 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
            register s32 w2 ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
            register s32 hi ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            hi = (s32)0x80020000;
            ASM_KEEP(hi);
            src = (u8 *)(hi + 0x5918);
            w0 = ((UW *)(src + 0))->w;
            w1 = ((UW *)(src + 4))->w;
            w2 = ((UW *)(src + 8))->w;
            ((UW *)((u8 *)obj + 0x40))->w = w0;
            ((UW *)((u8 *)obj + 0x44))->w = w1;
            ((UW *)((u8 *)obj + 0x48))->w = w2;
        }
        ASM_SCHED_BARRIER();
        ((S_818CF0E8_6 *)p)->unk_08.at00.v = (u8 *)obj + 0x40;
    }
    arg2->unk_1A = func_80069EF8() & 0xFFF;
}
