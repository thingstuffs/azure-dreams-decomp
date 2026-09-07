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

void func_80167354(void) __attribute__((noreturn));
extern M2C_UNK D_800814A0;

void func_801671AC(void *arg0, void *arg1, void *arg2) {
    register void *obj ASM_REG("$7");
    s16 temp_v1;
    s16 temp_v1_2;
    s32 var_a1;
    s32 var_t0;
    s32 var_t1;
    u16 count;
    u16 flags;
    u16 temp_v0;

    flags = M2C_FIELD(arg2, u16 *, 0x14);
    ASM_CLOBBER("$7");
    obj = arg0;
    ASM_KEEP(obj);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (flags & 0xFF7F);
    count = M2C_FIELD(obj, u16 *, 0x18);
    ASM_SCHED_BARRIER();
    temp_v0 = M2C_FIELD(obj, u16 *, 0x1C);
    count--;
    ASM_SCHED_BARRIER();
    temp_v0++;
    M2C_FIELD(obj, u16 *, 0x1C) = temp_v0;
    M2C_FIELD(obj, u16 *, 0x18) = count;
    if ((s16) temp_v0 == 3) {
        M2C_FIELD(obj, u16 *, 0x1C) = 0U;
    }
    var_t1 = 0x30;
    var_t0 = var_t1;
    temp_v1 = (s16) M2C_FIELD(obj, u16 *, 0x1C);
    var_a1 = 0x30;
    if (temp_v1 == 0) {
        var_a1 = 0x54;
    }
    if (temp_v1 == 1) {
        var_t0 = 0x54;
    }
    if (temp_v1 == 2) {
        var_t1 = 0x54;
    }
    temp_v1_2 = (s16) M2C_FIELD(obj, u16 *, 0x18);
    if (temp_v1_2 < 0x14) {
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((var_a1 * temp_v1_2) / 20);
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((var_t0 * (s16) M2C_FIELD(obj, u16 *, 0x18)) / 20);
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((var_t1 * (s16) M2C_FIELD(obj, u16 *, 0x18)) / 20);
        func_80167354();
    }
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((var_a1 * (0x1E - temp_v1_2)) / 10);
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((var_t0 * (0x1E - (s16) M2C_FIELD(obj, u16 *, 0x18))) / 10);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((var_t1 * (0x1E - (s16) M2C_FIELD(obj, u16 *, 0x18))) / 10);
    if ((s16) M2C_FIELD(obj, u16 *, 0x18) <= 0) {
        M2C_FIELD(obj, u16 *, -2) = (u16) (M2C_FIELD(obj, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
