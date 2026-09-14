#include "common.h"

extern s32 func_800A6D30(u32, u32, s32, s32);


/* Return a 16-bit random value within the inclusive bounds. */
s32 func_800A6DA4(u32 bound_a, u32 bound_b, s32 rng_arg2, s32 rng_arg3) {
    u32 result;
    u32 range;
    u32 random_value;
    u32 upper;
    u32 lower;

    lower = bound_a;
    upper = bound_b;
    if (upper < lower) {
        random_value = upper;
        upper = lower;
        lower = random_value;
    }
    random_value = func_800A6D30(bound_a, bound_b, rng_arg2, rng_arg3) & 0xFFFF;
    range = (upper - lower) + 1;
    result = ((random_value % range) + lower) & 0xFFFF;
    return result;
}
