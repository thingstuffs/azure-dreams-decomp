#include "common.h"

extern s32 func_800A6D30(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_800A48F0(void *arg0, s32 arg1, s32 arg2);
extern void func_80099844(void *arg0, const void *arg1);
extern void func_800DC1B8(s32 arg0);

extern s32 D_800DCF10[];
extern u8 D_800E1A55[];

/* Apply an entity effect when a random roll passes its threshold. */
s32 func_800C8CD8(void *entity_arg, s32 threshold_arg, s32 kind_arg, s32 rng_arg) {
    u16 threshold = threshold_arg;
    s16 kind = kind_arg;
    s32 roll;
    register s32 signed_threshold;
    s32 rng_result;

    rng_result = func_800A6D30(entity_arg, threshold_arg, kind_arg, rng_arg);
    rng_arg = *(u8 *)((u8 *)entity_arg + 3);
    signed_threshold = rng_result & 0xFFFF;
    if (rng_arg != 0) {
        s32 divisor = rng_arg;
        ASM_KEEP(divisor);
        roll = signed_threshold % divisor;
    } else {
        roll = 0;
    }

    signed_threshold = ((s32)((u32)threshold << 16)) >> 16;
    if ((((s32)(roll < signed_threshold)) != 0) || (signed_threshold == 0xFF)) {
        if ((s16)func_800A48F0(entity_arg, 2, (s8)kind) >= 0) {
            func_80099844(entity_arg, D_800E1A55);
            if (*(u8 *)((u8 *)entity_arg + 0x13) == 0) {
                func_800DC1B8(D_800DCF10[0]);
            }
            return 1;
        }
    }

    return 0;
}
