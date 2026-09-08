#include "common.h"

typedef struct S_807B0B3C_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_807B0B3C_0_pre;   /* the 0x8 bytes before initial in func_807B0B3C, addressed as initial[-1] */

typedef struct S_807B0B3C_0 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_807B0B3C_0;   /* initial in func_807B0B3C */

typedef struct S_807B0B3C_1 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u16 unk_04;
    s16 unk_06;
    union { u16 u16; u8 u8; } unk_08;   /* accessed as both */
} S_807B0B3C_1;   /* arg0 in func_807B0B3C */

typedef struct S_807B0B3C_2 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
} S_807B0B3C_2;   /* a3p in func_807B0B3C */

typedef struct S_807B0B3C_3 {
    union { volatile u16 v; s16 n; } unk_00;   /* accessed as both */
    union { volatile u16 v; s16 n; } unk_02;   /* accessed as both */
    u16 unk_04;
} S_807B0B3C_3;   /* a0p in func_807B0B3C */

typedef struct S_807B0B3C_4 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    u16 unk_0C;
} S_807B0B3C_4;   /* (u8 *)a2v in func_807B0B3C */

typedef struct S_807B0B3C_5 {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B0B3C_5;   /* (u8 *)a2p in func_807B0B3C */

typedef struct S_807B0B3C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_807B0B3C_6;   /* (u8 *)v1 in func_807B0B3C */

typedef struct S_807B0B3C_7 {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    s32 unk_14;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    s32 unk_20;
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_807B0B3C_7;   /* prim in func_807B0B3C */

typedef struct S_807B0B3C_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_807B0B3C_8;   /* verts in func_807B0B3C */

typedef struct S_807B0B3C_9 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_9;   /* rootp in func_807B0B3C */

typedef struct S_807B0B3C_10 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_10;   /* entryp in func_807B0B3C */

typedef struct S_807B0B3C_11 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_807B0B3C_11;   /* a1p in func_807B0B3C */

typedef struct S_807B0B3C_12 {
    union { u32 u; s32 s; } unk_00;   /* accessed as both */
    union { u32 u; s32 s; } unk_04;   /* accessed as both */
    union { u32 u; s32 s; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
} S_807B0B3C_12;   /* colors in func_807B0B3C */

typedef struct S_807B0B3C_13 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_807B0B3C_13;   /* dst in func_807B0B3C */

typedef struct S_807B0B3C_14 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u8 pad_12[0x6];
    u16 unk_18;
} S_807B0B3C_14;   /* scratch in func_807B0B3C */

typedef struct S_807B0B3C_15 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_15;   /* (u8 *)offset in func_807B0B3C */



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
        \
    } while (0)
#define FINISH_GLOBAL_TABLE(var, dep1, dep2) \
    do { \
        \
        ASM_KEEP_DEP_NV(var, dep2); \
        (var) = (u8 **)((u8 *)(var) + 0x3160); \
    } while (0)
#endif

s32 func_807B0B3C(void *object, s32 arg1, void *arg2) {
    u8 *scratch;
    register u8 *colors ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *verts;
    register u32 mask;
    u8 *arg0;
    register s32 in_a1 ASM_REG("$5") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register void *in_a2 ASM_REG("$6") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register s32 magic ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    StackLocals local;
    register u32 work ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 count;
    register s32 average ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 offset ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 constant ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    void *ca0;
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 color;
    u8 *p;
    u8 *q;
    register u8 *prim ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register u8 *initial ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *next;
    register u16 half ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 coord;

    (void)&object;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    colors = scratch;
    ASM_KEEP_NV(colors);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    colors = (u8 *)((u32)colors | 0x40);
    verts = scratch;
    ASM_KEEP_NV(verts);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    verts = (u8 *)((u32)verts | 0x80);
    magic = 0x66666667;
    mask = 0xFFFFFF;
    local.sp1C = magic;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    initial = (u8 *)object;
    arg0 = initial;
    if ((((S_807B0B3C_0 *)initial)->unk_06 >> 10) & 1) {
        u8 *a3p;
        u8 *a0p;
        register u32 a2v ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 a0h ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 a1v ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u16 v0h;
        register s32 product_hi ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        SignedProduct product;

        count = 0;
        a3p = scratch;
loop_a:
        v1 = count * 2;
        v0h = ((S_807B0B3C_1 *)arg0)->unk_00.u;
        local.sp18 = v1;
        ((S_807B0B3C_2 *)a3p)->unk_08 = v0h;
        ((S_807B0B3C_2 *)a3p)->unk_00 = v0h;
        a0p = a3p + 8;
        v1 = ((S_807B0B3C_1 *)arg0)->unk_02.s;
        if (count < 2) {
            register s32 implicit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            implicit = v1 - 0x20;
            ASM_TAILSLOT_PIN_TIED(implicit);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_800F83EC(a0p, in_a1, in_a2, a3p);
        }
        v0h = v1 + 0x20;
        ASM_KEEP(v0h);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_807B0B3C_3 *)a0p)->unk_02.v = v0h;
        a2v = local.sp18;
        v0h = ((S_807B0B3C_3 *)a0p)->unk_02.v;
        a2v <<= 3;
        ((S_807B0B3C_2 *)a3p)->unk_02 = v0h;
        a0h = ((S_807B0B3C_1 *)arg0)->unk_04;
        a2v += (u32)scratch;
        ((S_807B0B3C_4 *)((u8 *)a2v))->unk_0C = a0h;
        v0h = ((S_807B0B3C_1 *)arg0)->unk_08.u16;
        magic = local.sp1C;
        a1v = (s16)v0h;
        product.value = (long long)a1v * magic;
        count++;
        a3p += 0x10;
        ASM_KEEP_NV(product.words.hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        product_hi = product.words.hi;
        ASM_KEEP_NV(product_hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        v1 = product_hi >> 1;
        v1 -= a1v >> 31;
        a1v -= v1 * 5;
        a0h = a0h + a1v - 0x36;
        ((S_807B0B3C_4 *)((u8 *)a2v))->unk_04 = a0h;
        if (count < 2) {
            goto loop_a;
        }
        average = 0;
        ASM_TAILSLOT_PIN_TIED(average);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        return func_800F8500(a0h, a1v, (void *)a2v, a3p);
    }

    {
        s32 a2p;
        u8 *a0p;
        register s32 a0h ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 t0p;
        s32 a3end;
        register s32 a1v ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register s32 v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 v0h ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 product_hi ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        SignedProduct product;

        a2p = (s32)scratch;
        t0p = (s32)scratch + 0x10;
        a3end = (s32)scratch + 0x20;
loop_b:
        v1 = ((S_807B0B3C_1 *)arg0)->unk_00.s;
        a0p = (u8 *)a2p + 8;
        if (a2p < t0p) {
            register s32 implicit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            implicit = v1 - 0x20;
            ASM_TAILSLOT_PIN_TIED(implicit);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            return func_800F8488(a0p, in_a1, (void *)a2p, (void *)a3end);
        }
        v0h = v1 + 0x20;
        ((S_807B0B3C_5 *)((u8 *)a2p))->unk_08 = v0h;
        ASM_KEEP_NV(a0p);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        v0h = ((S_807B0B3C_3 *)a0p)->unk_00.v;
        ((S_807B0B3C_5 *)((u8 *)a2p))->unk_00 = v0h;
        v0h = ((S_807B0B3C_1 *)arg0)->unk_02.u;
        v1 = (s32)((u32)8 + (u32)a2p);
        ((S_807B0B3C_6 *)((u8 *)v1))->unk_02 = v0h;
        ((S_807B0B3C_5 *)((u8 *)a2p))->unk_02 = v0h;
        a0h = ((S_807B0B3C_1 *)arg0)->unk_04;
        ((S_807B0B3C_6 *)((u8 *)v1))->unk_04 = a0h;
        v0h = ((S_807B0B3C_1 *)arg0)->unk_08.u16;
        magic = local.sp1C;
        a1v = (s16)v0h;
        product.value = (long long)a1v * magic;
        ASM_KEEP_NV(product.words.hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        product_hi = product.words.hi;
        ASM_KEEP_NV(product_hi);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        v1 = product_hi >> 1;
        v1 -= a1v >> 31;
        a1v -= v1 * 5;
        a0h = a0h + a1v - 0x36;
        ((S_807B0B3C_5 *)((u8 *)a2p))->unk_04 = a0h;
        a2p += 0x10;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        average = 0;
        if (a2p < a3end) {
            goto loop_b;
        }
    }

    count = average;
    q = verts;
    p = scratch;
    do {
        register void *call_a0 ASM_REG("$4") = p;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register void *call_a1 ASM_REG("$5") = q;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register void *call_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        void *call_a3;
        register s32 before ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 result;

        call_a2 = &local.sp18;
        call_a3 = call_a2;
        result = func_80065420(call_a0, call_a1, call_a2, call_a3);
        before = average - 8;
        average = before + result;
        q += 4;
        count++;
        p += 8;
    } while (count < 4);

    {
        s32 rounded;

        rounded = average;
        if (average < 0) {
            rounded = average + 3;
        }
        average = rounded >> 2;
        ASM_KEEP_NV(average);
    }

    {
        register u8 **globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *rootp;

        globalp = &D_80083160;
        ASM_KEEP_NV(globalp);
        rootp = *globalp;
        prim = *(u8 **)(rootp + 0x8D0);
        ca0 = (void *)prim;
        ASM_KEEP_NV(ca0);
        *(u8 **)(rootp + 0x8D0) = prim + 0x34;
    }
    constant = 0xA0A0A0;
    ((S_807B0B3C_7 *)prim)->unk_1C = 0;
    ((S_807B0B3C_7 *)prim)->unk_04 = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_807B0B3C_7 *)prim)->unk_28 = constant;
    ((S_807B0B3C_7 *)prim)->unk_10 = constant;
    func_8006671C(ca0, constant);
    func_80066640(prim, 1);
    ((S_807B0B3C_7 *)prim)->unk_18.at02.v = func_80066460(0, 1, 0x280, 0x100);
    {
        u16 texture;
        s32 firstvert;

        texture = func_8006649C(0x90, 0x1F7);
        firstvert = ((S_807B0B3C_8 *)verts)->unk_00;
        ((S_807B0B3C_7 *)prim)->unk_0C.at02.v = texture;
        ((S_807B0B3C_7 *)prim)->unk_08 = firstvert;
    }
    ((S_807B0B3C_7 *)prim)->unk_14 = ((S_807B0B3C_8 *)verts)->unk_04;
    ((S_807B0B3C_7 *)prim)->unk_20 = ((S_807B0B3C_8 *)verts)->unk_08;
    ((S_807B0B3C_7 *)prim)->unk_2C = ((S_807B0B3C_8 *)verts)->unk_0C;

    work = ((S_807B0B3C_1 *)arg0)->unk_08.u16 & 7;
    value = (work & 3) << 5;
    color = value - 0x80;
    value -= 0x61;
    work = (work >> 2) << 5;
    ((S_807B0B3C_7 *)prim)->unk_30 = value;
    ((S_807B0B3C_7 *)prim)->unk_24 = value;
    value = work - 0x40;
    work -= 0x21;
    ((S_807B0B3C_7 *)prim)->unk_31 = value;
    ((S_807B0B3C_7 *)prim)->unk_18.at01.v = value;
    ((S_807B0B3C_7 *)prim)->unk_18.at00.v = color;
    ((S_807B0B3C_7 *)prim)->unk_0C.at00.v = color;
    ((S_807B0B3C_7 *)prim)->unk_25 = work;
    ((S_807B0B3C_7 *)prim)->unk_0C.at01.v = work;

    if ((u32)average < 0x1E0U) {
        register u8 **next_globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        {
            register u8 **globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register u8 *rootp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u32 highmask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u32 primword;
            u32 bucket;

            globalp = &D_80083160;
            ASM_KEEP_NV(globalp);
            work = average * 4;
            rootp = *globalp;
            highmask = 0xFF000000;
            primword = ((S_807B0B3C_7 *)prim)->unk_00;
            rootp = (u8 *)((u32)work + (u32)rootp);
            primword &= highmask;
            LOAD_GLOBAL_PAGE(next_globalp);
            bucket = ((S_807B0B3C_9 *)rootp)->unk_B0;
            FINISH_GLOBAL_TABLE(next_globalp, bucket, primword);
            ASM_KEEP_NV(next_globalp);
            ((S_807B0B3C_7 *)prim)->unk_00 = primword | (bucket & mask);
        }
        {
            u8 *rootp;
            u8 *entryp;
            register u32 highmask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            rootp = *next_globalp;
            highmask = 0xFF000000;
            entryp = (u8 *)((u32)work + (u32)rootp);
            ((S_807B0B3C_10 *)entryp)->unk_B0 =
                (((S_807B0B3C_10 *)entryp)->unk_B0 & highmask) |
                ((u32)prim & mask);
            ASM_KEEP(prim);
        }
    }

    {
        register u8 *a0p ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *a1p ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */

        count = 3;
        a1p = colors + 0xC;
        a0p = scratch + 0x18;
        do {
            coord = ((S_807B0B3C_1 *)arg0)->unk_00.s;
            if (count < 2) {
                ((S_807B0B3C_3 *)a0p)->unk_00.n = coord - 0x20;
            } else {
                ((S_807B0B3C_3 *)a0p)->unk_00.n = coord + 0x20;
            }
            coord = ((S_807B0B3C_1 *)arg0)->unk_02.s;
            if (count & 1) {
                ((S_807B0B3C_3 *)a0p)->unk_02.n = coord + 0x20;
            } else {
                ((S_807B0B3C_3 *)a0p)->unk_02.n = coord - 0x20;
            }
            count--;
            ((S_807B0B3C_3 *)a0p)->unk_04 = ((S_807B0B3C_1 *)arg0)->unk_04;
            a0p -= 8;
            value = (((S_807B0B3C_1 *)arg0)->unk_08.u8 & 3) * 8;
            ((S_807B0B3C_11 *)a1p)->unk_02 = value;
            ((S_807B0B3C_11 *)a1p)->unk_01 = value;
            ((S_807B0B3C_11 *)a1p)->unk_00 = value;
            a1p -= 4;
        } while (count >= 0);
    }

    coord = ((S_807B0B3C_1 *)arg0)->unk_06;
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
        register u8 *qq ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

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
        register u8 *qq ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        c3 = 3;
        qq = verts + 0xC;
        ASM_TAILSLOT_PIN_TIED(c3);
        ASM_TAILSLOT_PIN_TIED(qq);
        return func_800F87C8();
    }
    goto coord_C00;

coord_0:
    ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
    half = ((S_807B0B3C_1 *)arg0)->unk_02.u;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        u8 *dst;

        dst = scratch + 0x10;
        ASM_KEEP_NV(dst);
        ((S_807B0B3C_13 *)dst)->unk_02 = half;
    }
    ((S_807B0B3C_14 *)scratch)->unk_02 = half;
    return func_800F87C0();

coord_400:
    half = ((S_807B0B3C_1 *)arg0)->unk_00.u;
    ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
    ((S_807B0B3C_14 *)scratch)->unk_18 = half;
    ((S_807B0B3C_14 *)scratch)->unk_10 = half;
    return func_800F87C0();

coord_800:
    ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
    half = ((S_807B0B3C_1 *)arg0)->unk_02.u;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        u8 *dst;

        dst = scratch + 0x18;
        ASM_KEEP_NV(dst);
        ((S_807B0B3C_13 *)dst)->unk_02 = half;
    }
    ((S_807B0B3C_14 *)scratch)->unk_0A = half;
    return func_800F87C0();

coord_C00:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    half = ((S_807B0B3C_1 *)arg0)->unk_00.u;
    ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
    ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
    ((S_807B0B3C_14 *)scratch)->unk_08 = half;
    ((S_807B0B3C_14 *)scratch)->unk_00 = half;

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    count = 3;
    q = verts + 0xC;
    p = scratch + 0x18;
    do {
        register void *call_a0 ASM_REG("$4") = p;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register void *call_a1 ASM_REG("$5") = q;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        register void *call_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        void *call_a3;

        call_a2 = &local.sp18;
        call_a3 = call_a2;
        func_80065420(call_a0, call_a1, call_a2, call_a3);
        q -= 4;
        count--;
        p -= 8;
    } while (count >= 0);

    if ((u32)average < 0x1E0U) {
        s32 one;
        s32 zero2;
        s32 zero3;
        register u8 **next_globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        {
            register u8 **globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u8 *rootp;

            LOAD_SPLIT_GLOBAL(globalp);
            ASM_KEEP_NV(globalp);
            rootp = *globalp;
            prim = *(u8 **)(rootp + 0x8D0);
            {
            s32 firstcolor;

            firstcolor = ((S_807B0B3C_12 *)colors)->unk_00.s;
            *(u8 **)(rootp + 0x8D0) = prim + 0x24;
            ((S_807B0B3C_7 *)prim)->unk_04 = firstcolor;
            }
        }
        ((S_807B0B3C_7 *)prim)->unk_0C.at00u.v = ((S_807B0B3C_12 *)colors)->unk_04.s;
        ((S_807B0B3C_7 *)prim)->unk_14 = ((S_807B0B3C_12 *)colors)->unk_08.s;
        ((S_807B0B3C_7 *)prim)->unk_1C = ((S_807B0B3C_12 *)colors)->unk_0C.s;
        func_80066708(prim);
        func_80066640(prim, 1);
        {
            register u8 **globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register u8 *rootp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u32 highmask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 vertex;
            u32 primword;
            u32 bucket;

            LOAD_GLOBAL_PAGE(globalp);
            vertex = ((S_807B0B3C_8 *)verts)->unk_00;
            primword = ((S_807B0B3C_7 *)prim)->unk_00;
            FINISH_GLOBAL_TABLE(globalp, vertex, primword);
            ASM_KEEP_NV(globalp);
            ((S_807B0B3C_7 *)prim)->unk_08 = vertex;
            vertex = ((S_807B0B3C_8 *)verts)->unk_04;
            offset = average * 4;
            ((S_807B0B3C_7 *)prim)->unk_10 = vertex;
            vertex = ((S_807B0B3C_8 *)verts)->unk_08;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            work = 0;
            ASM_KEEP_NV(work);
            ((S_807B0B3C_7 *)prim)->unk_18.at00u.v = vertex;
            vertex = ((S_807B0B3C_8 *)verts)->unk_0C;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            one = 1;
            ASM_KEEP_NV(one);
            ((S_807B0B3C_7 *)prim)->unk_20 = vertex;
            rootp = *globalp;
            highmask = 0xFF000000;
            primword &= highmask;
            LOAD_GLOBAL_PAGE(next_globalp);
            rootp = (u8 *)((u32)offset + (u32)rootp);
            bucket = ((S_807B0B3C_9 *)rootp)->unk_B0;
            FINISH_GLOBAL_TABLE(next_globalp, bucket, primword);
            ASM_KEEP_NV(next_globalp);
            ((S_807B0B3C_7 *)prim)->unk_00 = primword | (bucket & mask);
        }
        {
            register u8 *entryp ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register u32 highmask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u32 entryword;

            entryp = *next_globalp;
            highmask = 0xFF000000;
            entryp = (u8 *)((u32)offset + (u32)entryp);
            entryword =
                (((S_807B0B3C_10 *)entryp)->unk_B0 & highmask) |
                ((u32)prim & mask);
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            next_globalp = &D_80083160;
            ASM_KEEP_NV(next_globalp);
            ((S_807B0B3C_10 *)entryp)->unk_B0 = entryword;
            entryp = *next_globalp;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            zero2 = work;
            ASM_KEEP_NV(zero2);
            prim = *(u8 **)(entryp + 0x8D0);
            zero3 = work;
            *(u8 **)(entryp + 0x8D0) = prim + 0xC;
        }
        half = func_80066460(work, one, zero2, zero3);
        {
            s32 z;
            void *pa;

            pa = (void *)prim;
            z = 0;
            func_80067F20(pa, z, z, half, 0);
        }

        {
            register u8 **globalp ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register u8 *entryp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u32 highmask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u32 primword;
            u32 bucket;

            globalp = &D_80083160;
            ASM_KEEP_NV(globalp);
            entryp = *globalp;
            highmask = 0xFF000000;
            primword = ((S_807B0B3C_7 *)prim)->unk_00;
            entryp = (u8 *)((u32)offset + (u32)entryp);
            primword &= highmask;
            LOAD_GLOBAL_PAGE(next_globalp);
            bucket = ((S_807B0B3C_10 *)entryp)->unk_B0;
            FINISH_GLOBAL_TABLE(next_globalp, bucket, primword);
            ASM_KEEP_NV(next_globalp);
            ((S_807B0B3C_7 *)prim)->unk_00 = primword | (bucket & mask);
        }
        {
            u8 *rootp;
            register u32 highmask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            rootp = *next_globalp;
            highmask = 0xFF000000;
            offset += (s32)rootp;
            ((S_807B0B3C_15 *)((u8 *)offset))->unk_B0 =
                (((S_807B0B3C_15 *)((u8 *)offset))->unk_B0 & highmask) |
                ((u32)prim & mask);
        }
    }

    initial = (u8 *)object;
    next = ((S_807B0B3C_0_pre *)initial)[-1].unk_00;
    if (next != 0) {
        next += 0x20;
        object = next;
        return func_800F8394(next);
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    {
        register s32 zr ASM_REG("$0");

        return zr;
    }
}
