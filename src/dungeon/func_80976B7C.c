#include "common.h"

typedef struct S_8017237C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
} S_8017237C_0;   /* p3 in func_8017237C */

typedef struct S_8017237C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017237C_1;   /* p2 in func_8017237C */

typedef struct S_8017237C_2 {
    u8 pad_00[0x8C];
    volatile s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    volatile u8 unk_9A;
    u8 unk_9B;
} S_8017237C_2;   /* p0 in func_8017237C */

typedef struct S_8017237C_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    volatile u8 unk_6D;
    u8 pad_6E[0x16];
    volatile u8 unk_84;
    volatile u8 unk_85;
} S_8017237C_3;   /* call0 in func_8017237C */



extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s16 func_800A2B5C(void *);
extern s16 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, void *, s32, s32);
extern s32 D_80083460;
extern u16 D_80083462;

s32 func_8017237C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    S_8017237C_2 *p0 = arg0;
    void *p1 = arg1;
    void *p3 = arg3;
    u16 *flags;
    u8 *page;
    register s32 state ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 raw;
    u8 masked;

    masked = ((S_8017237C_0 *)p3)->unk_71;
    {
    S_8017237C_1 *p2 = arg2;

    masked = (u8)(masked & 0x7F);
    ((S_8017237C_0 *)p3)->unk_71 = masked;
    ASM_KEEP(masked);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    page = (u8 *)0x80080000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    flags = (u16 *)(page + 0x3460);
    ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    state = 0;

    if (flags[1] & 0x2000) {
        return -1;
    }

    raw = func_800A04F0(
        p3, p2->unk_24, p2->unk_25,
        ((S_8017237C_0 *)p3)->unk_2A);
    {
    register void *first_call0 ASM_REG("$4") = p3;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 hit ASM_REG("$17") = raw;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    if (func_800A2CB8(first_call0, hit) == 0) {
        return state;
    }
    if (flags[1] & 0x2000) {
        return -1;
    }
    if ((((S_8017237C_0 *)p3)->unk_46 & 0x8000) == 0) {
        if (flags[1] & 8) {
            return -1;
        }
    }

    if ((u16)(0 - func_800A0134(hit, p3) + 0x40) >= 0x81U) {
        return state;
    }

    state = 1;
    if ((((S_8017237C_0 *)p3)->unk_46 & 0x8000) == 0) {
        if (D_80083462 & 8) {
            return -1;
        }
    }
    if (func_800A2B5C(p3) != 0) {
        return -1;
    }

    func_800C7930((u8 *)p3 - 0x20, p1, 8, 0x300);

    if (func_800A2B5C(p3) != 0) {
        return -1;
    }
    hit = state;

    p0->unk_9B = 0;
    p0->unk_96 = 0;
    if (hit != 0) {
        S_8017237C_3 *call0 = p3;
        void *call1 = p2;
        s32 angle;
        u8 count;

        p0->unk_8C = 0;
        p0->unk_9A = 0x11;
        angle = call0->unk_2A;
        call0->unk_84 = 0x7C;
        count = call0->unk_6D;
        call0->unk_85 = 0;
        call0->unk_6D = (u8)(count - 1);
        func_8009C93C(call0, call1, angle, 1, 0);
    }

    ASM_KEEP(p0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(hit);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    return hit;
    }
    }
}

/* MECHANISM: Pinned argument roles produce the 0x38 frame and s4/s6/s5/s0 holds.
   RMW seams plus a pinned 0x80080000 page emit v0->s3; a nested raw-return
   live range orders a0 before s1. Volatile tail stores retain the call ABI order. */
