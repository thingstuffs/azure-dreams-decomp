#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
typedef s32 M2C_UNK;
#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64(s32 a0);
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80046398;

void *func_800BDBD0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        func_8004491C(temp_v0, &D_80046398);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg1;
        M2C_FIELD(temp_v1, s16 *, 0x1A) = (s16) arg2;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x20) = 0x1000;
        M2C_FIELD(temp_v1, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_v1, s32 *, 8) = arg3;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, s32 *, 0) = M2C_FIELD(arg0, s32 *, 0);
        M2C_FIELD(temp_v1_2, s32 *, 4) = M2C_FIELD(arg0, s32 *, 4);
        M2C_FIELD(temp_v1_2, s32 *, 8) = M2C_FIELD(arg0, s32 *, 8);
    }
    return temp_v0;
}
