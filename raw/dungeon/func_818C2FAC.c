#include "common.h"

typedef unsigned long uptr;
typedef long long s64_local;
typedef union {
    s64_local all;
    struct {
        s32 hi;
        s32 lo;
    } part;
} product_pair;

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_800248C0(void) __attribute__((noreturn));
#ifndef NON_MATCHING
extern void func_800248CC(void) __attribute__((noreturn));
#else
extern void func_800248CC() __attribute__((noreturn));
#endif
extern s32 func_800249E4() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64(s32);
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();

extern u8 D_80024710[];
extern u8 D_80045340[];
extern u8 D_800DEC70[];

s32 func_818C2FAC(void *arg0, void *arg1, s32 arg2)
{
    register s32 angle ASM_REG("$4");
    s16 kind;
    s32 biased;
    s32 random;
    s32 reduced;
    s32 h1;
    s32 h2;
    s32 delta;
    s32 newv;
    u16 flags;
    u16 mode;
    s64_local pair01;
    product_pair pair;
    s32 quotient;
    s32 copy2;
    s32 copy3;
    s32 copy4;
    s32 copy5;
    register uptr input ASM_REG("$18") = (uptr)arg0;
    register uptr source ASM_REG("$20") = (uptr)arg1;
    register s32 a0i ASM_REG("$4");
    register s32 coord ASM_REG("$17");
    register uptr obj ASM_REG("$19");
    register uptr temp ASM_REG("$16");
    register s32 pa0 ASM_REG("$4");
    register u32 pg0 ASM_REG("$5");
    register s32 pa1 ASM_REG("$4");
    register u32 pg1 ASM_REG("$5");
    s32 prod;
    s32 magic;
    void *work;

    a0i = 0x212;
    ASM_KEEP_NV(a0i);
    coord = arg2;
    obj = (uptr)func_8003FC64(a0i);
    ASM_KEEP(input);
    ASM_KEEP(source);
    ASM_KEEP(coord);
    if (obj != NULL) {

    FIELD((void *)obj, void *, 0x10) = D_80024710;
    FIELD((void *)obj, s32, 0x20) = FIELD((void *)input, s32, 0);
    work = (u8 *)obj + 0x20;
    FIELD(work, s16, 4) = 0;
    FIELD(work, s16, 6) = 0;

    temp = (uptr)FIELD((void *)obj, void *, 0xC);
    flags = FIELD((void *)temp, volatile u16, 0x14);
    FIELD((void *)temp, volatile u8, 0xE) = 0x80;
    FIELD((void *)temp, volatile u8, 0xD) = 0x80;
    FIELD((void *)temp, volatile u8, 0xC) = 0x80;
    mode = FIELD((void *)temp, volatile u16, 0x10);
    flags |= 0xC;
    mode |= 0x60;
    FIELD((void *)temp, volatile u16, 0x14) = flags;
    flags |= 0x100;
    FIELD((void *)temp, volatile u16, 0x10) = mode;
    FIELD((void *)temp, volatile u16, 0x14) = flags;

    angle = FIELD((void *)input, s16, 0x12);
    biased = angle;
    if (angle < 0) {
        biased = angle + 3;
    }
    kind = angle - ((biased >> 2) * 4);
    ASM_USE(angle);

    if (kind == 1) goto case1;
    if (kind >= 2) goto tree2;
    pa0 = (s32)temp;
    if (kind == 0) goto case0;
#ifndef NON_MATCHING
    ASM_KEEP(pa0);
    pg0 = 0x800E0000;
    ASM_PAGEBASE_PIN(pg0);
    func_800248CC();
#else
    func_800248CC((void *)temp, 0x800E0000);
#endif
tree2:
    if (kind == 2) goto case2;
    pa1 = (s32)temp;
    if (kind == 3) goto case3;
#ifndef NON_MATCHING
    ASM_KEEP(pa1);
    pg1 = 0x800E0000;
    ASM_PAGEBASE_PIN(pg1);
    func_800248CC();
#else
    func_800248CC((void *)temp, 0x800E0000);
#endif
case0:
    {
        register s32 vpin0 ASM_REG("$2");
        vpin0 = 0x7DCF;
        ASM_TAILSLOT_PIN(vpin0);
        func_800248C0();
    }
case1:
    {
        register s32 vpin1 ASM_REG("$2");
        vpin1 = 0x7E00;
        ASM_TAILSLOT_PIN(vpin1);
        func_800248C0();
    }
case2:
    {
        register s32 vpin2 ASM_REG("$2");
        vpin2 = 0x7E01;
        ASM_TAILSLOT_PIN(vpin2);
        func_800248C0();
    }
case3:
    FIELD((void *)temp, s16, 0x12) = 0x7E02;
    ASM_CLOBBER("$4");
    {
        register s32 A0p ASM_REG("$4");
        register u8 *A1p ASM_REG("$5");
        A0p = (s32)temp;
        A1p = D_800DEC70;
        func_8003DB94(A0p, A1p, 0);
    }
    random = func_80069EF8();
    reduced = random;
    if (random < 0) {
        reduced = random + 0xFFF;
    }
    FIELD((void *)temp, s16, 0x1A) = random - ((reduced >> 12) << 12);
    FIELD((void *)temp, s16, 0x1E) = 0x1000;
    FIELD((void *)temp, s16, 0x1C) = 0x1000;
    func_8004491C((void *)obj, D_80045340);

    input = (uptr)FIELD((void *)obj, void *, 8);
    pair01 = FIELD((void *)source, s64_local, 0);
    copy2 = FIELD((void *)source, s32, 8);
    copy3 = FIELD((void *)source, s32, 0xC);
    FIELD((void *)input, s64_local, 0) = pair01;
    FIELD((void *)input, s32, 8) = copy2;
    FIELD((void *)input, s32, 0xC) = copy3;
    copy4 = FIELD((void *)source, s32, 0x10);
    copy5 = FIELD((void *)source, s32, 0x14);
    FIELD((void *)input, s32, 0x10) = copy4;
    FIELD((void *)input, s32, 0x14) = copy5;

    random = func_80069EF8();
    magic = 0x78787879;
    temp = (uptr)random;
    ASM_USE_NV(magic);
    coord = (s16)coord;
    temp = (uptr)((s32)temp % 17 + 0x20);
    h1 = func_800644B8(coord) >> 4;
    ASM_SCHED_BARRIER();
    temp = (uptr)(s16)(s32)temp;
    {
        s32 sh1;
        prod = h1 * (s32)temp;
        sh1 = prod << 8;
        FIELD((void *)input, s32, 0) += sh1;
    }
    {
        register s32 ret ASM_REG("$2");
        h2 = func_80064584(coord) >> 4;
        ret = (s32)obj;
        prod = h2 * (s32)temp;
        delta = prod << 8;
        newv = FIELD((void *)input, s32, 4) + delta;
        ASM_KEEP(ret);
        FIELD((void *)input, s32, 4) = newv;
        func_800249E4(delta);
    }

    }
    {
        register s32 rv ASM_REG("$2");
        rv = 0;
        ASM_KEEP(rv);
        return rv;
    }
}
