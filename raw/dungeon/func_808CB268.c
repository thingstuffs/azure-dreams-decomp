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

extern s32 D_80126A88;
extern M2C_UNK D_80129728;

void func_80123700(void) {
    s8 *var_v0;
    s8 *var_a1;
    s32 temp_v0;
    s32 *temp_v1;
    s32 var_a2;
    s32 var_a3;
    void **var_a0;

    var_a2 = 0;
    var_a3 = 0x800;
    var_v0 = (s8 *)&D_80129728;
    var_a0 = (void **)(var_v0 + 0x38);
    var_a1 = (s8 *)&D_80126A88;
    do {
        temp_v1 = *(s32 **)var_a0;
        temp_v0 = *(s32 *)var_a1;
        var_a1 += 8;
        *temp_v1 = temp_v0;
        var_a2 += 1;
        M2C_FIELD(M2C_FIELD(*var_a0, void **, 8), s16 *, 2) = var_a3;
        var_a0 = (void **)((s8 *)((void **)((s8 *)var_a0 + 4)));
    } while (var_a2 < 0xE);
}
