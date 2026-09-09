#include "common.h"

extern s32 func_800A6D30(u32, u32, s32, s32);

#ifdef NON_MATCHING
#define TF14_KEEP(var) ((void)0)
#else
#define TF14_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

/* Return a 16-bit random value within the inclusive bounds. */
s32 func_800A6DA4(u32 bound_a, u32 bound_b, s32 rng_arg2, s32 rng_arg3) {
    register u32 range ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u32 result;
    u32 swap_bound;
    u32 upper;
    u32 lower;

    lower = bound_a;
    upper = bound_b;
    if (upper < lower) {
        TF14_KEEP(upper);
        swap_bound = upper;
        upper = lower;
        lower = swap_bound;
    }
    result = func_800A6D30(bound_a, bound_b, rng_arg2, rng_arg3) & 0xFFFF;
    range = (upper - lower) + 1;
    result %= range;
    result += lower;
    return result & 0xFFFF;
}
