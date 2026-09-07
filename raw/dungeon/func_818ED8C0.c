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

extern s16 D_80026428[];
extern s32 D_800814A0[3];
extern void *D_80024008[];

void func_800250C0(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    void **jump_table;
    s32 temp_v1;
    s32 temp_lo;
    s32 result;

    arg1 = M2C_FIELD(arg0, s16 *, 4);
    arg3 = M2C_FIELD(arg0, s16 *, 0xA);
    D_80026428[0] = 1;
    if (arg1 < arg3) {
        temp_lo = arg1 * 3;
        goto block_4;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 2);
    temp_v1 -= arg1;
    temp_lo = temp_v1 * 3;
block_4:
    result = (temp_lo * 0x10) / arg3;
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) result;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) result;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) result;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1E);
    M2C_FIELD(arg0, s16 *, 4) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 4) + 1);
    if ((u32) temp_v1 >= 8U) {
        goto block_10;
    }
    jump_table = D_80024008;
    (void)jt_keep; goto *jump_table[(u32)(temp_v1)];
jt_c0:
jt_c1:
jt_c2:
jt_c4:
jt_c5:
jt_c6:
    M2C_FIELD(arg0, s16 *, 0x1E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1E) + 1);
    M2C_FIELD(arg0, u8 *, 0x28) = (u8) (M2C_FIELD(arg0, u8 *, 0x28) + 0x10);
    goto block_10;
jt_c3:
    M2C_FIELD(arg0, s16 *, 0x1E) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1E) + 1);
    M2C_FIELD(arg0, u8 *, 0x28) = (u8) (M2C_FIELD(arg0, u8 *, 0x28) - 0x30);
    M2C_FIELD(arg0, u8 *, 0x29) = (u8) (M2C_FIELD(arg0, u8 *, 0x29) + 0x20);
    goto block_10;
jt_c7:
    M2C_FIELD(arg0, s16 *, 0x1E) = 0;
    M2C_FIELD(arg0, u8 *, 0x28) = (u8) (M2C_FIELD(arg0, u8 *, 0x28) - 0x30);
    M2C_FIELD(arg0, u8 *, 0x29) = (u8) (M2C_FIELD(arg0, u8 *, 0x29) - 0x20);
block_10:
    if (M2C_FIELD(arg0, s16 *, 4) < M2C_FIELD(arg0, s16 *, 2)) {
        goto block_12;
    }
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
block_12:
    return;
}
