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
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
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

extern s16 D_80025924[5];
extern s32 D_800814A0[3];
s32 rand();
s32 func_800A45D8();
s16 func_800BCB04();

void func_818CEDC8(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    s32 call_a2;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x4C));
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) (M2C_FIELD(arg0, s32 *, 0x4C) + M2C_FIELD(arg0, s32 *, 0x58));
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6),
                       (call_a2 = M2C_FIELD(arg1, s16 *, 0xA), *D_80025924 = 1, call_a2)) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0x4C));
        M2C_FIELD(arg0, s32 *, 0x4C) = 0;
        M2C_FIELD(arg0, s32 *, 0x58) = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x50));
    M2C_FIELD(arg0, s32 *, 0x50) = (s32) (M2C_FIELD(arg0, s32 *, 0x50) + M2C_FIELD(arg0, s32 *, 0x5C));
    if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(arg1, s16 *, 0xA)) << 0x10) != 0) {
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 0x50));
        M2C_FIELD(arg0, s32 *, 0x50) = 0;
        M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    }
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x54));
    {
        s32 temp_az = M2C_FIELD(arg0, s32 *, 0x60);
        M2C_FIELD(arg0, s32 *, 0x54) += temp_az;
    }
    M2C_FIELD(arg0, s32 *, 0x4C) = (s32) ((M2C_FIELD(arg0, s32 *, 0x4C) * 0x60) / 100);
    M2C_FIELD(arg0, s32 *, 0x50) = (s32) ((M2C_FIELD(arg0, s32 *, 0x50) * 0x60) / 100);
    temp_s0 = M2C_FIELD(arg1, s16 *, 0xA);
    if ((func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, volatile s16 *, 0xA) - 4)) - 0x10) < temp_s0) {
        M2C_FIELD(arg0, s32 *, 0x54) = 0;
        M2C_FIELD(arg1, s16 *, 0xA) = (s16) (func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) - 4)) - 0x11);
        M2C_FIELD(arg1, s16 *, 8) = 0;
        if (M2C_FIELD(arg0, s16 *, 8) == 0) {
            M2C_FIELD(arg0, s16 *, 8) = 1;
            M2C_FIELD(arg0, s32 *, 0x4C) = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
            M2C_FIELD(arg0, s32 *, 0x50) = (s32) ((((rand() & 0x7F) << 0xB) + 0xFFFE0000) * 3);
        }
    }
    temp_v0 = M2C_FIELD(arg0, u16 *, 4) + 1;
    M2C_FIELD(arg0, u16 *, 4) = temp_v0;
    if (!(temp_v0 & 3)) {
        func_800478B8(arg2);
    }
    temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1C) + 0x64;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2;
    if ((u32) (temp_v0_2 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
    }
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x64;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) >= 0x1001U) {
        M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
    }
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 2) - 1;
    M2C_FIELD(arg0, u16 *, 2) = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
