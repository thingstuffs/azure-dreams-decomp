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

extern s32 func_8001890C(void *obj);
extern M2C_UNK D_80016000[];
extern u32 D_8001C368[];

void func_800189BC(void) {
    void *temp_a0;

    temp_a0 = M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x38);
    M2C_FIELD(temp_a0, s32 *, 0x2D5C) = (u32) (M2C_FIELD(temp_a0, s32 *, 0x2D5C) - D_8001C368[0]);
    if (func_8001890C(temp_a0) != 0) {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(M2C_UNK, M2C_UNK), 0x4C)(0x10, 5);
    }
}
