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

extern void *func_8009C390();
extern s16 func_800C2AE8();
extern M2C_UNK func_800CBAE0();

void func_800CBB68(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8009C390(0, 0, 0, 0);
    if (temp_v0 != NULL) {
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        temp_s2 = M2C_FIELD(temp_v0, s32 *, 0xC);
        temp_s1 = (s8 *)temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s32 *, 0) = (s32)(arg1 << 0x10);
        M2C_FIELD(temp_s0, s32 *, 4) = (s32)(arg2 << 0x10);
        M2C_FIELD(temp_s0, s32 *, 8) = 0xFF000000;
        M2C_FIELD(temp_s0, s16 *, 0xA) = func_800C2AE8(temp_s0);
        M2C_FIELD(temp_s1, s8 *, 0x96) = arg0;
        func_800CBAE0(temp_s1, temp_s0, temp_s2);
    }
}
