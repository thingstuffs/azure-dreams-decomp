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
#define BSWAP32(x) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

extern s32 func_8009A350();
extern s32 func_800BCB04();

s32 func_800A4778(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 r_arg0 ASM_REG("$19") = arg0;
    register s32 r_arg1 ASM_REG("$20") = arg1;
    s16 sp10;
    s16 temp_v0_3;
    register s32 temp_v1 ASM_REG("$3");
    s32 var_v0;
    s32 var_v0_3;
    register s32 temp_s0 ASM_REG("$16");
    register s32 temp_s2 ASM_REG("$18");
    register s32 temp_s5 ASM_REG("$21");
    register s32 temp_v0_2 ASM_REG("$17");
    s32 var_a0;
    s32 var_v0_2;
    s32 var_v0_4;
    register u32 temp_a0 ASM_REG("$4");
    register u32 temp_a1 ASM_REG("$5");
    register s32 temp_a2 ASM_REG("$6");
    register u32 temp_v0 ASM_REG("$2");

    ASM_KEEP_NV(r_arg0);
    temp_s2 = arg2;
    ASM_KEEP_NV(temp_s2);
    temp_v0 = r_arg0;
    temp_s5 = temp_s2;
    if (arg3 == 0) {
        temp_v0 = (u32) (temp_v0 & 0xFFFF) >> 6;
        temp_a0 = temp_v0 - 1;
        temp_a1 = (u32) (r_arg1 & 0xFFFF) >> 6;
        ASM_SCHED_BARRIER();
        temp_a2 = 0;
        ASM_USE(temp_a2);
        temp_s0 = temp_v0;
        temp_v0_2 = temp_a1;
        if ((func_8009A350(temp_a0, temp_a1, temp_a2, &sp10) << 0x10) != 0) {
            temp_v0 = temp_s0 << 6;
            ASM_KEEP(temp_v0);
            temp_s0 = temp_v0 + 0x20;
            temp_a0 = temp_s0 & 0xFFE0;
            temp_v0 = temp_v0_2 << 6;
            ASM_KEEP(temp_v0);
            temp_v0 += 0x20;
            temp_a1 = temp_v0 & 0xFFE0;
            temp_a2 = (s16) (temp_s2 - 0x20);
            temp_v0_2 = temp_v0;
            temp_v0_3 = func_800BCB04(temp_a0, temp_a1, temp_a2);
            sp10 = temp_v0_3;
            if (temp_v0_3 >= 0x201) {
                temp_s2 = temp_s0;
                ASM_KEEP_NV(temp_s0);
                temp_v0 = temp_s0 - r_arg0;
                temp_v1 = (s16) temp_v0;
                var_v0 = temp_v1;
                if (temp_v1 < 0) {
                    var_v0 = 0 - var_v0;
                }
                var_a0 = 0;
                if (var_v0 >= 0x16) {
                    var_v0_2 = 0x40;
                    if (temp_v1 > 0) {
                        var_v0_2 = -0x40;
                    }
                    var_a0 = var_v0_2;
                }
                temp_v0 = temp_v0_2 - r_arg1;
                temp_v1 = (s16) temp_v0;
                var_v0_3 = temp_v1;
                if (temp_v1 < 0) {
                    var_v0_3 = 0 - var_v0_3;
                }
                if (var_v0_3 >= 0x16) {
                    var_v0_4 = 0x40;
                    if (temp_v1 > 0) {
                        var_v0_4 = -0x40;
                    }
                } else {
                    var_v0_4 = 0;
                }
                sp10 = func_800BCB04((temp_s2 + var_a0) & 0xFFFF, (temp_v0_2 + var_v0_4) & 0xFFFF, (s16) (temp_s5 - 0x20));
                return sp10 > 0x200;
            }
        }
    }
    return 0;
}
