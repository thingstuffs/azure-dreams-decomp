/* cfail-repair: tf7-phase1-cache-v3 */
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
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern u16 *D_800D1868[4];

void func_800B7978(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    register s16 var_a0;
    register s16 var_t1;
    u16 *var_a2;
    u16 temp_t3;
    u16 temp_t4;
    u16 temp_v1;
    u16 temp_v0_3;
    u8 *base;
    u8 *address;
    s32 index;

    index = arg2 << 0x10;
    base = (u8 *)D_800D1868;
    ASM_KEEP(base);
    index >>= 0xE;
    address = (u8 *)index;
    address = (u8 *)((s32)address + (s32)base);
    var_a2 = *(u16 **)address;
    var_t1 = 0;
    temp_t4 = *var_a2++;
    temp_t3 = *var_a2++;
    temp_v1 = *var_a2++;
    temp_v0_3 = *var_a2++;
    arg0 -= temp_v1;
    arg1 -= temp_v0_3;
    while ((var_t1 << 0x10) < (temp_t3 << 0x10)) {
        var_a0 = 0;
        while (var_a0 < (s16)temp_t4) {
            temp_v1 = *var_a2;
            if (temp_v1 != 0) {
                ((u16 *)arg3)[((var_t1 + (s16)arg1) << 7) + var_a0 + (s16)arg0] = temp_v1;
            }
            var_a2++;
            var_a0++;
        }
        var_t1++;
    }
}
