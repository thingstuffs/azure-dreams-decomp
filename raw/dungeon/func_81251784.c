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

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
M2C_UNK func_80170B50();
M2C_UNK func_80173C30();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern u16 D_8008378A;
extern M2C_UNK D_8017112C;
extern M2C_UNK D_80171514;
extern M2C_UNK D_80173E8C;
extern void *D_80174710;

void *func_80170F84(s16 arg0, s32 arg1, s16 arg2, u16 arg3) {
    void *var_s4 = NULL;
    s16 saved_arg1;
    s16 saved_arg3;
    s16 saved_arg2;
    u16 temp_s2;
    u16 temp_s3;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    temp_v0 = func_8003FD64(0x112, &D_80083498);
    if (temp_v0 != NULL) {
        var_s4 = temp_v0 + 0x20;
        D_80174710 = temp_v0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8017112C;
        M2C_FIELD(var_s4, s8 *, 0x13) = 0x37;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, u16 *, 0xA) = saved_arg3;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s8 *, 0x24) = saved_arg1;
        M2C_FIELD(temp_s0, s8 *, 0x25) = saved_arg2;
        M2C_FIELD(temp_s0, M2C_UNK **, 0x2C) = &D_80173E8C;
        M2C_FIELD(var_s4, s16 *, 0x9E) = 0;
        func_800A9C18(temp_v0, temp_s1, temp_s0, arg0);
        M2C_FIELD(var_s4, u8 *, 0x9A) = 0xFF;
        M2C_FIELD(var_s4, s8 *, 0x9C) = -1;
        M2C_FIELD(var_s4, M2C_UNK **, 0x8C) = &D_80171514;
        M2C_FIELD(var_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s4, s32 *, 0x1C) | 0x40000);
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        func_800AA36C(var_s4, temp_s1, temp_s0, var_s4);
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) D_8008378A;
        M2C_FIELD(temp_s1, s16 *, 0x16) = (s16) (M2C_FIELD(temp_s1, u16 *, 0xA) - 0x20);
        M2C_FIELD(temp_s1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s1, u16 *, 0xA) - 0x190);
        temp_s2 = M2C_FIELD(temp_s0, u16 *, 0x1C);
        temp_s3 = M2C_FIELD(temp_s0, u16 *, 0x1E);
        M2C_FIELD(temp_s0, u16 *, 0x1C) = 0U;
        M2C_FIELD(temp_s0, u16 *, 0x1E) = 0U;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x80);
        func_80170B50(var_s4, temp_s1, temp_s0, 1);
        func_80170B50(var_s4, temp_s1, temp_s0, 2);
        M2C_FIELD(temp_s0, u16 *, 0x1C) = temp_s2;
        M2C_FIELD(temp_s0, u16 *, 0x1E) = temp_s3;
        func_80173C30();
    }
    return var_s4;
}
