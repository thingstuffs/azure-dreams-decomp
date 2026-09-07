#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
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

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

M2C_UNK func_8001E660(); /* extern */
M2C_UNK func_8009A21C();             /* extern */
s32 func_8009A350();         /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A6DA4();                    /* extern */
extern u8 D_800E3549[];
extern u8 D_800E36C8[];

void func_8001D328(void *arg0) {
    register s32 rand_v0 ASM_REG("$2");
    u16 sp10;
    s16 temp_v1;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s2;
    register s32 var_v0 ASM_REG("$2");
    void *var_s1;
    void *var_s3;
    void *var_s4;
    u8 *base_3549;

    rand_v0 = func_800A6D30();
    ASM_KEEP(rand_v0);
    {
        register s32 mul_a0 ASM_REG("$4");
        register s32 mul_v1 ASM_REG("$3");
        register s32 mul_t0 ASM_REG("$8");
        register s32 calc_v1 ASM_REG("$3");

        mul_a0 = M2C_FIELD(arg0, u16 *, 6);
        ASM_KEEP(mul_a0);
        mul_v1 = M2C_FIELD(arg0, u16 *, 4);
        ASM_KEEP(mul_v1);
        mul_t0 = mul_a0 * mul_v1;
        rand_v0 &= 7;
        ASM_KEEP(rand_v0);
        ASM_KEEP(mul_t0);
        calc_v1 = (mul_t0 >> 6) + rand_v0 + 4;
        ASM_KEEP(calc_v1);
        var_v0 = calc_v1;
        ASM_KEEP(var_v0);
        temp_v1 = calc_v1;
    }
    temp_v1 = temp_v1 < 0x3D;
    if (!temp_v1) {
        var_v0 = 0x3C;
    }
    var_s2 = (s16) var_v0;
    if (var_s2 >= 0) {
        register u8 *prev_a0 ASM_REG("$4");
        register s32 index_v1 ASM_REG("$3");
        register u8 *base36_v1 ASM_REG("$3");
        register s32 offset_v0 ASM_REG("$2");

        base_3549 = D_800E3549;
        prev_a0 = base_3549 - 1;
        ASM_KEEP(prev_a0);
        index_v1 = var_s2 * 4;
        ASM_KEEP(index_v1);
        var_s4 = (void *) (index_v1 + (s32) prev_a0);
        var_s3 = index_v1 + base_3549;
        base36_v1 = D_800E36C8;
        ASM_KEEP(base36_v1);
        offset_v0 = var_s2 * 0xC;
        ASM_KEEP(offset_v0);
        var_s1 = (void *) (offset_v0 + (s32) base36_v1);
        do {
            temp_s0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 4) - 1) & 0xFFFF) & 0xFFFF;
            temp_v0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 6) - 1) & 0xFFFF) & 0xFFFF;
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 0) + temp_s0;
            M2C_FIELD(var_s1, u8 *, 0) = (u8) temp_v1_2;
            temp_v1_2 = M2C_FIELD(arg0, u8 *, 2) + temp_v0;
            M2C_FIELD(var_s1, u8 *, 1) = (u8) temp_v1_2;
            if (((func_8009A350(M2C_FIELD(var_s1, u8 *, 0) - 1, *(volatile u8 *) ((u8 *) var_s1 + 1), 0, &sp10) << 0x10) == 0) || !(sp10 & 0xFF20)) {
                func_8009A21C(M2C_FIELD(var_s1, u8 *, 0), M2C_FIELD(var_s1, u8 *, 1), 0x800);
                func_8001E660(var_s3, var_s4, 0, 1);
            }
            var_s4 -= 4;
            var_s3 -= 4;
            var_s2 -= 1;
            var_s1 -= 0xC;
        } while (var_s2 >= 0);
    }
}
/* MECHANISM: Short-lived guarded pins encode the multiply, clamp, and held-base register roles.
   Byte-array globals prevent fourfold pointer scaling and preserve the retail address order.
   One reused RMW temp plus a volatile call-site reread closes the final store/load live ranges. */
