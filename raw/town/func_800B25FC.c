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
void func_800AF9C4(void *arg0);
extern M2C_UNK D_800AFD00[];

void func_800AFD5C(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x9C), s16 *, 6) = (s16) ((temp_v0 << 0xC) / 5);
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 8) + 1;
    M2C_FIELD(arg0, s32 *, 8) = temp_v0_2;
    if (temp_v0_2 < 6) {
    } else {
        M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800AFD00;
    }
    func_800AF9C4(arg0);
}
