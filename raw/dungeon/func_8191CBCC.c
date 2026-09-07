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

void func_80024554(void) __attribute__((noreturn));                /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                             /* extern */
typedef struct { s32 w0, w1, w2, w3, w4, w5; } Blk24;
extern M2C_UNK D_80024288;
extern M2C_UNK D_80024F74;
extern M2C_UNK D_80045C34;

s32 func_8191CBCC(void *arg0, void *arg1) {
    register void *held_arg0 ASM_REG("$19") = arg0;
    register void *held_arg1 ASM_REG("$20") = arg1;
    register void *tail_obj ASM_REG("$2");
    s16 temp_a0;
    s32 temp_v0_3;
    s32 temp_ret;
    s32 temp_v0_2;
    s32 tail_value;
    register s32 var_v0 ASM_REG("$2");
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    ASM_KEEP(held_arg0);
    ASM_KEEP(held_arg1);
    if (temp_v0 != NULL) {
        temp_s2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024288;
        M2C_FIELD(temp_v0, void **, 0x20) = held_arg0;
        M2C_FIELD(temp_s2, s16 *, 0xE) = 0;
        M2C_FIELD(temp_s2, s16 *, 0x10) = 0;
        temp_ret = rand();
        M2C_FIELD(temp_s2, s16 *, 0x12) = (s16)(temp_ret % 7);
        M2C_FIELD(temp_s2, u16 *, 0x14) = (u16) M2C_FIELD(held_arg0, u16 *, 0x12);
        M2C_FIELD(temp_s2, s16 *, 0x16) = (s16) (0x1C - M2C_FIELD(held_arg0, u16 *, 0x10));
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, M2C_UNK **, 8) = &D_80024F74;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x60);
        var_v0 = rand(temp_ret / 7);
        temp_v0_2 = var_v0;
        ASM_KEEP(var_v0);
        var_v0 >>= 0xC;
        if (temp_v0_2 < 0) {
            var_v0 = (s32) (temp_v0_2 + 0xFFF) >> 0xC;
        }
        var_v0 = temp_v0_2 - (var_v0 << 0xC);
        ASM_KEEP(var_v0);
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16)var_v0;
        temp_v0_3 = M2C_FIELD(held_arg0, s16 *, 0x10) << 8;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = temp_v0_3;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = temp_v0_3;
        func_8004491C(temp_v0, &D_80045C34);
        {
            register void *copy_dst ASM_REG("$5");

            copy_dst = M2C_FIELD(temp_v0, void **, 8);
            ASM_KEEP(copy_dst);
            *(Blk24 *) copy_dst = *(Blk24 *) held_arg1;
            temp_a0 = M2C_FIELD(temp_s2, s16 *, 0x14);
            tail_value = ((M2C_FIELD(copy_dst, s32 *, 0x14) * temp_a0) -
                          (M2C_FIELD(held_arg0, s16 *, 0x10) << 0x13)) / temp_a0;
            tail_obj = temp_v0;
            ASM_KEEP(tail_obj);
            M2C_FIELD(copy_dst, s32 *, 0x14) = tail_value;
            func_80024554();
        }
    }
    tail_obj = NULL;
    ASM_KEEP(tail_obj);
    return (s32)tail_obj;
}
