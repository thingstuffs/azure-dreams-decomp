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
#define MULT_HI(a, b) (0)

s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
void func_800B1F10(s32 arg0, s32 arg1);
void func_800B1F48(s32 arg0, s32 arg1, s32 arg2);
void func_800B204C(void);

void func_800B1F80(s8 *arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_ret;
    s32 temp_s1;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + ((M2C_FIELD(arg0, s32 *, 0xC) * 0x10) + 0x1C);
    temp_ret = func_80049E1C(M2C_FIELD(temp_s0, s32 *, 8), arg1, M2C_FIELD(temp_s0, s32 *, 0xC));
    temp_v0 = temp_ret;
    if (temp_v0 >= M2C_FIELD(temp_s0, s32 *, 0xC)) {
        M2C_FIELD(temp_s0, s32 *, 8) = 0;
        func_800B204C();
        return;
    }
    if (temp_v0 != M2C_FIELD(temp_s0, s32 *, 8)) {
        M2C_FIELD(temp_s0, s32 *, 8) = temp_v0;
        temp_a1 = M2C_FIELD(arg0, s32 *, 0xC);
        temp_s1 = temp_ret / 10;
        func_800B1F48(*((s32 *)((s8 *)arg0 + (temp_a1 * 4))), temp_a1, temp_v0);
        if (temp_s1 != M2C_FIELD(temp_s0, s32 *, 0)) {
            M2C_FIELD(temp_s0, s32 *, 0) = temp_s1;
            temp_a1_2 = M2C_FIELD(arg0, s32 *, 0xC);
            func_800B1F10(*((s32 *)((s8 *)arg0 + (temp_a1_2 * 4))), temp_a1_2);
        }
    }
}
