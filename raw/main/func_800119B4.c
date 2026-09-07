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

extern void *func_8004DA74(void *a0, u8 *a1, s32 a2);
extern u8 *D_800283EC[];

void func_800249B4(void *arg0) {
    s32 var_t0;
    s16 var_t1;
    s16 var_a3;
    s32 var_a2;
    void *temp_a0;
    void *temp_v0;
    void *temp_v1;
    void *var_a1;

    func_8004DA74((u8 *)arg0 + 0x84, D_800283EC[0], 1);
    func_8004DA74((u8 *)arg0 + 0x204, D_800283EC[1], 1);
    var_t0 = 0;
    var_t1 = 0xA9;
    var_a3 = 0x110;
    var_a2 = 0x84;
    var_a1 = arg0;
    do {
        temp_a0 = (u8 *)arg0 + var_a2;
        temp_v0 = M2C_FIELD(var_a1, void **, 0xB4C);
        var_a2 += 0x180;
        temp_v1 = M2C_FIELD(temp_v0, void **, 4);
        var_a1 = (u8 *)var_a1 + 4;
        M2C_FIELD(temp_v0, s32 *, 0) = temp_a0;
        M2C_FIELD(temp_v1, s16 *, 8) = var_t1;
        var_t0 += 1;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s16 *, 0xA) = var_a3;
        var_a3 += 0x10;
    } while (var_t0 < 2);
}
