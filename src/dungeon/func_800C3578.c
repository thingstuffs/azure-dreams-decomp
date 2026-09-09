#include "common.h"

extern s32 func_800A6D30(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_800A48F0(void *arg0, s32 arg1, s32 arg2);
extern void func_80099844(void *arg0, const void *arg1);
extern void func_800DC1B8(s32 arg0);

extern s32 D_800DCF10[];
extern u8 D_800E1A55[];

s32 func_800C8CD8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *entity = arg0;
    register s32 threshold ASM_REG("$17") = arg1; /* MATCH: preserve retail's entry save order after merging the threshold arms. */
    register s32 kind ASM_REG("$18") = arg2; /* MATCH: retain the kind save in the RNG call delay slot. */
    s32 random;
    s32 range;
    register s32 roll ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 threshold_shift ASM_REG("$2"); /* MATCH: retail merges the threshold shift in v0 at the shared tail. */
    register s32 signed_threshold ASM_REG("$4"); /* MATCH: retail keeps the signed threshold in a0 across both comparisons. */
    register s32 compare ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 rng;

    rng = func_800A6D30(arg0, arg1, arg2, arg3);
    range = *(u8 *)((u8 *)entity + 3);
    random = rng & 0xFFFF;
    if (range != 0) {
        s32 divisor = range;
        ASM_KEEP(divisor);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        roll = random % divisor;
        ASM_KEEP(random);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(roll);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        threshold_shift = (u32)threshold << 16;
    } else {
        roll = 0;
        threshold_shift = (u32)threshold << 16;
    }

    signed_threshold = threshold_shift >> 16;
    ASM_KEEP(signed_threshold);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    compare = roll < signed_threshold;
    if ((compare != 0) || (signed_threshold == 0xFF)) {
        ASM_SCHED_BARRIER(); /* MATCH: keep call arguments after the threshold guards. */
        if ((s16)func_800A48F0(entity, 2, (s8)kind) >= 0) {
            func_80099844(entity, D_800E1A55);
            if (*(u8 *)((u8 *)entity + 0x13) == 0) {
                func_800DC1B8(D_800DCF10[0]);
            }
            return 1;
        }
    }

    return 0;
}

/* MECHANISM: The 0x20 frame follows from raw args held in s0/s1/s2 and split RNG/range/result live ranges.
   Restored LEAD-22 tails place threshold<<16 and return 1 in the two continuation jump slots.
   ASM_UNDEF at the zero-result seam defeats beqz equivalence and retains retail's move v1,zero. */
