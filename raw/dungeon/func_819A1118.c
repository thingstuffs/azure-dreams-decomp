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

extern s16 D_800261B0[];
extern s32 D_800814A0;

void func_819A1118(void *arg0) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    u16 temp_v0;
    void *var_a0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x3A) - 1;
    D_800261B0[0] = 1;
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x3E);
    M2C_FIELD(arg0, u16 *, 0x3A) = temp_v0;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x3C) - (s16) temp_v0;
    if (temp_a0 >= temp_v1) {
        M2C_FIELD(arg0, s16 *, 0x54) = (s16) (M2C_FIELD(arg0, u16 *, 0x60) + ((s32) (M2C_FIELD(arg0, s16 *, 0x6C) * temp_v1) / temp_a0));
        M2C_FIELD(arg0, s16 *, 0x56) = (s16) (M2C_FIELD(arg0, u16 *, 0x62) + ((s32) (M2C_FIELD(arg0, s16 *, 0x6E) * (M2C_FIELD(arg0, s16 *, 0x3C) - (s16) M2C_FIELD(arg0, u16 *, 0x3A))) / (s16) M2C_FIELD(arg0, s16 *, 0x3E)));
        M2C_FIELD(arg0, s16 *, 0x58) = (s16) (M2C_FIELD(arg0, u16 *, 0x64) + ((s32) (M2C_FIELD(arg0, s16 *, 0x70) * (M2C_FIELD(arg0, s16 *, 0x3C) - (s16) M2C_FIELD(arg0, u16 *, 0x3A))) / (s16) M2C_FIELD(arg0, s16 *, 0x3E)));
        M2C_FIELD(arg0, s16 *, 0x5A) = (s16) (M2C_FIELD(arg0, u16 *, 0x66) + ((s32) (M2C_FIELD(arg0, s16 *, 0x72) * (M2C_FIELD(arg0, s16 *, 0x3C) - (s16) M2C_FIELD(arg0, u16 *, 0x3A))) / (s16) M2C_FIELD(arg0, s16 *, 0x3E)));
        M2C_FIELD(arg0, s16 *, 0x5C) = (s16) (M2C_FIELD(arg0, u16 *, 0x68) + ((s32) (M2C_FIELD(arg0, s16 *, 0x74) * (M2C_FIELD(arg0, s16 *, 0x3C) - (s16) M2C_FIELD(arg0, u16 *, 0x3A))) / (s16) M2C_FIELD(arg0, s16 *, 0x3E)));
        M2C_FIELD(arg0, s16 *, 0x5E) = (s16) (M2C_FIELD(arg0, u16 *, 0x6A) + ((s32) (M2C_FIELD(arg0, s16 *, 0x76) * (M2C_FIELD(arg0, s16 *, 0x3C) - (s16) M2C_FIELD(arg0, u16 *, 0x3A))) / (s16) M2C_FIELD(arg0, s16 *, 0x3E)));
    }
    var_a1 = 0;
    var_a0 = arg0;
    do {
        M2C_FIELD(var_a0, s8 *, 0xC) = (s8) ((s32) (M2C_FIELD(var_a0, u8 *, 0x1C) * (s16) M2C_FIELD(arg0, u16 *, 0x3A)) / (s16) M2C_FIELD(arg0, s16 *, 0x3C));
        M2C_FIELD(var_a0, s8 *, 0xD) = (s8) ((s32) (M2C_FIELD(var_a0, u8 *, 0x1D) * (s16) M2C_FIELD(arg0, u16 *, 0x3A)) / (s16) M2C_FIELD(arg0, s16 *, 0x3C));
        var_a1 += 1;
        M2C_FIELD(var_a0, s8 *, 0xE) = (s8) ((s32) (M2C_FIELD(var_a0, u8 *, 0x1E) * (s16) M2C_FIELD(arg0, u16 *, 0x3A)) / (s16) M2C_FIELD(arg0, s16 *, 0x3C));
        var_a0 += 4;
    } while (var_a1 < 4);
    if ((s16) M2C_FIELD(arg0, u16 *, 0x3A) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
