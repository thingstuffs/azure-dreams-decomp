#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    s32 sp18;
    s32 sp1C;
} StackLocals;

typedef union {
    long long value;
    struct {
        s32 hi;
        s32 lo;
    } words;
} SignedProduct;

extern s32 func_80065420(void *, void *, void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_80066708(void *);
extern void func_8006671C(void *, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s32 func_800F8394() __attribute__((noreturn));
extern s32 func_800F83EC() __attribute__((noreturn));
extern s32 func_800F8488() __attribute__((noreturn));
extern s32 func_800F8500() __attribute__((noreturn));
extern s32 func_800F87C0() __attribute__((noreturn));
extern s32 func_800F87C8() __attribute__((noreturn));
extern u8 *D_80083160;

#ifdef NON_MATCHING
#define LOAD_SPLIT_GLOBAL(var) ((var) = &D_80083160)
#else
#define LOAD_SPLIT_GLOBAL(var) \
    do { \
        (var) = (u8 **)0x80080000; \
        ASM_KEEP_NV(var); \
        (var) = (u8 **)((u8 *)(var) + 0x3160); \
    } while (0)
#endif

#ifdef NON_MATCHING
#define LOAD_GLOBAL_PAGE(var) ((var) = &D_80083160)
#define FINISH_GLOBAL_TABLE(var, dep1, dep2) ((void)0)
#else
#define LOAD_GLOBAL_PAGE(var) \
    do { \
        (var) = (u8 **)0x80080000; \
        ASM_KEEP_NV(var); \
    } while (0)
#define FINISH_GLOBAL_TABLE(var, dep1, dep2) \
    do { \
        ASM_KEEP_DEP_NV(var, dep1); \
        ASM_KEEP_DEP_NV(var, dep2); \
        (var) = (u8 **)((u8 *)(var) + 0x3160); \
    } while (0)
#endif

s32 func_807B0B3C(void *object, s32 arg1, void *arg2) {
    register u8 *scratch ASM_REG("$22");
    register u8 *colors ASM_REG("$21");
    register u8 *verts ASM_REG("$23");
    register u32 mask;
    register u8 *arg0 ASM_REG("$19");
    register s32 in_a1 ASM_REG("$5") = arg1;
    register void *in_a2 ASM_REG("$6") = arg2;
    register s32 magic ASM_REG("$9");
    StackLocals local;
    register u32 work ASM_REG("$4");
    register s32 count ASM_REG("$18");
    register s32 average ASM_REG("$20");
    register s32 offset ASM_REG("$17");
    register s32 constant ASM_REG("$5");
    register void *ca0 ASM_REG("$4");
    register s32 value ASM_REG("$2");
    s32 color;
    u8 *p;
    u8 *q;
    register u8 *prim ASM_REG("$16");
    register u8 *initial ASM_REG("$9");
    register u8 *next ASM_REG("$4");
    register u16 half ASM_REG("$3");
    s32 coord;

    (void)&object;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);
    colors = scratch;
    ASM_KEEP_NV(colors);
    colors = (u8 *)((u32)colors | 0x40);
    verts = scratch;
    ASM_KEEP_NV(verts);
    verts = (u8 *)((u32)verts | 0x80);
    magic = 0x66666667;
    mask = 0xFFFFFF;
    ASM_KEEP(verts);
    ASM_KEEP(mask);
    local.sp1C = magic;
    ASM_MEM_BARRIER();
    initial = (u8 *)object;
    arg0 = initial;
    if ((FIELD(initial, u16, 6) >> 10) & 1) {
        register u8 *a3p ASM_REG("$7");
        register u8 *a0p ASM_REG("$4");
        register u32 a2v ASM_REG("$6");
        register s32 a0h ASM_REG("$4");
        register s32 a1v ASM_REG("$5");
        register s32 v1 ASM_REG("$3");
        register u16 v0h ASM_REG("$2");
        register s32 product_hi ASM_REG("$9");
        SignedProduct product;

        count = 0;
        a3p = scratch;
loop_a:
        v1 = count * 2;
        v0h = FIELD(arg0, u16, 0);
        local.sp18 = v1;
        FIELD(a3p, u16, 8) = v0h;
        FIELD(a3p, u16, 0) = v0h;
        a0p = a3p + 8;
        v1 = FIELD(arg0, s16, 2);
        if (count < 2) {
            register s32 implicit ASM_REG("$2");

            implicit = v1 - 0x20;
            ASM_TAILSLOT_PIN_TIED(implicit);
            return func_800F83EC(a0p, in_a1, in_a2, a3p);
        }
        ASM_KEEP(a0p);
        ASM_USE(v1);
        v0h = v1 + 0x20;
        ASM_KEEP(v0h);
        FIELD(a0p, volatile u16, 2) = v0h;
        a2v = local.sp18;
        v0h = FIELD(a0p, volatile u16, 2);
        a2v <<= 3;
        FIELD(a3p, u16, 2) = v0h;
        a0h = FIELD(arg0, u16, 4);
        a2v += (u32)scratch;
        FIELD((u8 *)a2v, u16, 0xC) = a0h;
        v0h = FIELD(arg0, u16, 8);
        magic = local.sp1C;
        a1v = (s16)v0h;
        ASM_USE(magic);
        ASM_SCHED_BARRIER();
        product.value = (long long)a1v * magic;
        count++;
        a3p += 0x10;
        ASM_KEEP_NV(product.words.hi);
        product_hi = product.words.hi;
        ASM_KEEP_NV(product_hi);
        v1 = product_hi >> 1;
        v1 -= a1v >> 31;
        a1v -= v1 * 5;
        a0h = a0h + a1v - 0x36;
        FIELD((u8 *)a2v, s16, 4) = a0h;
        if (count < 2) {
            goto loop_a;
        }
        average = 0;
        ASM_TAILSLOT_PIN_TIED(average);
        return func_800F8500(a0h, a1v, (void *)a2v, a3p);
    }

    {
        register s32 a2p ASM_REG("$6");
        u8 *a0p;
        register s32 a0h ASM_REG("$4");
        register s32 t0p ASM_REG("$8");
        register s32 a3end ASM_REG("$7");
        register s32 a1v ASM_REG("$5");
        register s32 v1 ASM_REG("$3");
        register u16 v0h ASM_REG("$2");
        register s32 product_hi ASM_REG("$9");
        SignedProduct product;

        a2p = (s32)scratch;
        t0p = (s32)scratch + 0x10;
        a3end = (s32)scratch + 0x20;
loop_b:
        v1 = FIELD(arg0, s16, 0);
        a0p = (u8 *)a2p + 8;
        if (a2p < t0p) {
            register s32 implicit ASM_REG("$2");

            implicit = v1 - 0x20;
            ASM_TAILSLOT_PIN_TIED(implicit);
            return func_800F8488(a0p, in_a1, (void *)a2p, (void *)a3end);
        }
        v0h = v1 + 0x20;
        FIELD((u8 *)a2p, u16, 8) = v0h;
        ASM_KEEP_NV(a0p);
        v0h = FIELD(a0p, volatile u16, 0);
        FIELD((u8 *)a2p, u16, 0) = v0h;
        ASM_SCHED_BARRIER();
        v0h = FIELD(arg0, u16, 2);
        ASM_SCHED_BARRIER();
        v1 = (s32)((u32)8 + (u32)a2p);
        ASM_KEEP(v1);
        FIELD((u8 *)v1, u16, 2) = v0h;
        FIELD((u8 *)a2p, u16, 2) = v0h;
        a0h = FIELD(arg0, u16, 4);
        FIELD((u8 *)v1, u16, 4) = a0h;
        v0h = FIELD(arg0, u16, 8);
        magic = local.sp1C;
        a1v = (s16)v0h;
        ASM_USE(magic);
        ASM_SCHED_BARRIER();
        product.value = (long long)a1v * magic;
        ASM_KEEP_NV(product.words.hi);
        product_hi = product.words.hi;
        ASM_KEEP_NV(product_hi);
        v1 = product_hi >> 1;
        v1 -= a1v >> 31;
        a1v -= v1 * 5;
        a0h = a0h + a1v - 0x36;
        FIELD((u8 *)a2p, s16, 4) = a0h;
        a2p += 0x10;
        ASM_SCHED_BARRIER();
        average = 0;
        if (a2p < a3end) {
            goto loop_b;
        }
    }

    ASM_KEEP_NV(average);
    count = average;
    q = verts;
    p = scratch;
    do {
        register void *call_a0 ASM_REG("$4") = p;
        register void *call_a1 ASM_REG("$5") = q;
        register void *call_a2 ASM_REG("$6");
        register void *call_a3 ASM_REG("$7");
        register s32 before ASM_REG("$3");
        s32 result;

        ASM_KEEP_NV(call_a0);
        ASM_KEEP_NV(call_a1);
        call_a2 = &local.sp18;
        call_a3 = call_a2;
        result = func_80065420(call_a0, call_a1, call_a2, call_a3);
        before = average - 8;
        ASM_KEEP_NV(before);
        average = before + result;
        q += 4;
        count++;
        p += 8;
    } while (count < 4);

    {
        register s32 rounded ASM_REG("$2");

        rounded = average;
        if (average < 0) {
            rounded = average + 3;
        }
        ASM_KEEP_NV(rounded);
        average = rounded >> 2;
        ASM_KEEP_NV(average);
    }

    {
        register u8 **globalp ASM_REG("$9");
        register u8 *rootp ASM_REG("$3");

        globalp = &D_80083160;
        ASM_KEEP_NV(globalp);
        rootp = *globalp;
        ASM_KEEP_NV(rootp);
        prim = *(u8 **)(rootp + 0x8D0);
        ca0 = (void *)prim;
        ASM_KEEP_NV(ca0);
        *(u8 **)(rootp + 0x8D0) = prim + 0x34;
    }
    constant = 0xA0A0A0;
    FIELD(prim, s32, 0x1C) = 0;
    FIELD(prim, s32, 4) = 0;
    ASM_SCHED_BARRIER();
    FIELD(prim, s32, 0x28) = constant;
    FIELD(prim, s32, 0x10) = constant;
    func_8006671C(ca0, constant);
    func_80066640(prim, 1);
    FIELD(prim, s16, 0x1A) = func_80066460(0, 1, 0x280, 0x100);
    {
        u16 texture;
        register s32 firstvert ASM_REG("$3");

        texture = func_8006649C(0x90, 0x1F7);
        firstvert = FIELD(verts, s32, 0);
        ASM_KEEP_NV(firstvert);
        FIELD(prim, s16, 0xE) = texture;
        FIELD(prim, s32, 8) = firstvert;
    }
    FIELD(prim, s32, 0x14) = FIELD(verts, s32, 4);
    FIELD(prim, s32, 0x20) = FIELD(verts, s32, 8);
    FIELD(prim, s32, 0x2C) = FIELD(verts, s32, 0xC);

    work = FIELD(arg0, u16, 8) & 7;
    value = (work & 3) << 5;
    color = value - 0x80;
    value -= 0x61;
    work = (work >> 2) << 5;
    FIELD(prim, s8, 0x30) = value;
    FIELD(prim, s8, 0x24) = value;
    value = work - 0x40;
    work -= 0x21;
    FIELD(prim, s8, 0x31) = value;
    FIELD(prim, s8, 0x19) = value;
    FIELD(prim, s8, 0x18) = color;
    FIELD(prim, s8, 0xC) = color;
    FIELD(prim, s8, 0x25) = work;
    FIELD(prim, s8, 0xD) = work;

    if ((u32)average < 0x1E0U) {
        register u8 **next_globalp ASM_REG("$9");

        {
            register u8 **globalp ASM_REG("$9");
            register u8 *rootp ASM_REG("$2");
            register u32 highmask ASM_REG("$9");
            register u32 primword ASM_REG("$3");
            register u32 bucket ASM_REG("$2");

            globalp = &D_80083160;
            ASM_KEEP_NV(globalp);
            work = average * 4;
            rootp = *globalp;
            ASM_KEEP_NV(rootp);
            highmask = 0xFF000000;
            ASM_KEEP_NV(highmask);
            primword = FIELD(prim, u32, 0);
            ASM_SCHED_BARRIER();
            rootp = (u8 *)((u32)work + (u32)rootp);
            primword &= highmask;
            LOAD_GLOBAL_PAGE(next_globalp);
            bucket = FIELD(rootp, u32, 0xB0);
            FINISH_GLOBAL_TABLE(next_globalp, bucket, primword);
            ASM_KEEP_NV(next_globalp);
            FIELD(prim, u32, 0) = primword | (bucket & mask);
        }
        {
            register u8 *rootp ASM_REG("$2");
            register u8 *entryp ASM_REG("$4");
            register u32 highmask ASM_REG("$9");

            rootp = *next_globalp;
            ASM_KEEP_NV(rootp);
            highmask = 0xFF000000;
            ASM_KEEP_NV(highmask);
            entryp = (u8 *)((u32)work + (u32)rootp);
            ASM_KEEP_NV(entryp);
            FIELD(entryp, u32, 0xB0) =
                (FIELD(entryp, u32, 0xB0) & highmask) |
                ((u32)prim & mask);
            ASM_KEEP(prim);
        }
    }

    {
        register u8 *a0p ASM_REG("$4");
        register u8 *a1p ASM_REG("$5");

        count = 3;
        a1p = colors + 0xC;
        a0p = scratch + 0x18;
        do {
            coord = FIELD(arg0, s16, 0);
            if (count < 2) {
                FIELD(a0p, s16, 0) = coord - 0x20;
            } else {
                FIELD(a0p, s16, 0) = coord + 0x20;
            }
            coord = FIELD(arg0, s16, 2);
            if (count & 1) {
                FIELD(a0p, s16, 2) = coord + 0x20;
            } else {
                FIELD(a0p, s16, 2) = coord - 0x20;
            }
            count--;
            FIELD(a0p, u16, 4) = FIELD(arg0, u16, 4);
            a0p -= 8;
            value = (FIELD(arg0, u8, 8) & 3) * 8;
            FIELD(a1p, s8, 2) = value;
            FIELD(a1p, s8, 1) = value;
            FIELD(a1p, s8, 0) = value;
            a1p -= 4;
        } while (count >= 0);
    }

    coord = FIELD(arg0, s16, 6);
    if (coord == 0x400) {
        goto coord_400;
    }
    if (coord > 0x400) {
        goto coord_high;
    }
    if (coord == 0) {
        goto coord_0;
    }
    {
        register s32 c3 ASM_REG("$18");
        register u8 *qq ASM_REG("$17");

        c3 = 3;
        qq = verts + 0xC;
        ASM_TAILSLOT_PIN_TIED(c3);
        ASM_TAILSLOT_PIN_TIED(qq);
        return func_800F87C8();
    }

coord_high:
    if (coord == 0x800) {
        goto coord_800;
    }
    if (coord != 0xC00) {
        register s32 c3 ASM_REG("$18");
        register u8 *qq ASM_REG("$17");

        c3 = 3;
        qq = verts + 0xC;
        ASM_TAILSLOT_PIN_TIED(c3);
        ASM_TAILSLOT_PIN_TIED(qq);
        return func_800F87C8();
    }
    goto coord_C00;

coord_0:
    ASM_SCHED_BARRIER();
    FIELD(colors, u32, 8) = 0x808080;
    FIELD(colors, u32, 0) = 0x808080;
    half = FIELD(arg0, u16, 2);
    ASM_SCHED_BARRIER();
    {
        register u8 *dst ASM_REG("$2");

        dst = scratch + 0x10;
        ASM_KEEP_NV(dst);
        FIELD(dst, u16, 2) = half;
    }
    FIELD(scratch, u16, 2) = half;
    return func_800F87C0();

coord_400:
    half = FIELD(arg0, u16, 0);
    FIELD(colors, u32, 0xC) = 0x808080;
    FIELD(colors, u32, 8) = 0x808080;
    FIELD(scratch, u16, 0x18) = half;
    FIELD(scratch, u16, 0x10) = half;
    return func_800F87C0();

coord_800:
    FIELD(colors, u32, 0xC) = 0x808080;
    FIELD(colors, u32, 4) = 0x808080;
    half = FIELD(arg0, u16, 2);
    ASM_SCHED_BARRIER();
    {
        register u8 *dst ASM_REG("$2");

        dst = scratch + 0x18;
        ASM_KEEP_NV(dst);
        FIELD(dst, u16, 2) = half;
    }
    FIELD(scratch, u16, 0xA) = half;
    return func_800F87C0();

coord_C00:
    ASM_SCHED_BARRIER();
    half = FIELD(arg0, u16, 0);
    FIELD(colors, u32, 4) = 0x808080;
    FIELD(colors, u32, 0) = 0x808080;
    FIELD(scratch, u16, 8) = half;
    FIELD(scratch, u16, 0) = half;

    ASM_SCHED_BARRIER();
    count = 3;
    q = verts + 0xC;
    p = scratch + 0x18;
    do {
        register void *call_a0 ASM_REG("$4") = p;
        register void *call_a1 ASM_REG("$5") = q;
        register void *call_a2 ASM_REG("$6");
        register void *call_a3 ASM_REG("$7");

        ASM_KEEP_NV(call_a0);
        ASM_KEEP_NV(call_a1);
        call_a2 = &local.sp18;
        call_a3 = call_a2;
        func_80065420(call_a0, call_a1, call_a2, call_a3);
        q -= 4;
        count--;
        p -= 8;
    } while (count >= 0);

    if ((u32)average < 0x1E0U) {
        register s32 one ASM_REG("$5");
        register s32 zero2 ASM_REG("$6");
        register s32 zero3 ASM_REG("$7");
        register u8 **next_globalp ASM_REG("$9");

        {
            register u8 **globalp ASM_REG("$9");
            register u8 *rootp ASM_REG("$3");

            LOAD_SPLIT_GLOBAL(globalp);
            ASM_KEEP_NV(globalp);
            rootp = *globalp;
            ASM_KEEP_NV(rootp);
            prim = *(u8 **)(rootp + 0x8D0);
            ASM_SCHED_BARRIER();
            {
            register s32 firstcolor ASM_REG("$4");

            firstcolor = FIELD(colors, s32, 0);
            ASM_KEEP_NV(firstcolor);
            *(u8 **)(rootp + 0x8D0) = prim + 0x24;
            FIELD(prim, s32, 4) = firstcolor;
            }
        }
        FIELD(prim, s32, 0xC) = FIELD(colors, s32, 4);
        FIELD(prim, s32, 0x14) = FIELD(colors, s32, 8);
        FIELD(prim, s32, 0x1C) = FIELD(colors, s32, 0xC);
        func_80066708(prim);
        func_80066640(prim, 1);
        {
            register u8 **globalp ASM_REG("$9");
            register u8 *rootp ASM_REG("$2");
            register u32 highmask ASM_REG("$9");
            register s32 vertex ASM_REG("$2");
            register u32 primword ASM_REG("$3");
            register u32 bucket ASM_REG("$2");

            LOAD_GLOBAL_PAGE(globalp);
            vertex = FIELD(verts, s32, 0);
            primword = FIELD(prim, u32, 0);
            FINISH_GLOBAL_TABLE(globalp, vertex, primword);
            ASM_KEEP_NV(globalp);
            FIELD(prim, s32, 8) = vertex;
            vertex = FIELD(verts, s32, 4);
            ASM_SCHED_BARRIER();
            offset = average * 4;
            ASM_KEEP_NV(offset);
            FIELD(prim, s32, 0x10) = vertex;
            vertex = FIELD(verts, s32, 8);
            ASM_SCHED_BARRIER();
            work = 0;
            ASM_KEEP_NV(work);
            FIELD(prim, s32, 0x18) = vertex;
            vertex = FIELD(verts, s32, 0xC);
            ASM_SCHED_BARRIER();
            one = 1;
            ASM_KEEP_NV(one);
            FIELD(prim, s32, 0x20) = vertex;
            rootp = *globalp;
            ASM_KEEP_NV(rootp);
            highmask = 0xFF000000;
            ASM_KEEP_NV(highmask);
            primword &= highmask;
            LOAD_GLOBAL_PAGE(next_globalp);
            rootp = (u8 *)((u32)offset + (u32)rootp);
            bucket = FIELD(rootp, u32, 0xB0);
            FINISH_GLOBAL_TABLE(next_globalp, bucket, primword);
            ASM_KEEP_NV(next_globalp);
            FIELD(prim, u32, 0) = primword | (bucket & mask);
        }
        {
            register u8 *entryp ASM_REG("$3");
            register u32 highmask ASM_REG("$9");
            register u32 entryword ASM_REG("$2");

            entryp = *next_globalp;
            ASM_KEEP_NV(entryp);
            highmask = 0xFF000000;
            ASM_KEEP_NV(highmask);
            entryp = (u8 *)((u32)offset + (u32)entryp);
            entryword =
                (FIELD(entryp, u32, 0xB0) & highmask) |
                ((u32)prim & mask);
            ASM_SCHED_BARRIER();
            next_globalp = &D_80083160;
            ASM_KEEP_NV(next_globalp);
            FIELD(entryp, u32, 0xB0) = entryword;
            entryp = *next_globalp;
            ASM_KEEP_NV(entryp);
            ASM_SCHED_BARRIER();
            zero2 = work;
            ASM_KEEP_NV(zero2);
            prim = *(u8 **)(entryp + 0x8D0);
            ASM_SCHED_BARRIER();
            zero3 = work;
            ASM_KEEP_NV(zero3);
            *(u8 **)(entryp + 0x8D0) = prim + 0xC;
        }
        half = func_80066460(work, one, zero2, zero3);
        {
            register s32 z ASM_REG("$5");
            register void *pa ASM_REG("$4");

            pa = (void *)prim;
            ASM_KEEP_NV(pa);
            z = 0;
            ASM_KEEP_NV(z);
            func_80067F20(pa, z, z, half, 0);
        }

        {
            register u8 **globalp ASM_REG("$9");
            register u8 *entryp ASM_REG("$2");
            register u32 highmask ASM_REG("$9");
            register u32 primword ASM_REG("$3");
            register u32 bucket ASM_REG("$2");

            globalp = &D_80083160;
            ASM_KEEP_NV(globalp);
            entryp = *globalp;
            ASM_KEEP_NV(entryp);
            highmask = 0xFF000000;
            ASM_KEEP_NV(highmask);
            primword = FIELD(prim, u32, 0);
            ASM_SCHED_BARRIER();
            entryp = (u8 *)((u32)offset + (u32)entryp);
            primword &= highmask;
            LOAD_GLOBAL_PAGE(next_globalp);
            bucket = FIELD(entryp, u32, 0xB0);
            FINISH_GLOBAL_TABLE(next_globalp, bucket, primword);
            ASM_KEEP_NV(next_globalp);
            FIELD(prim, u32, 0) = primword | (bucket & mask);
        }
        {
            register u8 *rootp ASM_REG("$2");
            register u32 highmask ASM_REG("$9");

            rootp = *next_globalp;
            ASM_KEEP_NV(rootp);
            highmask = 0xFF000000;
            ASM_KEEP_NV(highmask);
            offset += (s32)rootp;
            FIELD((u8 *)offset, u32, 0xB0) =
                (FIELD((u8 *)offset, u32, 0xB0) & highmask) |
                ((u32)prim & mask);
        }
    }

    ASM_KEEP_NV(mask);
    initial = (u8 *)object;
    ASM_KEEP_NV(initial);
    next = FIELD(initial, u8 *, -8);
    if (next != 0) {
        next += 0x20;
        object = next;
        return func_800F8394(next);
    }
    ASM_SCHED_BARRIER();
    {
        register s32 zr ASM_REG("$0");

        return zr;
    }
}
