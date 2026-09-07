#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;

s32 func_806D4ECC(void) {
    s8 sp10[2];

    sp10[1] = 0x17;
    sp10[0] = 5;
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), s32 (**)(s8 *), 0x50)(sp10) - M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x40), s32 *, 0x110);
}
