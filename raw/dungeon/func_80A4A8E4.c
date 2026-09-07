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

s32 rand();
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_800814A0[3];

void func_801740E4(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0;
    s32 random_v0;
    s32 field_v1;

    M2C_FIELD(arg1, s32 *, 0) += ((D_8006CCD8[M2C_FIELD(arg0, s16 *, 0x14)] * M2C_FIELD(arg0, s16 *, 0x32)) << 7) + (rand() & 0x7FFF);
    M2C_FIELD(arg1, s32 *, 4) += ((D_8006CCE8[M2C_FIELD(arg0, s16 *, 0x14)] * M2C_FIELD(arg0, s16 *, 0x32)) << 7) + (rand() & 0x7FFF);
    random_v0 = rand();
    field_v1 = M2C_FIELD(arg1, s32 *, 8) + (s32) 0xFFFE0000;
    M2C_FIELD(arg1, s32 *, 8) = field_v1 - (random_v0 & 0xFFF);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 8;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    if (((temp_v0 << 0x10) <= 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
