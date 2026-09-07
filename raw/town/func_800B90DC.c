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

M2C_UNK func_800B6580();

void func_800B683C(void *arg0) {
    s32 *temp_v0;
    s32 var_a1;

    var_a1 = 0x14;
    do {
        temp_v0 = *(s32 **)((var_a1 * 4) + M2C_FIELD(arg0, void **, 0x98));
        var_a1 += 1;
        *temp_v0 = 0;
    } while (var_a1 < 0x16);
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), void ***, 0x5C) = arg0 + 0x18;
    func_800B6580(*M2C_FIELD(M2C_FIELD(arg0, void **, 0x98), void ***, 0x5C), 0);
}
