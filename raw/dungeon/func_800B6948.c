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
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BBBE0;
extern M2C_UNK D_800BC054;

void *func_800BC0A8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    register s32 hold4 ASM_REG("$21") = arg4;
    register s32 hold5 ASM_REG("$23") = arg5;
    register s32 hold7 ASM_REG("$22") = arg7;
    void *temp_a0;
    void *temp_a1;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_8003FD64(0x202, &D_80083498);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800BBBE0;
        func_8004491C(temp_v0, &D_800BC054);
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
        temp_a1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0_2, s16 *, 2) = arg0;
        M2C_FIELD(temp_a1, s16 *, 4) = arg0;
        M2C_FIELD(temp_v0_2, s16 *, 6) = arg1;
        M2C_FIELD(temp_a1, s16 *, 6) = arg1;
        M2C_FIELD(temp_v0_2, s16 *, 0xA) = arg2;
        M2C_FIELD(temp_a1, s16 *, 8) = arg2;
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1A) = (s16) (arg3 + 0x400);
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_a1, s16 *, 0x4E) = arg3;
        M2C_FIELD(temp_a1, s16 *, 0x4C) = 4;
        M2C_FIELD(temp_a1, s16 *, 0x50) = (s16) hold4;
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg6;
        M2C_FIELD(temp_a1, s16 *, 0x58) = (s16) hold5;
        M2C_FIELD(temp_a1, s16 *, 0x48) = (s16) hold7;
    }
    return temp_v0;
}
