/* cfail-repair: tf7-phase1-cache-v3 */
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

extern struct {
    u8 *ptr;
    u8 pad[8];
} D_8001E950;
extern M2C_UNK D_8001F0D8;
extern M2C_UNK D_8001F18C;

s32 func_8001CF9C(void *arg0, s32 arg1) {
    M2C_UNK *sp[2];

    do { sp[0] = &D_8001F0D8; } while (0);
    sp[1] = &D_8001F18C;
    M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) = sp[D_8001E950.ptr[1]];
    return 0;
}
