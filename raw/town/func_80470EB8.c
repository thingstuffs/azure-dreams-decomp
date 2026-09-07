/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800186D8();
extern void *D_80016000[3];

s32 func_80017EB8(void *arg0) {
    s32 temp_s0;
    register s32 var_v0 ASM_REG("$2");
    register s32 var_v1 ASM_REG("$3");
    u8 temp_a0;
    u8 temp_a1;

    temp_a1 = M2C_FIELD(arg0, u8 *, 1);
    temp_a0 = M2C_FIELD(arg0, u8 *, 0);
    temp_s0 = M2C_FIELD((temp_a0 * 0x14) + M2C_FIELD(((temp_a1 * 0x14) + M2C_FIELD(M2C_FIELD(D_80016000[0], void **, 0x24), s32 *, 0x6C)), s32 *, 0xC), s16 *, 0);
    if (func_800186D8(temp_a0, temp_a1) != 0) {
        goto zero;
    }
    var_v0 = 0;
    var_v1 = temp_s0 - 8;
    if ((u32) var_v1 < 2U) {
        var_v0 = 1;
        goto done;
    }
zero:
    var_v0 = 0;
done:
    return var_v0;
}
