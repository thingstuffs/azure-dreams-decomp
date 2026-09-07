#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register void *p0 ASM_REG("$20") = arg0;
    register void *p1 ASM_REG("$22") = arg1;
    register void *p3 ASM_REG("$16") = arg3;
    register u16 *flags ASM_REG("$19");
    register u8 *page ASM_REG("$2");
    register s32 state ASM_REG("$18");
    s32 raw;
    u8 masked;

    masked = FIELD(p3, u8, 0x71);
    ASM_KEEP(masked);
    {
    register void *p2 ASM_REG("$21") = arg2;

    masked = (u8)(masked & 0x7F);
    FIELD(p3, u8, 0x71) = masked;
    ASM_KEEP(masked);
    page = (u8 *)0x80080000;
    ASM_KEEP(page);
    flags = (u16 *)(page + 0x3460);
    ASM_KEEP(flags);
    state = 0;

    if (flags[1] & 0x2000) {
        return -1;
    }

    raw = func_800A04F0(
        p3, FIELD(p2, u8, 0x24), FIELD(p2, u8, 0x25),
        FIELD(p3, s16, 0x2A));
    {
    register void *first_call0 ASM_REG("$4") = p3;
    register s32 hit ASM_REG("$17") = raw;

    if (func_800A2CB8(first_call0, hit) == 0) {
        return state;
    }
    if (flags[1] & 0x2000) {
        return -1;
    }
    if ((FIELD(p3, u16, 0x46) & 0x8000) == 0) {
        if (flags[1] & 8) {
            return -1;
        }
    }

    if ((u16)(0 - func_800A0134(hit, p3) + 0x40) >= 0x81U) {
        return state;
    }

    state = 1;
    if ((FIELD(p3, u16, 0x46) & 0x8000) == 0) {
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

    FIELD(p0, u8, 0x9B) = 0;
    FIELD(p0, s16, 0x96) = 0;
    if (hit != 0) {
        register void *call0 ASM_REG("$4") = p3;
        register void *call1 ASM_REG("$5") = p2;
        s32 angle;
        u8 count;

        FIELD(p0, volatile s32, 0x8C) = 0;
        FIELD(p0, volatile u8, 0x9A) = 0x11;
        angle = FIELD(call0, s16, 0x2A);
        FIELD(call0, volatile u8, 0x84) = 0x7C;
        count = FIELD(call0, volatile u8, 0x6D);
        FIELD(call0, volatile u8, 0x85) = 0;
        FIELD(call0, volatile u8, 0x6D) = (u8)(count - 1);
        func_8009C93C(call0, call1, angle, 1, 0);
    }

    ASM_KEEP(p0);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);
    ASM_KEEP(flags);
    ASM_KEEP(state);
    ASM_KEEP(hit);
    return hit;
    }
    }
}

/* MECHANISM: Pinned argument roles produce the 0x38 frame and s4/s6/s5/s0 holds.
   RMW seams plus a pinned 0x80080000 page emit v0->s3; a nested raw-return
   live range orders a0 before s1. Volatile tail stores retain the call ABI order. */
