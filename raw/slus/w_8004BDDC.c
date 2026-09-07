#include "common.h"

/* first_pass warm draft: compiles, best score 115 @ 2.7.2 */
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

M2C_UNK func_8004C010();                 /* extern */

void *func_8004BDDC(s32 arg0, s32 arg1, void *arg2, void *arg3, void *arg4) {
    register void *temp_s3 ASM_REG("$19");
    s8 temp_v0;
    s8 temp_v1_3;
    u8 temp_v1;
    u8 temp_v1_2;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;

    M2C_FIELD(arg2, s32 *, 0x2C) = (s32) M2C_FIELD(arg2, s32 *, 0x20);
    M2C_FIELD(arg2, s32 *, 0x20) = (s32) M2C_FIELD(arg2, s32 *, 0x18);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) M2C_FIELD(arg2, s32 *, 0x10);
    temp_s3 = arg3;
    {
        u8 f8 = *(volatile u8 *) ((u8 *) arg4 + 8);
        temp_v1 = *(volatile u8 *) ((u8 *) arg4 + 0xA);
        if ((temp_v1 + f8) >= 0x100) {
            M2C_FIELD(arg4, u8 *, 0xA) = (u8) (temp_v1 - 1);
        }
    }
    {
        u8 f9 = *(volatile u8 *) ((u8 *) arg4 + 9);
        temp_v1_2 = *(volatile u8 *) ((u8 *) arg4 + 0xB);
        if ((temp_v1_2 + f9) >= 0x100) {
            M2C_FIELD(arg4, u8 *, 0xB) = (u8) (temp_v1_2 - 1);
        }
    }
    temp_s3 = (void *) ((u8 *) temp_s3 + 0xC);
    temp_s0 = arg2 + 0x10;
    M2C_FIELD(arg2, s32 *, 0x10) = (s32) M2C_FIELD(temp_s3, s32 *, 0);
    M2C_FIELD(arg2, u8 *, 4) = (u8) M2C_FIELD(arg2, u8 *, 0x13);
    func_8004C010(temp_s0, arg0);
    func_8004C010(temp_s0, arg1);
    temp_s0_2 = arg2 + 0x1C;
    M2C_FIELD(arg2, s32 *, 0x1C) = (s32) M2C_FIELD(temp_s3, s32 *, 4);
    M2C_FIELD(arg2, u8 *, 5) = (u8) M2C_FIELD(arg2, u8 *, 0x1F);
    func_8004C010(temp_s0_2, arg0);
    func_8004C010(temp_s0_2, arg1);
    temp_s0_3 = arg2 + 0x28;
    M2C_FIELD(arg2, s32 *, 0x28) = (s32) M2C_FIELD(temp_s3, s32 *, 8);
    M2C_FIELD(arg2, u8 *, 6) = (u8) M2C_FIELD(arg2, u8 *, 0x2B);
    func_8004C010(temp_s0_3, arg0);
    func_8004C010(temp_s0_3, arg1);
    temp_s0_4 = arg2 + 4;
    func_8004C010(temp_s0_4, arg0);
    func_8004C010(temp_s0_4, arg1);
    M2C_FIELD(arg2, s8 *, 3) = 0xC;
    M2C_FIELD(arg2, u8 *, 7) = (u8) M2C_FIELD(arg4, u8 *, 1);
    M2C_FIELD(arg2, u8 *, 0xC) = (u8) M2C_FIELD(arg4, u8 *, 8);
    M2C_FIELD(arg2, u16 *, 0xE) = (u16) M2C_FIELD(arg4, u16 *, 6);
    M2C_FIELD(arg2, u8 *, 0xD) = (u8) M2C_FIELD(arg4, u8 *, 9);
    if ((M2C_FIELD(arg2, s16 *, 0x14) < M2C_FIELD(arg2, s16 *, 8)) ||
        (M2C_FIELD(arg2, s16 *, 8) != M2C_FIELD(arg2, s16 *, 0x20))) {
        M2C_FIELD(arg4, u8 *, 0xA) = (u8) (M2C_FIELD(arg4, u8 *, 0xA) - 1);
    }
    temp_v0 = M2C_FIELD(arg4, u8 *, 8) + M2C_FIELD(arg4, u8 *, 0xA);
    M2C_FIELD(arg2, s8 *, 0x30) = temp_v0;
    M2C_FIELD(arg2, s8 *, 0x18) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0x19) = (u8) M2C_FIELD(arg4, u8 *, 9);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) M2C_FIELD(arg4, u16 *, 4);
    M2C_FIELD(arg2, u8 *, 0x24) = (u8) M2C_FIELD(arg4, u8 *, 8);
    if ((M2C_FIELD(arg2, s16 *, 0x22) < M2C_FIELD(arg2, s16 *, 0xA)) ||
        (M2C_FIELD(arg2, s16 *, 0xA) != M2C_FIELD(arg2, s16 *, 0x16))) {
        M2C_FIELD(arg4, u8 *, 0xB) = (u8) (M2C_FIELD(arg4, u8 *, 0xB) - 1);
    }
    temp_v1_3 = M2C_FIELD(arg4, u8 *, 9) + M2C_FIELD(arg4, u8 *, 0xB);
    M2C_FIELD(arg2, s8 *, 0x31) = temp_v1_3;
    M2C_FIELD(arg2, s8 *, 0x25) = temp_v1_3;
    return temp_s3;
}
