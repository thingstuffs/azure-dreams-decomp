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

M2C_UNK func_800644B8();
extern M2C_UNK D_800814A0;

void func_800220A8(void *arg0, void *arg1) {
    s16 temp_v1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 temp_a1;
    u16 temp_a0_2;

    temp_a1 = 2;
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x18) == temp_a1) {
        M2C_FIELD(arg0, s16 *, 0) = 3;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    if (temp_v1 != temp_a1) {
        if (temp_v1 < 3) {
            if (temp_v1 != 0) {
                if (temp_v1 == 1) {
                    goto state1;
                }
                return;
            }
            goto state0;
        }
        if (temp_v1 != 3) {
            if (temp_v1 != 0xF0) {
                return;
            }
            goto state_f0;
        }
        goto state3;
    }
    goto state2;

state0:
    if ((M2C_FIELD(arg1, s32 *, 8) += 0x100000) < (s32)0xFF900000) {
        return;
    }
    M2C_FIELD(arg0, u16 *, 2) = 0;
    M2C_FIELD(arg1, s32 *, 0x14) = -0x40000;
    goto set_state1;

state1:
{
    register s32 state1_a0 ASM_REG("$4");
    register s32 state1_v1 ASM_REG("$3");
    register s32 state1_v0 ASM_REG("$2");

    state1_a0 = M2C_FIELD(arg1, s32 *, 0x14);
    state1_v1 = state1_a0;
    ASM_KEEP_NV(state1_v1);
    state1_v0 = M2C_FIELD(arg1, s32 *, 8);
    state1_v0 += state1_a0;
    state1_v1 += 0x4000;
    M2C_FIELD(arg1, s32 *, 8) = state1_v0;
    M2C_FIELD(arg1, s32 *, 0x14) = state1_v1;
    if (state1_v1 != 0x40000) {
        return;
    }
    M2C_FIELD(arg0, s16 *, 0) = temp_a1;
    return;
}

state2:
{
    register s32 state2_v0 ASM_REG("$2");
    register s32 state2_v1 ASM_REG("$3");

    state2_v0 = M2C_FIELD(arg1, s32 *, 8);
    state2_v1 = M2C_FIELD(arg1, s32 *, 0x14);
    state2_v0 += state2_v1;
    M2C_FIELD(arg1, s32 *, 8) = state2_v0;
    state2_v0 = state2_v1;
    ASM_KEEP_NV(state2_v0);
    state2_v1 = -0x8000;
    state2_v0 += state2_v1;
    M2C_FIELD(arg1, s32 *, 0x14) = state2_v0;
    if (state2_v0 != -0x40000) {
        return;
    }
}

set_state1:
    M2C_FIELD(arg0, s16 *, 0) = 1;
    return;

state_f0:
{
    register u16 statef0_a0 ASM_REG("$4");
    register s32 statef0_v0 ASM_REG("$2");
    register s32 statef0_v1 ASM_REG("$3");

    statef0_a0 = (M2C_FIELD(arg0, u16 *, 2) + 1) & 0x7F;
    M2C_FIELD(arg0, u16 *, 2) = statef0_a0;
    statef0_v0 = func_800644B8(statef0_a0 << 6, temp_a1, arg0);
    statef0_v0 <<= 7;
    statef0_v1 = (s32)0xFF900000;
    statef0_v0 += statef0_v1;
    M2C_FIELD(arg1, s32 *, 8) = statef0_v0;
    return;
}

state3:
{
    register s32 state3_v0 ASM_REG("$2");
    register s32 state3_v1 ASM_REG("$3");

    state3_v0 = M2C_FIELD(arg1, s32 *, 8);
    state3_v1 = (s32)0xFFF00000;
    state3_v0 += state3_v1;
    state3_v1 = (s32)0xFE000000;
    state3_v1 = state3_v1 < state3_v0;
    M2C_FIELD(arg1, s32 *, 8) = state3_v0;
    if (state3_v1 != 0) {
        return;
    }
    M2C_FIELD(arg0, u16 *, -2) |= 0x8000;
    state3_v0 = D_800814A0;
    state3_v0 |= 0x8000;
    D_800814A0 = state3_v0;
    return;
}
}
