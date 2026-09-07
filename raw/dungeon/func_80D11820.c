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

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80170D2C;
extern M2C_UNK D_80170F0C;

void func_80171020(void *arg0, s16 arg1, s32 arg2, s32 arg3, volatile s32 arg4, volatile s32 arg5, volatile s32 arg6) {
    register s32 temp_s2 = arg4;
    register s32 temp_s3 = arg5;
    register s32 temp_s4 = arg6;
    register s16 temp_s5 = arg1;
    register s32 temp_s6 = arg2;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 == NULL) {
        return;
    }
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80170F0C;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + temp_s2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + temp_s3);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + temp_s4);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s32 *, 0x40) = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(temp_s0, s32 *, 0x44) = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(temp_s0, s32 *, 0x48) = (s32) (((rand() & 0x3FFF) - 0x6000) * 0x10);
        temp_a2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a2, s32 *, 0) = (s32) (M2C_FIELD(temp_a2, s32 *, 0) + (M2C_FIELD(temp_s0, s32 *, 0x40) * 2));
        temp_a2_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a2_2, s32 *, 4) = (s32) (M2C_FIELD(temp_a2_2, s32 *, 4) + (M2C_FIELD(temp_s0, s32 *, 0x44) * 2));
        M2C_FIELD(temp_s0, s32 *, 0x54) = 0x8000;
        M2C_FIELD(temp_s0, s16 *, 0x14) = temp_s5;
        M2C_FIELD(temp_s0, s16 *, 0x32) = 0x14;
        M2C_FIELD(temp_s0, s16 *, 0x34) = 0x14;
        func_8004491C(temp_v0, &D_80170D2C, temp_a2_2);
        M2C_FIELD(temp_v0, s32 *, 0x20) = temp_s6;
    M2C_FIELD(temp_s0, s32 *, 8) = temp_s6;
}
