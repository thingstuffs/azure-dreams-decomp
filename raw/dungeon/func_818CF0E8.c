#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

void func_818CF0E8(void *arg0, void *arg1, void *arg2)
{
    register u8 *star ASM_REG("$20");
    void *env;
    void *obj;
    void *p;
    s32 dv;
    s32 av;
    u16 flags;
    s16 cnt;
    s32 r;
    s32 b;

    D_80025924[0] = 1;
    env = FIELD(arg0, void *, 0x2C);
    if (FIELD(arg0, s16, 0) == 0) {
        p = (void *)0;
        do {
            register void *a0v ASM_REG("$4");
            register s32 a2v ASM_REG("$6");
            register s32 a3v ASM_REG("$7");
            s32 rv;
            p = (u8 *)p + 1;
            rv = func_80069EF8();
            a0v = (u8 *)arg0 - 0x20;
            ASM_USE(a0v);
            a2v = 0xC0C0C0;
            a3v = (rv & 0xFF) | 0x80;
            ASM_USE2(a2v, a3v);
            func_80024358(a0v, FIELD(arg0, s16, 0x16), a2v, a3v, 0, 0, 0);
        } while ((s32)p < 4);
        if ((func_800A4778(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                           FIELD(arg1, s16, 0xA), FIELD(arg0, void *, 0x30)) << 0x10) != 0) {
            goto finish;
        }
        if (FIELD(arg0, s16, 8) != 0) {
            star = FIELD(FIELD(arg0, void *, 0x30), void *, -0x18);
            if (FIELD(arg1, s32, 8) < FIELD(star, s32, 8) + (s32)0xFF800000) {
                FIELD(arg0, s32, 0x54) /= 2;
            }
            {
            register s32 d ASM_REG("$3");
            register s32 aw ASM_REG("$2");
            d = FIELD(arg1, s16, 2);
            d -= FIELD(star, s16, 2);
            aw = d;
            if (d < 0) {
                aw = 0 - aw;
            }
            if (aw < 8) {
                register s32 v ASM_REG("$4");
                register s32 a ASM_REG("$3");
                register s32 lim ASM_REG("$2");
                lim = 0x40000;
                v = FIELD(arg0, s32, 0x4C);
                a = v;
                if (v < 0) {
                    a = 0 - a;
                }
                if (a > lim) {
                    register s32 t ASM_REG("$2");
                    t = v / 2;
                    ASM_TAILSLOT_PIN(t);
                    func_80024A58();
                    return;
                }
            } else if (FIELD(arg0, s32, 0x4C) == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                FIELD(arg0, s32, 0x4C) = nv;
            }
            }
            {
            register s32 d ASM_REG("$3");
            register s32 aw ASM_REG("$2");
            d = FIELD(arg1, s16, 6);
            d -= FIELD(star, s16, 6);
            aw = (d >= 0) ? d : (0 - d);
            if (aw < 8) {
                register s32 v ASM_REG("$4");
                register s32 a ASM_REG("$3");
                register s32 lim ASM_REG("$2");
                lim = 0x40000;
                v = FIELD(arg0, s32, 0x50);
                a = v;
                if (v < 0) {
                    a = 0 - a;
                }
                if (a > lim) {
                    register s32 t ASM_REG("$2");
                    t = v / 2;
                    ASM_TAILSLOT_PIN(t);
                    func_80024ACC();
                    return;
                }
            } else if (FIELD(arg0, s32, 0x50) == 0) {
                s32 nv = -0x200000;
                if (d <= 0) {
                    nv = 0x200000;
                }
                FIELD(arg0, s32, 0x50) = nv;
            }
            }
            {
                register u16 a2v ASM_REG("$6");
                register u16 a1v ASM_REG("$5");
                register s32 aw ASM_REG("$3");
                register s32 d ASM_REG("$2");
                s32 st;
                a2v = FIELD(arg1, u16, 2);
                ASM_MEM_BARRIER();
                d = FIELD(arg1, s16, 2);
                st = FIELD(star, s16, 2);
                ASM_MEM_BARRIER();
                a1v = FIELD(star, u16, 2);
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    register s32 t ASM_REG("$2");
                    ASM_USE2(a2v, a1v);
                    t = FIELD(arg1, s32, 0);
                    t += FIELD(arg0, s32, 0x4C);
                    ASM_TAILSLOT_PIN(t);
                    func_80024B48();
                    return;
                }
                if (aw >= 4) {
                    FIELD(arg1, s32, 0) += (FIELD(arg0, s32, 0x4C) * aw) / 192;
                    func_80024B6C();
                    return;
                }
                if (FIELD(arg0, s16, 0x38) != FIELD(arg0, s16, 0x3C)) {
                    register s32 one ASM_REG("$2");
                    one = 1;
                    FIELD(arg0, s16, 0) = one;
                    FIELD(arg0, s16, 2) = 0;
                    ASM_CLOBBER("$2");
                    ASM_MEM_BARRIER();
                    if (FIELD(arg0, s16, 0x38) != FIELD(arg0, s16, 0x3C)) {
                        s32 v = FIELD(arg0, s32, 0x4C);
                        if (v > 0) {
                            register s32 t1 ASM_REG("$3");
                            register s32 t0 ASM_REG("$2");
                            t1 = a1v << 0x10;
                            ASM_USE(t1);
                            t0 = a2v << 0x10;
                            ASM_TAILSLOT_PIN(t0);
                            func_80024BA4();
                            return;
                        }
                        if (v < 0) {
                            if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                                FIELD(arg0, s16, 0) = 1;
                                FIELD(arg0, s16, 2) = 0;
                            }
                        }
                    }
                }
                ASM_USE2(a2v, a1v);
            }
            {
                register u16 a2v ASM_REG("$6");
                register u16 a1v ASM_REG("$5");
                register s32 aw ASM_REG("$3");
                register s32 d ASM_REG("$2");
                s32 st;
                a2v = FIELD(arg1, u16, 6);
                ASM_MEM_BARRIER();
                d = FIELD(arg1, s16, 6);
                st = FIELD(star, s16, 6);
                ASM_MEM_BARRIER();
                a1v = FIELD(star, u16, 6);
                d -= st;
                aw = (d >= 0) ? d : (0 - d);
                if (aw >= 0xC1) {
                    register s32 t ASM_REG("$2");
                    ASM_USE2(a2v, a1v);
                    t = FIELD(arg1, s32, 4);
                    t += FIELD(arg0, s32, 0x50);
                    ASM_TAILSLOT_PIN(t);
                    func_80024C30();
                    return;
                }
                if (aw >= 4) {
                    FIELD(arg1, s32, 4) += (FIELD(arg0, s32, 0x50) * aw) / 192;
                    func_80024C54();
                    return;
                }
                if (FIELD(arg0, s16, 0x3A) != FIELD(arg0, s16, 0x3E)) {
                    register s32 one ASM_REG("$2");
                    one = 1;
                    FIELD(arg0, s16, 0) = one;
                    FIELD(arg0, s16, 2) = 0;
                    ASM_CLOBBER("$2");
                    ASM_MEM_BARRIER();
                    if (FIELD(arg0, s16, 0x3A) != FIELD(arg0, s16, 0x3E)) {
                        s32 v = FIELD(arg0, s32, 0x50);
                        if (v > 0) {
                            register s32 t1 ASM_REG("$3");
                            register s32 t0 ASM_REG("$2");
                            t1 = a1v << 0x10;
                            ASM_USE(t1);
                            t0 = a2v << 0x10;
                            ASM_TAILSLOT_PIN(t0);
                            func_80024C8C();
                            return;
                        }
                        if (v < 0) {
                            if ((s32)(a2v << 0x10) <= (s32)(a1v << 0x10)) {
                                FIELD(arg0, s16, 0) = 1;
                                FIELD(arg0, s16, 2) = 0;
                            }
                        }
                    }
                }
                ASM_USE2(a2v, a1v);
            }
            if (FIELD(arg0, s32, 0x4C) != 0) {
                register u16 a2v ASM_REG("$6");
                register u16 a1v ASM_REG("$5");
                register s32 t ASM_REG("$2");
                a2v = FIELD(arg1, u16, 2);
                a1v = FIELD(star, u16, 2);
                ASM_USE(a1v);
                t = a2v << 0x10;
                ASM_TAILSLOT_PIN(t);
                func_80024CCC();
                return;
            }
            {
                register u16 a2v ASM_REG("$6");
                register u16 a1v ASM_REG("$5");
                register s32 aw ASM_REG("$3");
                register s32 d ASM_REG("$2");
                s32 st;
                a2v = FIELD(arg1, u16, 6);
                a1v = FIELD(star, u16, 6);
                d = (s16)a2v;
                st = (s16)a1v;
                d -= st;
                aw = d;
                if (d < 0) {
                    aw = 0 - aw;
                }
                if (aw >= 0xC1) {
                    register s32 t ASM_REG("$2");
                    ASM_USE2(a2v, a1v);
                    t = FIELD(arg1, s32, 8);
                    t += FIELD(arg0, s32, 0x54);
                    ASM_TAILSLOT_PIN(t);
                    func_80024D40();
                    return;
                }
                if (aw >= 4) {
                    FIELD(arg1, s32, 8) += (FIELD(arg0, s32, 0x54) * aw) / 192;
                    func_80024DA0();
                    return;
                }
            }
        } else {
            FIELD(arg0, u16, 4) -= 1;
            FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x4C);
            FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x50);
            FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x54);
            if (FIELD(arg0, s16, 4) <= 0) {
                goto finish;
            }
        }
    }
    if (FIELD(arg0, s16, 0) == 1) {
        if (FIELD(arg0, s16, 2) == 0) {
            func_800A56E0(0x300);
            func_800542BC();
        }
        cnt = FIELD(arg0, u16, 2) + 1;
        FIELD(arg0, s16, 2) = cnt;
        if (cnt >= 0xF) {
            FIELD(arg0, s16, 2) = 0;
            FIELD(arg0, u16, 0) += 1;
        }
    }
    if (FIELD(arg0, s16, 0) == 2) {
        FIELD(arg0, u16, 2) += 1;
        FIELD(arg2, u16, 0x1C) -= 0x32;
        FIELD(arg2, u16, 0x1E) -= 0x32;
        obj = func_8003FC64(0x212);
        {
            register u8 *s3 ASM_REG("$19");
            s3 = (u8 *)obj + 0x20;
            if (obj != 0) {
            FIELD(s3, s16, 2) = 0x34;
            FIELD(obj, void *, 0x10) = D_800245C8;
            func_8004491C(obj, D_80045340);
            p = FIELD(obj, void *, 0xC);
            flags = FIELD(p, u16, 0x14) | 0xC;
            FIELD(p, s16, 0x10) = 0x60;
            FIELD(p, u16, 0x14) = flags;
            ASM_SET(flags);
            FIELD(p, volatile u16, 0x14) = flags | 2;
            p = FIELD(obj, void *, 8);
            {
                register s32 r2 ASM_REG("$2");
                register s32 b2 ASM_REG("$3");
                r2 = func_80069EF8() & 0x1F;
                b2 = FIELD(arg1, u16, 2) - 0x10;
                b2 += r2;
                FIELD(p, s16, 2) = b2;
            }
            {
                register s32 r2 ASM_REG("$2");
                register s32 b2 ASM_REG("$3");
                r2 = func_80069EF8() & 0x1F;
                b2 = FIELD(arg1, u16, 6) - 0x10;
                b2 += r2;
                FIELD(p, s16, 6) = b2;
            }
            FIELD(p, u16, 0xA) = FIELD(arg1, u16, 0xA);
            FIELD(s3, s32, 0x54) = func_80069EF8() + 0x30000;
            FIELD(s3, s32, 0x60) = 0x6000;
            p = FIELD(obj, void *, 0xC);
            FIELD(p, s16, 0x1C) = 0x800;
            FIELD(p, s16, 0x1E) = 0x800;
            FIELD(p, u8, 0xE) = 0x80;
            FIELD(p, u8, 0xD) = 0x80;
            FIELD(p, u8, 0xC) = 0x80;
            flags = FIELD(p, volatile u16, 0x14) | 0x100;
            FIELD(p, s16, 0x12) = 0x7DCF;
            FIELD(p, u16, 0x14) = flags;
            func_8003DB94(p, D_800DE870, 0);
            }
        }
        if ((FIELD(arg0, u16, 2) & 3) == 1) {
            obj = func_8003FC64(0x212);
            {
            register u8 *s3 ASM_REG("$19");
            s3 = (u8 *)obj + 0x20;
            if (obj != 0) {
                FIELD(s3, s16, 2) = 0x14;
                FIELD(obj, void *, 0x10) = D_80024478;
                func_8004491C(obj, D_80045340);
                p = FIELD(obj, void *, 0xC);
                flags = FIELD(p, u16, 0x14) | 0xC;
                FIELD(p, s16, 0x10) = 0;
                FIELD(p, u16, 0x14) = flags;
                p = FIELD(obj, void *, 8);
                star = FIELD(FIELD(arg0, void *, 0x30), void *, -0x18);
                {
                    register s32 r2 ASM_REG("$2");
                    register s32 b2 ASM_REG("$3");
                    r2 = func_80069EF8() & 0x1F;
                    b2 = FIELD(star, u16, 2) - 0x10;
                    b2 += r2;
                FIELD(p, s16, 2) = b2;
                }
                {
                    register s32 r2 ASM_REG("$2");
                    register s32 b2 ASM_REG("$3");
                    r2 = func_80069EF8() & 0x1F;
                    b2 = FIELD(star, u16, 6) - 0x10;
                    b2 += r2;
                FIELD(p, s16, 6) = b2;
                }
                {
                    register s32 r2 ASM_REG("$2");
                    register s32 b2 ASM_REG("$3");
                    r2 = (func_80069EF8() & 0x3F) + 0x20;
                    b2 = FIELD(star, u16, 0xA);
                    b2 -= r2;
                    FIELD(p, s16, 0xA) = b2;
                }
                p = FIELD(obj, void *, 0xC);
                FIELD(p, s16, 0x1C) = 0x800;
                FIELD(p, s16, 0x1E) = 0x800;
                FIELD(s3, s32, 0x54) = func_80069EF8() + (s32)0xFFFE0000;
                FIELD(p, u8, 0xE) = 0x80;
                FIELD(p, u8, 0xD) = 0x80;
                FIELD(p, u8, 0xC) = 0x80;
                flags = FIELD(p, volatile u16, 0x14) | 0x100;
                FIELD(p, s16, 0x12) = 0x7DC0;
                FIELD(p, u16, 0x14) = flags;
                func_8003DB94(p, D_800DEC00, 0);
            }
            }
        }
        if (FIELD(arg0, s16, 2) >= 0x29) {
            FIELD(arg0, s16, 2) = 0;
            FIELD(arg0, u16, 0) += 1;
            if (func_8009D218(FIELD(env, s32, 0x60), 2, env) == 0) {
                s32 a2v;
                s32 a1v;
                s32 rr;
                rr = (func_800A6D30() & 3) + 2;
                a2v = (FIELD(arg0, u8, 0x15) >> 2) + rr;
                a1v = 0x10;
                if (D_800E3D68[0] == 0xFF) {
                    a1v = 0xFF;
                }
                func_800C8CD8(FIELD(arg0, void *, 0x30), a1v, a2v);
            }
        }
    }
    if (FIELD(arg0, s16, 0) == 3) {
        FIELD(arg0, u16, 2) += 1;
        FIELD(arg2, u16, 0x1C) -= 0x32;
        FIELD(arg2, u16, 0x1E) -= 0x32;
        if (FIELD(arg0, s16, 2) >= 0x15) {
finish:
            FIELD(FIELD(arg0, void *, 0x34), s16, 0x86) = 1;
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            func_80025344();
            return;
        }
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        FIELD(obj, s16, 0x22) = 1;
        FIELD(obj, void *, 0x10) = D_80024578;
        func_8004491C(obj, D_80045340);
        p = FIELD(obj, void *, 0xC);
        flags = FIELD(p, u16, 0x14) | 0xC;
        FIELD(p, s16, 0x10) = 0x60;
        FIELD(p, u16, 0x14) = flags;
        p = FIELD(obj, void *, 8);
        FIELD(p, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(p, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(p, u16, 0xA) = FIELD(arg1, u16, 0xA);
        p = FIELD(obj, void *, 0xC);
        FIELD(p, s16, 0x1E) = 0x1000;
        FIELD(p, s16, 0x1C) = 0x1000;
        FIELD(p, s16, 6) = -1;
        FIELD(p, u8, 0xC) = FIELD(arg2, u8, 0xC);
        FIELD(p, u8, 0xD) = FIELD(arg2, u8, 0xD);
        FIELD(p, u8, 0xE) = FIELD(arg2, u8, 0xE);
        FIELD(p, s16, 0x1A) = func_80069EF8() & 0xFFF;
        ASM_SCHED_BARRIER();
        {
            register u8 *src ASM_REG("$6");
            register s32 w0 ASM_REG("$3");
            register s32 w1 ASM_REG("$4");
            register s32 w2 ASM_REG("$5");
            register s32 hi ASM_REG("$2");
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
        FIELD(p, void *, 8) = (u8 *)obj + 0x40;
    }
    obj = func_8003FC64(0x12);
    if (obj != 0) {
        FIELD(obj, s16, 0x22) = 1;
        FIELD(obj, void *, 0x10) = D_80024578;
        func_8004491C(obj, D_80045340);
        p = FIELD(obj, void *, 0xC);
        flags = FIELD(p, u16, 0x14) | 0xC;
        FIELD(p, s16, 0x10) = 0x60;
        FIELD(p, u16, 0x14) = flags;
        p = FIELD(obj, void *, 8);
        FIELD(p, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(p, u16, 6) = FIELD(arg1, u16, 6);
        FIELD(p, u16, 0xA) = FIELD(arg1, u16, 0xA);
        p = FIELD(obj, void *, 0xC);
        FIELD(p, s16, 0x1E) = 0x1000;
        FIELD(p, s16, 0x1C) = 0x1000;
        FIELD(p, s16, 6) = -2;
        FIELD(p, u8, 0xC) = FIELD(arg2, u8, 0xC);
        FIELD(p, u8, 0xD) = FIELD(arg2, u8, 0xD);
        FIELD(p, u8, 0xE) = FIELD(arg2, u8, 0xE);
        FIELD(p, s16, 0x1A) = func_80069EF8() & 0xFFF;
        ASM_SCHED_BARRIER();
        {
            register u8 *src ASM_REG("$6");
            register s32 w0 ASM_REG("$3");
            register s32 w1 ASM_REG("$4");
            register s32 w2 ASM_REG("$5");
            register s32 hi ASM_REG("$2");
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
        FIELD(p, void *, 8) = (u8 *)obj + 0x40;
    }
    FIELD(arg2, s16, 0x1A) = func_80069EF8() & 0xFFF;
}
