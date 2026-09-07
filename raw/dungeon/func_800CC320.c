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
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() 0
#define M2C_SYNC() 0
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern s16 D_8008346A[];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
void func_8009A028(void *arg0);
void func_8009A3D0(u8 arg0, u8 arg1, s32 arg2);
void func_800A32A4(void *arg0);
void func_800A56E0(s32 arg0);
s32 func_80042900(void *arg0, s32 arg1);

s32 func_800D1A80(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 *flag = D_8008346A;
    s16 temp_a1;
    M2C_UNK var_a2;
    s16 temp_v0_2;
    s32 temp_v1_4;
    s32 *var_a0;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_a0_2;
    u8 temp_a1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return 0;
        }
        goto block_6;
    }
    if (*flag == 0) {
        M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
        M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
        func_800A56E0(0x805);
        M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
        M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_6:
        temp_v1_2 = M2C_FIELD(arg2, u8 *, 0xC);
        temp_a1 = M2C_FIELD(arg0, s16 *, 0x96);
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) (temp_v1_2 + ((s32) (0x20 - temp_v1_2) / temp_a1));
        temp_v1_3 = M2C_FIELD(arg2, u8 *, 0xD);
        temp_v0 = M2C_FIELD(arg2, u8 *, 0xE);
        temp_a1 = M2C_FIELD(arg0, s16 *, 0x96);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_v1_3 + ((s32) (0x20 - temp_v1_3) / temp_a1));
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_v0 + ((s32) (0x20 - temp_v0) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
        if (((temp_v0_2 << 0x10) > 0) && ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) == 0)) {
            return 0;
        }
        var_a0 = D_80083460;
        {
            temp_v1_4 = M2C_FIELD(var_a0, s32 *, 0x10);
            if (temp_v1_4 == (arg3 - 0x20)) {
                M2C_FIELD(var_a0, s32 *, 0x10) = (s32) (temp_v1_4 & 0x7FFFFFFF);
            }
            func_800A32A4(arg3);
            if ((func_80042900(arg3, 0x1B) << 0x10) == 0) {
                temp_a0_2 = M2C_FIELD(arg2, u8 *, 0x24);
                temp_a1_2 = M2C_FIELD(arg2, u8 *, 0x25);
                var_a2 = 0x3000;
                if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A3D0(temp_a0_2, temp_a1_2, var_a2);
            }
            func_8009A028(arg3);
            M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            return 1;
        }
        return 0;
    }
    return 0;
}
