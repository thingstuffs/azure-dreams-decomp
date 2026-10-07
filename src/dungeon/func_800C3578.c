#include "common.h"

extern s32 func_800A6D30(void);
extern s32 func_800A48F0(void *ptr, s32 value, s32 kind);
extern void func_80099844(void *ptr, const void *data);
extern void func_800DC1B8(s32 value);

extern s32 D_800DCF10[];
extern u8 D_800E1A55[];

/* Apply an entity effect when a random roll passes its threshold. */
s32 func_800C8CD8(void *ptr, s32 threshold_input, s32 kind_input) {
    s32 value;
    u16 threshold = threshold_input;
    s16 kind = kind_input;
    s32 roll;
    register s32 signed_threshold;
    s32 rng_result;

    rng_result = func_800A6D30();
    value = *(u8 *)((u8 *)ptr + 3);
    signed_threshold = rng_result & 0xFFFF;
    if (value != 0) {
        s32 divisor = (*(u32 *)ptr) >> 24;
        roll = signed_threshold % divisor;
    } else {
        roll = 0;
    }

    signed_threshold = ((s32)((u32)threshold << 16)) >> 16;
    if ((((s32)(roll < signed_threshold)) != 0) || (signed_threshold == 0xFF)) {
        if ((s16)func_800A48F0(ptr, 2, (s8)kind) >= 0) {
            func_80099844(ptr, D_800E1A55);
            if (*(u8 *)((u8 *)ptr + 0x13) == 0) {
                func_800DC1B8(D_800DCF10[0]);
            }
            return 1;
        }
    }

    return 0;
}
