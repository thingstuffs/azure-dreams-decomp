#include "common.h"

extern s32 func_800A6D30(void);

#ifdef NON_MATCHING
#define TF14_HOLD(var) ((void)0)
#define TF14_KEEP(var) ((void)0)
#else
#define TF14_HOLD(var) __asm__ __volatile__("" : : "r"(var))
#define TF14_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

s32 func_800A6DA4(u32 arg0, u32 arg1) {
    register u32 range ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u32 result;
    u32 temp_v0;
    u32 var_s0;
    u32 var_s1;

    var_s1 = arg0;
    var_s0 = arg1;
    if (var_s0 < var_s1) {
        TF14_KEEP(var_s0);
        temp_v0 = var_s0;
        var_s0 = var_s1;
        var_s1 = temp_v0;
    }
    result = func_800A6D30() & 0xFFFF;
    range = (var_s0 - var_s1) + 1;
    TF14_HOLD(range);
    result %= range;
    TF14_HOLD(var_s0);
    result += var_s1;
    return result & 0xFFFF;
}
