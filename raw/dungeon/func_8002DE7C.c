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

M2C_UNK func_800C2E84(void *arg0, M2C_UNK arg1, M2C_UNK *arg2);
extern s8 D_80082660[];
extern M2C_UNK D_800CB570;
extern M2C_UNK D_800D694C;

void func_800CB5DC(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D694C);
    D_80082660[M2C_FIELD(arg0, s32 *, 0x60) * 8] = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800CB570;
    M2C_FIELD(arg0, M2C_UNK16 *, 0x6C) = 0xA;
}
