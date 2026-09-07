#include "common.h"

extern s32 func_800A6D30(void);
extern s32 func_800A48F0(void *arg0, s32 arg1, s32 arg2);
extern void func_80099844(void *arg0, const void *arg1);
extern void func_800C8D28(void);
extern void func_800C8D94(void);
extern void func_800DC1B8(s32 arg0);

extern s32 D_800DCF10[];
extern u8 D_800E1A55[];

s32 func_800C8CD8(void *arg0, s32 arg1, s32 arg2) {
    void *entity = arg0;
    s32 threshold = arg1;
    s32 kind = arg2;
    s32 random;
    s32 range;
    register s32 roll ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 threshold_shift;
    s32 signed_threshold;
    register s32 compare ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 rng;

    rng = func_800A6D30();
    range = *(u8 *)((u8 *)entity + 3);
    random = rng & 0xFFFF;
    if (range != 0) {
        s32 divisor = range;
        ASM_KEEP(divisor);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        roll = random % divisor;
        ASM_KEEP(random);   /* MATCH pin: retail register colouring depends on it */
        ASM_KEEP(roll);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800C8D28();
        return (u32)threshold << 16;
    } else {
        roll = 0;
    }

    threshold_shift = (u32)threshold << 16;
    signed_threshold = threshold_shift >> 16;
    ASM_KEEP(signed_threshold);   /* MATCH pin: load-bearing for the whole function shape */
    compare = roll < signed_threshold;
    if ((compare != 0) || (signed_threshold == 0xFF)) {
        if ((s16)func_800A48F0(entity, 2, (s8)kind) >= 0) {
            func_80099844(entity, D_800E1A55);
            if (*(u8 *)((u8 *)entity + 0x13) == 0) {
                func_800DC1B8(D_800DCF10[0]);
            }
            func_800C8D94();
            return 1;
        }
    }

    return 0;
}

/* MECHANISM: The 0x20 frame follows from raw args held in s0/s1/s2 and split RNG/range/result live ranges.
   Restored LEAD-22 tails place threshold<<16 and return 1 in the two continuation jump slots.
   ASM_UNDEF at the zero-result seam defeats beqz equivalence and retains retail's move v1,zero. */
