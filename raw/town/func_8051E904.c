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

extern s32 func_80017710(s32, M2C_UNK);
extern M2C_UNK func_80018A64();

s32 func_8051E904(s32 arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_s0;

    temp_s0 = func_80017710(arg0, arg2);
    func_80018A64(M2C_FIELD(arg1, s16 *, 0x18));
    return M2C_FIELD(((temp_s0 * 8) + arg0), s32 *, 4);
}
