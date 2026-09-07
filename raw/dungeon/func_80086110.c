#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8008B9D8();
M2C_UNK func_8008CAA0();
M2C_UNK func_8008CBA0();
M2C_UNK func_8008CF6C();
M2C_UNK func_80090200();
M2C_UNK func_800A2B04();
extern u16 D_80013714[];
extern M2C_UNK D_8004F5F4;
extern s32 D_80082EB0[];
extern M2C_UNK D_80083160[];
extern u16 D_80083462[];
extern s32 D_800E4940[];

void func_8008B870(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_v1;
    M2C_UNK *temp_s4 = D_80083160;

    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    temp_v1 = M2C_FIELD(arg3, s16 *, 0x64);
    if ((temp_v1 < 0) || (M2C_FIELD(arg0, u16 *, 0x10C) & 1)) {
        M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        func_8008CAA0(arg0, arg1, arg2, arg3);
        func_8008B9D8();
        return;
    }
    if (temp_v1 > 0) {
        func_8008CBA0(arg0, arg1, arg2, arg3);
    }
    if (!(D_80013714[0] & 1) && !(D_80083462[0] & 4) && (temp_s4[2] & 0x80)) {
        M2C_FIELD(arg3, s16 *, 0x8A) = 2;
        D_800E4940[0] = 2;
        func_8008CF6C(arg0, arg1, arg2, &D_8004F5F4);
        D_80082EB0[0] = 0;
        M2C_FIELD(arg0, s32 *, 0xC8) = 0;
        M2C_FIELD(arg0, s32 *, 0x104) = 0;
        func_8008B9D8();
        return;
    }
    if ((M2C_FIELD(arg0, u8 *, 0x9A) != 0xD) && (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200)) {
        M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
        func_80090200(arg0, arg1, arg2, arg3);
    }
}
