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

void func_800DCA88(void *arg0, s32 arg1) {
    if (arg1 != 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 8) = -0x8C;
    } else {
        M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 8) = -0x22;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xA) = -0x52;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xC) = 0x200;
}
