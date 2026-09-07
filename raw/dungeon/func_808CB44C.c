#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

extern M2C_UNK D_80129728[16];
extern s32 D_801331A0;

void func_801238E4(void) {
    M2C_UNK *base;
    s32 **var_a0;
    s32 *temp_v1;
    s32 *var_a1;
    s32 var_a2;

    var_a2 = 0x10;
    var_a1 = &D_801331A0;
    base = D_80129728;
    var_a0 = (s32 **)(base + 0x10);
    do {
        temp_v1 = *var_a0;
        var_a0++;
        var_a2++;
        *temp_v1 = *var_a1;
        var_a1++;
    } while (var_a2 < 0x1C);
}
