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

s32 func_8004AC3C();
s32 func_8004DC14();
M2C_UNK func_800B0318();

void func_800AF674(void *arg0) {
    s32 sp10;
    s32 *temp_v1_2;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0x10;
    func_800B0318(M2C_FIELD(arg0, s32 *, 0xA8));
    var_s0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x10) * 0xA;
loop_1:
    if (var_s0 < M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x1C)) {
        temp_a0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 **, 0x20)[var_s0];
        temp_v0 = func_8004AC3C(temp_a0, &sp10);
        var_s0 += 1;
        temp_v0 = func_8004DC14(temp_v0, sp10);
        temp_v1_2 = M2C_FIELD(arg0, s32 **, 0xA8)[var_s1];
        var_s1 += 1;
        *temp_v1_2 = temp_v0;
        if (var_s1 < 0x1A) {
            goto loop_1;
        }
    }
}
