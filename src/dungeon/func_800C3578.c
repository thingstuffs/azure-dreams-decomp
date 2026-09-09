#include "common.h"

extern s32 func_800A6D30(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_800A48F0(void *arg0, s32 arg1, s32 arg2);
extern void func_80099844(void *arg0, const void *arg1);
extern void func_800DC1B8(s32 arg0);

extern s32 D_800DCF10[];
extern u8 D_800E1A55[];

/* Apply an entity effect when a random roll passes its threshold. */
s32 func_800C8CD8(void *entity_arg, s32 threshold_arg, s32 kind_arg, s32 rng_arg) {
    void *entity = entity_arg;
    register s32 threshold ASM_REG("$17") = threshold_arg;
    register s32 kind ASM_REG("$18") = kind_arg;
    s32 random_value;
    s32 roll_range;
    register s32 roll ASM_REG("$3");
    register s32 shifted_threshold ASM_REG("$2");
    register s32 signed_threshold;
    register s32 below_threshold ASM_REG("$2");
    s32 rng_result;

    rng_result = func_800A6D30(entity_arg, threshold_arg, kind_arg, rng_arg);
    roll_range = *(u8 *)((u8 *)entity + 3);
    random_value = rng_result & 0xFFFF;
    if (roll_range != 0) {
        s32 divisor = roll_range;
        ASM_KEEP(divisor);
        roll = random_value % divisor;
        ASM_KEEP(random_value);
        shifted_threshold = (u32)threshold << 16;
    } else {
        roll = 0;
        shifted_threshold = (u32)threshold << 16;
    }

    signed_threshold = shifted_threshold >> 16;
    below_threshold = roll < signed_threshold;
    if ((below_threshold != 0) || (signed_threshold == 0xFF)) {
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
