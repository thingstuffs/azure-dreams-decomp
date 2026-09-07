#include "common.h"

typedef long long s64;
typedef unsigned long long u64;

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001A7E8();
extern s32 func_8001AC60();
extern void *D_8001E950;

s32 func_8001AC10(void *arg0, s32 arg1) {
    if (M2C_FIELD(D_8001E950, u8 *, 5) == 9) {
        M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) = func_8001A7E8();
        return 0;
    }
    func_8001AC60();
    return 1;
}
