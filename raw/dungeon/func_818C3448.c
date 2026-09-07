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

extern s32 D_800814A0[3];
M2C_UNK func_800247AC();
M2C_UNK func_80024AF4();
M2C_UNK func_80024E9C() __attribute__((noreturn));
void func_80024EEC(void) __attribute__((noreturn));
s32 func_80069EF8();

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} Func818C3448State;

void func_818C3448(void *arg0, void *arg1, void *arg2) {
    s16 temp_lo;
    s32 temp_a1_s16;
    register s32 temp_s0 ASM_REG("$16");
    s16 temp_v0;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 tail_v0;
    s16 tail_v1;
    s32 var_v1;
    s32 temp_a0;
    s32 temp_a0_3;
    s32 temp_a1;
    register s32 case0_scale ASM_REG("$2");
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a2;
    s32 var_v0;
    s32 tail_cond;
    u16 case2_state;
    u16 temp_a0_2;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0xC) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xC) + 1);
    temp_v1_3 = (s16) (M2C_FIELD(arg0, u16 *, 0x12) + 1);
    temp_s0 = temp_v1_3;
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) (M2C_FIELD(arg0, u16 *, 0x10) + 1);
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) temp_v1_3;
    temp_s0 = (temp_s0 % 7) + 1;
    func_800478B8(arg2);
    temp_a1_s16 = (s16) temp_s0;
    var_v1 = temp_a1_s16;
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x300);
    if (temp_a1_s16 < 0) {
        var_v1 = temp_a1_s16 + 3;
    }
    temp_a0 = temp_a1_s16 / 2;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((var_v1 >> 2) << 7);
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((s32) (((s16) temp_a0 - (((s32) ((s16) temp_a0 + ((u32) (temp_a0 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((s32) ((temp_a1_s16 - (temp_a0 * 2)) << 0x10) >> 9);
    temp_v1_4 = M2C_FIELD(arg0, s16 *, 0xE);
    temp_a0_2 = (u16) M2C_FIELD(arg0, s16 *, 0xE);
    if (temp_v1_4 == 1) {
        goto case_1;
    }
    if (temp_v1_4 < 2) {
        if (temp_v1_4 == 0) {
            case0_scale = 0x1400;
            goto case_0;
        }
        func_80024EEC();
    }
    ASM_SCHED_BARRIER();
    if (temp_v1_4 == 2) {
        goto case_2;
    }
    if (temp_v1_4 == 3) {
        goto case_3;
    }
    func_80024EEC();

case_0:
        temp_lo = (case0_scale / (s16) M2C_FIELD(arg0, s16 *, 0x14)) * (s16) M2C_FIELD(arg0, u16 *, 0x10);
        M2C_FIELD(arg2, s16 *, 0x1E) = temp_lo;
        M2C_FIELD(arg2, s16 *, 0x1C) = temp_lo;
        temp_v0_3 = ((Func818C3448State *)arg1)->f0;
        temp_v1_6 = ((Func818C3448State *)arg1)->fC;
        temp_a0_3 = ((Func818C3448State *)arg1)->f10;
        temp_a1 = ((Func818C3448State *)arg1)->f14;
        ((Func818C3448State *)arg1)->f0 = temp_v0_3 + temp_v1_6;
        ((Func818C3448State *)arg1)->f4 = (s32) (((Func818C3448State *)arg1)->f4 + temp_a0_3);
        ((Func818C3448State *)arg1)->f8 = (s32) (((Func818C3448State *)arg1)->f8 + temp_a1);
        tail_v0 = M2C_FIELD(arg0, s16 *, 0x10);
        tail_v1 = M2C_FIELD(arg0, s16 *, 0x14);
        tail_cond = tail_v0 < tail_v1;
        ASM_TAILSLOT_PIN(tail_cond);
        func_80024E9C(temp_a0_3, temp_a1);
        return;
case_1:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < 0xC) {
            return;
        }
        M2C_FIELD(arg0, s16 *, 0xE) = (s16) (temp_a0_2 + 1);
        M2C_FIELD(arg0, s16 *, 0x10) = 0;
        func_80024EEC();
        return;
case_2:
        func_80024AF4(arg0, arg1, arg2);
        var_v0 = func_80069EF8();
        temp_v1_5 = var_v0;
        if (temp_v1_5 < 0) {
            var_v0 = temp_v1_5 + 0xFFF;
        }
        temp_v0 = temp_v1_5 - ((var_v0 >> 0xC) << 0xC);
        func_800247AC(arg0, arg1, temp_v0);
        temp_v0_2 = temp_v0 + 0x800;
        var_a2 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_a2 = temp_v0 + 0x17FF;
        }
        func_800247AC(arg0, arg1, (s16) (temp_v0_2 - ((var_a2 >> 0xC) << 0xC)));
        if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < 0x21) {
            return;
        }
        case2_state = M2C_FIELD(arg0, u16 *, 0xE);
        M2C_FIELD(arg0, u16 *, 0x10) = 0U;
        M2C_FIELD(arg0, u16 *, 0xE) = (u16) (case2_state + 1);
        func_80024EEC();
        return;
case_3:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] |= 0x8000;
        }
        return;
}
