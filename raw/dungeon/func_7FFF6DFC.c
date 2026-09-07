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

M2C_UNK func_80094984();
M2C_UNK func_80094C1C();
extern M2C_UNK D_80092A84;
extern M2C_UNK D_800D0130;

void func_8009455C(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    M2C_FIELD(arg0, s16 *, 0x3E) = 6;
    func_80094C1C(arg0, arg1, arg2, arg3);
    func_80094984(&D_800D0130, arg0, arg2);
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_80092A84;
}
