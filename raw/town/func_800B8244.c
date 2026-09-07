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

s32 func_8004A658();
s32 func_8004AC3C();
M2C_UNK bzero(void **, M2C_UNK);
M2C_UNK func_800B5264();
M2C_UNK func_800B53BC();
M2C_UNK func_800B58B8(void **, s32);
s32 func_800B5918();

void func_800B59A4(s32 arg0, void *arg1) {
    s32 sp18[10];
    s16 var_s4;
    s32 var_s2;
    s32 var_s3;
    void **temp_s0;
    void *temp_a0;
    void *temp_v0;
    void *temp_v0_2;
    void *var_s1;

    var_s1 = arg1;
    bzero((void **) &sp18[0], 0xC);
    func_800B58B8((void **) &sp18[0], arg0);
    var_s3 = 0;
    var_s4 = 0x66;
    var_s2 = 0xD8;
loop_1:
    temp_s0 = (void **)((s32)(var_s3 << 2) + (s32)&sp18[0]);
    temp_a0 = *temp_s0;
    if (temp_a0 != NULL) {
        func_800B5264(M2C_FIELD(var_s1, s32 *, 0x18), func_8004AC3C(temp_a0, &sp18[8]), sp18[8], 0x58, var_s2);
        func_800B53BC(M2C_FIELD(var_s1, s32 *, 0x24), func_800B5918(*temp_s0, &sp18[4]), 0, 0xA0, var_s2);
        temp_v0 = *temp_s0;
        var_s3 += 1;
        M2C_FIELD(M2C_FIELD(var_s1, void **, 0x30), s32 *, 0) = func_8004A658(M2C_FIELD(temp_v0, u8 *, 1), M2C_FIELD(temp_v0, u8 *, 0));
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_s1, void **, 0x30), void **, 4), s16 *, 8) = -0x30;
        var_s2 += 0x10;
        temp_v0_2 = M2C_FIELD(M2C_FIELD(var_s1, void **, 0x30), void **, 4);
        var_s1 += 4;
        M2C_FIELD(temp_v0_2, s16 *, 0xA) = var_s4;
        var_s4 += 0x10;
        if (var_s3 < 3) {
            goto loop_1;
        }
    }
}
