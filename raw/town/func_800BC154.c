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
#define M2C_BREAK() M2C_ERROR(0)
#define M2C_SYNC() M2C_ERROR(0)
#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_80033AA8();
M2C_UNK func_80033AE8();
M2C_UNK func_8003E4FC();
M2C_UNK func_8003F320();
M2C_UNK func_800B7934();
extern u8 D_80010000[];
extern M2C_UNK D_800D1BF4;
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

void func_800B98B4(void) {
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s3;
    s32 var_s2;
    u8 temp_v0;
    void *temp_v1;
    void *temp_v2;

    func_8003E4FC(6, &D_800D1BF4, 0);
    var_s2 = 0;
    func_8003F320();
    func_80033AE8(0x12C3);
    var_s3 = D_800D2644;
    var_s1 = D_800D2EA4;
    var_s0 = (u8 *)0x80010000;
    do {
        temp_v0 = M2C_FIELD(var_s0, u8 *, 0x33A4 + (var_s2 * 2));
        if (temp_v0 != 0) {
            temp_v1 = (void *)((u32)(temp_v0 << 5) + (u32)var_s3);
            if (M2C_FIELD(temp_v1, u8 *, 1) != 0) {
                func_800B7934(M2C_FIELD(var_s1, u8 *, 0), M2C_FIELD(var_s1, u8 *, 1), M2C_FIELD(temp_v1, u8 *, 0));
            }
            temp_v2 = (void *)((u32)(M2C_FIELD(var_s0, u8 *, 0x33A4 + (var_s2 * 2)) << 5) + (u32)var_s3);
            if (M2C_FIELD(temp_v2, u8 *, 0) == 1) {
                func_80033AA8(0x12C3);
            }
        }
        var_s1 += 8;
        var_s2 += 1;
    } while (var_s2 < 0x21);
}
