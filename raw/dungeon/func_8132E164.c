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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
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

extern s32 D_800814A0[3];
extern u8 D_80080000[];

void func_80165164(void *arg0, void *arg1) {
    s16 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x4C));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x50));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x54));
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) + M2C_FIELD(arg0, s32 *, 0x58));
    M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) + M2C_FIELD(arg0, s32 *, 0x5C));
    M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + M2C_FIELD(arg0, s32 *, 0x60));
    var_v0 = abs(M2C_FIELD(arg0, s16 *, 0x42) - M2C_FIELD(arg1, s16 *, 2));
    if (var_v0 < 0x10) {
        var_v0_2 = abs(M2C_FIELD(arg0, s16 *, 0x44) - M2C_FIELD(arg1, s16 *, 6));
        if (var_v0_2 < 0x10) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            M2C_FIELD(D_80080000, s32 *, 0x14A0) = (s32) (M2C_FIELD(D_80080000, s32 *, 0x14A0) | 0x8000);
        }
    }
    var_a0 = M2C_FIELD(arg0, u8 *, 0) * M2C_FIELD(arg0, s16 *, 0x32);
    if (var_a0 < 0) {
        var_a0 += 0xFF;
    }
    M2C_FIELD(arg0, s8 *, 4) = (s8) (var_a0 >> 8);
    var_a1 = M2C_FIELD(arg0, u8 *, 1) * M2C_FIELD(arg0, s16 *, 0x32);
    if (var_a1 < 0) {
        var_a1 += 0xFF;
    }
    M2C_FIELD(arg0, s8 *, 5) = (s8) (var_a1 >> 8);
    var_v1 = M2C_FIELD(arg0, u8 *, 2) * M2C_FIELD(arg0, s16 *, 0x32);
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    M2C_FIELD(arg0, s8 *, 6) = (s8) (var_v1 >> 8);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 8;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 4);
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        M2C_FIELD(D_80080000, s32 *, 0x14A0) = (s32) (M2C_FIELD(D_80080000, s32 *, 0x14A0) | 0x8000);
    }
}
