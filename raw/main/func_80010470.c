#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80023470(void *arg0) {
    s32 var_v1;
    void *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    do {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1C8), s8 **, 4), s16 *, 8) = 0x24;
        *M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1C8), s8 **, 4) = 0x68;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1C8), s8 **, 4), s8 *, 1) = 0x68;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1C8), s8 **, 4), s8 *, 2) = 0x60;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1A8), void **, 4), s16 *, 8) = 9;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1B8), void **, 4), s16 *, 8) = 0x42;
        var_v1 += 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1D8), void **, 4), s16 *, 8) = 0x8F;
        var_a0 += 4;
    } while (var_v1 < 3);
}
