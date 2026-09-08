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


typedef struct S_818C2FAC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C2FAC_0;   /* (void *)obj in func_818C2FAC */

typedef struct S_818C2FAC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818C2FAC_1;   /* work in func_818C2FAC */

typedef struct S_818C2FAC_2 {
    u8 pad_00[0xC];
    volatile u8 unk_0C;
    volatile u8 unk_0D;
    volatile u8 unk_0E;
    u8 pad_0F[0x1];
    volatile u16 unk_10;
    s16 unk_12;
    volatile u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C2FAC_2;   /* (void *)temp in func_818C2FAC */

s32 func_818C2FAC(void *arg0, void *arg1, s32 arg2)
{
    s32 angle;
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
    uptr input = (uptr)arg0;
    uptr source = (uptr)arg1;
    s32 a0i;
    register s32 coord ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register uptr obj ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register uptr temp ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 pa0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    register u32 pg0 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 pa1;
    register u32 pg1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 prod;
    s32 magic;
    S_818C2FAC_1 *work;

    a0i = 0x212;
    ASM_KEEP_NV(a0i);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    coord = arg2;
    obj = (uptr)func_8003FC64(a0i);
    ASM_KEEP(source);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (obj != NULL) {

    ((S_818C2FAC_0 *)((void *)obj))->unk_10 = D_80024710;
    ((S_818C2FAC_0 *)((void *)obj))->unk_20 = (*(s32 *)((u8 *)((void *)input) + 0));
    work = (u8 *)obj + 0x20;
    work->unk_04 = 0;
    work->unk_06 = 0;

    temp = (uptr)((S_818C2FAC_0 *)((void *)obj))->unk_0C;
    flags = ((S_818C2FAC_2 *)((void *)temp))->unk_14;
    ((S_818C2FAC_2 *)((void *)temp))->unk_0E = 0x80;
    ((S_818C2FAC_2 *)((void *)temp))->unk_0D = 0x80;
    ((S_818C2FAC_2 *)((void *)temp))->unk_0C = 0x80;
    mode = ((S_818C2FAC_2 *)((void *)temp))->unk_10;
    flags |= 0xC;
    mode |= 0x60;
    ((S_818C2FAC_2 *)((void *)temp))->unk_14 = flags;
    flags |= 0x100;
    ((S_818C2FAC_2 *)((void *)temp))->unk_10 = mode;
    ((S_818C2FAC_2 *)((void *)temp))->unk_14 = flags;

    angle = (*(s16 *)((u8 *)((void *)input) + 0x12));
    biased = angle;
    if (angle < 0) {
        biased = angle + 3;
    }
    kind = angle - ((biased >> 2) * 4);

    if (kind == 1) goto case1;
    if (kind >= 2) goto tree2;
    pa0 = (s32)temp;
    if (kind == 0) goto case0;
#ifndef NON_MATCHING
    ASM_KEEP(pa0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    pg0 = 0x800E0000;
    ASM_PAGEBASE_PIN(pg0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_800248CC();
#else
    func_800248CC((void *)temp, 0x800E0000);
#endif
tree2:
    if (kind == 2) goto case2;
    pa1 = (s32)temp;
    if (kind == 3) goto case3;
#ifndef NON_MATCHING
    ASM_KEEP(pa1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    pg1 = 0x800E0000;
    ASM_PAGEBASE_PIN(pg1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_800248CC();
#else
    func_800248CC((void *)temp, 0x800E0000);
#endif
case0:
    {
        s32 vpin0;
        vpin0 = 0x7DCF;
        ASM_TAILSLOT_PIN(vpin0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800248C0();
    }
case1:
    {
        s32 vpin1;
        vpin1 = 0x7E00;
        ASM_TAILSLOT_PIN(vpin1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800248C0();
    }
case2:
    {
        s32 vpin2;
        vpin2 = 0x7E01;
        ASM_TAILSLOT_PIN(vpin2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800248C0();
    }
case3:
    ((S_818C2FAC_2 *)((void *)temp))->unk_12 = 0x7E02;
    ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    {
        s32 A0p;
        u8 *A1p;
        A0p = (s32)temp;
        A1p = D_800DEC70;
        func_8003DB94(A0p, A1p, 0);
    }
    random = func_80069EF8();
    reduced = random;
    if (random < 0) {
        reduced = random + 0xFFF;
    }
    ((S_818C2FAC_2 *)((void *)temp))->unk_1A = random - ((reduced >> 12) << 12);
    ((S_818C2FAC_2 *)((void *)temp))->unk_1E = 0x1000;
    ((S_818C2FAC_2 *)((void *)temp))->unk_1C = 0x1000;
    func_8004491C((void *)obj, D_80045340);

    input = (uptr)((S_818C2FAC_0 *)((void *)obj))->unk_08;
    pair01 = (*(s64_local *)((u8 *)((void *)source) + 0));
    copy2 = (*(s32 *)((u8 *)((void *)source) + 8));
    copy3 = (*(s32 *)((u8 *)((void *)source) + 0xC));
    (*(s64_local *)((u8 *)((void *)input) + 0)) = pair01;
    (*(s32 *)((u8 *)((void *)input) + 8)) = copy2;
    (*(s32 *)((u8 *)((void *)input) + 0xC)) = copy3;
    copy4 = (*(s32 *)((u8 *)((void *)source) + 0x10));
    copy5 = (*(s32 *)((u8 *)((void *)source) + 0x14));
    (*(s32 *)((u8 *)((void *)input) + 0x10)) = copy4;
    (*(s32 *)((u8 *)((void *)input) + 0x14)) = copy5;

    random = func_80069EF8();
    magic = 0x78787879;
    temp = (uptr)random;
    ASM_USE_NV(magic);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    coord = (s16)coord;
    temp = (uptr)((s32)temp % 17 + 0x20);
    h1 = func_800644B8(coord) >> 4;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp = (uptr)(s16)(s32)temp;
    {
        s32 sh1;
        prod = h1 * (s32)temp;
        sh1 = prod << 8;
        (*(s32 *)((u8 *)((void *)input) + 0)) += sh1;
    }
    {
        register s32 ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        h2 = func_80064584(coord) >> 4;
        ret = (s32)obj;
        prod = h2 * (s32)temp;
        delta = prod << 8;
        newv = (*(s32 *)((u8 *)((void *)input) + 4)) + delta;
        ASM_KEEP(ret);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        (*(s32 *)((u8 *)((void *)input) + 4)) = newv;
        func_800249E4(delta);
    }

    }
    {
        s32 rv;
        rv = 0;
        return rv;
    }
}
