/* first_pass: swept 49 configs, best 2.7.2-cdk '-fno-delayed-branch' 89 words off — do NOT re-sweep by hand */
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

M2C_UNK func_8004FA2C();
s32 func_8004FD78();
M2C_UNK func_80053DA8();
extern void *D_800814A8[];
extern M2C_UNK D_80083160[8];

void func_8004FAA4(void *arg0) {
    M2C_UNK var_a1;
    M2C_UNK *input;
    register void *call_arg0 ASM_REG("$4");
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s0;

    input = D_80083160;
    var_s0 = 0;
    if ((M2C_FIELD(input, s32 *, 8) != 0) && (M2C_FIELD(arg0, s32 *, 0x24) >= 2)) {
        if (M2C_FIELD(input, s32 *, 8) & 0xA000) {
            ASM_KEEP(input);
            if (M2C_FIELD(input, s32 *, 0x10) & 0x2000) {
                var_s0 = 1;
                goto block_7;
            }
            if (M2C_FIELD(input, s32 *, 0x10) & 0x8000) {
                var_s0 = -1;
block_7:
                M2C_FIELD(arg0, s32 *, 0x38) = 0;
                M2C_FIELD(arg0, s32 *, 0x28) = 4;
            } else {
                temp_v1 = M2C_FIELD(arg0, s32 *, 0x38);
                if (temp_v1 >= 9) {
                    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (temp_v1 - 2);
                    temp_v1 = M2C_FIELD(input, volatile s32 *, 8);
                    if (temp_v1 & 0x2000) {
                        var_s0 = 1;
                        goto block_13;
                    }
                    if (temp_v1 & 0x8000) {
                        var_s0 = -1;
block_13:
                        M2C_FIELD(arg0, s32 *, 0x28) = 3;
                    }
                } else {
                    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (temp_v1 + 1);
                }
            }
        }
        if (var_s0 == 0) {
            ASM_KEEP(input);
            if (M2C_FIELD(input, s32 *, 0x10) & 1) {
                ASM_SCHED_BARRIER();
                if (M2C_FIELD(D_800814A8[0], s32 *, 0xB0) != 0) {
                    call_arg0 = arg0;
                    ASM_KEEP(call_arg0);
                    var_a1 = 1;
                    goto block_22;
                }
            } else if (M2C_FIELD(input, s32 *, 0x10) & 2) {
                ASM_SCHED_BARRIER();
                if (M2C_FIELD(D_800814A8[0], s32 *, 0xAC) != 0) {
                    call_arg0 = arg0;
                    ASM_KEEP(call_arg0);
                    var_a1 = 0;
block_22:
                    temp_v0 = func_8004FD78(call_arg0, var_a1);
                    M2C_FIELD(arg0, s32 *, 0x28) = 4;
                    var_s0 = temp_v0 - M2C_FIELD(arg0, s32 *, 0x30);
                }
            }
            if (var_s0 != 0) {
                goto block_24;
            }
        } else {
block_24:
            func_80053DA8(0x504);
            func_8004FA2C(arg0, var_s0);
        }
    }
}
