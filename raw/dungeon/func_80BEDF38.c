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

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
} FuncArg1;

M2C_UNK func_8003DB94();
M2C_UNK func_800478B8(void *, s32);
s32 func_800644B8();
s32 func_80064584();
extern s32 D_800814A0[];
extern M2C_UNK D_800DEC70;

void func_80173738(void *arg0, FuncArg1 *arg1, void *arg2) {
    s16 temp_a0;
    s16 temp_v0;
    s32 temp_lo;
    s32 temp_base;
    s32 temp_delta;
    register void *dst ASM_REG("$4");

    M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) - 0x12C);
    M2C_FIELD(arg0, u16 *, 0x20) = (u16) (M2C_FIELD(arg0, u16 *, 0x20) + 2);
    arg1->unk00 = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + ((s16) M2C_FIELD(arg0, u16 *, 0x20) * func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x1E)) * 0x10));
    temp_lo = (s16) M2C_FIELD(arg0, u16 *, 0x20) * func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x1E));
    dst = arg2;
    temp_delta = 0xFFF40000U;
    ASM_KEEP_NV(temp_delta);
    temp_base = M2C_FIELD(arg0, s32 *, 0x44);
    arg1->unk08 = (s32) (arg1->unk08 + temp_delta);
    arg1->unk04 = (s32) (temp_base + (temp_lo * 0x10));
    func_800478B8(dst, temp_delta);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x4000) {
        func_8003DB94(arg2, &D_800DEC70, 0);
    }
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x1A);
    if (temp_a0 < 0xA) {
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((M2C_FIELD(arg0, u8 *, 0) * temp_a0) / 9);
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((M2C_FIELD(arg0, u8 *, 1) * M2C_FIELD(arg0, s16 *, 0x1A)) / 9);
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((M2C_FIELD(arg0, u8 *, 2) * M2C_FIELD(arg0, s16 *, 0x1A)) / 9);
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x1A) - 1;
    M2C_FIELD(arg0, s16 *, 0x1A) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        M2C_FIELD(D_800814A0, s32 *, 0) = (s32) (M2C_FIELD(D_800814A0, s32 *, 0) | 0x8000);
    }
}
