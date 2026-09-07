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

extern s32 func_80049E1C();
extern M2C_UNK func_800B1F10();
extern M2C_UNK func_800B1F48();

void func_800B2068(void *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_ret;
    void *temp_s0;

    temp_s0 = arg0 + ((M2C_FIELD(arg0, s32 *, 0xC) * 0x10) + 0x1C);
    temp_ret = func_80049E1C(M2C_FIELD(temp_s0, s32 *, 8) - 1, 1, M2C_FIELD(temp_s0, s32 *, 0xC));
    M2C_FIELD(temp_s0, s32 *, 8) = temp_ret;
    M2C_FIELD(temp_s0, s32 *, 0) = (s32) (temp_ret / 10);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0xC);
    func_800B1F48(*((s32 *)arg0 + temp_a1), temp_a1);
    temp_a1_2 = M2C_FIELD(arg0, s32 *, 0xC);
    func_800B1F10(*((s32 *)arg0 + temp_a1_2), temp_a1_2);
    temp_a1_3 = M2C_FIELD(arg0, s32 *, 0x18);
    func_800B1F10(*((s32 *)arg0 + temp_a1_3), temp_a1_3);
}
