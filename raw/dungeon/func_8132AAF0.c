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

void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_8003DB94();
M2C_UNK func_800A56E0();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80172274;
extern void *D_80174CD8;

void func_801722F0(void) {
    void *temp_a0;
    void *temp_a1;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_s1 = M2C_FIELD(D_80174CD8, void **, 8);
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_a1 = &D_80045340;
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x16) = 0x1E;
        M2C_FIELD(temp_v1, s16 *, 0x18) = 0x1E;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80172274;
        func_8004491C(temp_v0, temp_a1);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 6) = 0;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) M2C_FIELD(temp_s1, s32 *, 0);
        M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) M2C_FIELD(temp_s1, s32 *, 4);
        M2C_FIELD(temp_v1_2, s32 *, 8) = (s32) M2C_FIELD(temp_s1, s32 *, 8);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0x80);
        func_8003DB94(temp_a0, &D_800DE870, 0);
        func_800A56E0(0x703);
    }
}
