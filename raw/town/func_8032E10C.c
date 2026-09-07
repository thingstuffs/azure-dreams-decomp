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

extern u8 D_80016000[0x10];

s32 func_8001890C(void) {
    s8 sp10[2];

    sp10[1] = 0x17;
    sp10[0] = 5;
    return (s32) M2C_FIELD(M2C_FIELD(M2C_FIELD(D_80016000, void **, 0), void **, 0x40), u32 *, 0x110) >= M2C_FIELD(M2C_FIELD(M2C_FIELD(D_80016000, void **, 0), void **, 0x20), u32 (**)(s8 *), 0x50)(sp10);
}
