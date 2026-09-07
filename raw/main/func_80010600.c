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

M2C_UNK func_800233D0();                      /* extern */
M2C_UNK func_80023470();       /* extern */
M2C_UNK func_8002352C();                            /* extern */
M2C_UNK func_800235A0();    /* extern */

void func_80023600(void *arg0) {
    s32 var_t3;
    s32 var_t2;
    s32 var_t1;
    s32 var_t0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    void *var_a0;

    M2C_FIELD(arg0, s32 *, 0x80) = 1;
    M2C_FIELD(arg0, s32 *, 0x84) = 1;
    func_8002352C();
    func_800235A0(arg0 + 4, 0x36, 0x10);
    func_800233D0(arg0);
    var_a3 = 0;
    var_t3 = 0x8E;
    var_t2 = 9;
    var_t1 = 0x42;
    var_t0 = 0x24;
    var_a1 = 0xA;
    var_a2 = 0x82;
    var_a0 = arg0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x1A0), void **, 4), s16 *, 0xA) = 0x1A;
    do {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1D8), void **, 4), s16 *, 8) = var_t3;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1D8), void **, 4), s16 *, 0xA) = var_a2;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1A8), void **, 4), s16 *, 8) = var_t2;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1A8), void **, 4), s16 *, 0xA) = var_a1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1B8), void **, 4), s16 *, 8) = var_t1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1B8), void **, 4), s16 *, 0xA) = var_a1;
        var_a3 += 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1C8), void **, 4), s16 *, 8) = var_t0;
        var_a2 += 0x10;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(var_a0, void **, 0x1C8), void **, 4), s16 *, 0xA) = var_a1;
        var_a0 += 4;
        var_a1 += 0x10;
    } while (var_a3 < 3);
    func_80023470(arg0, var_a1, var_a2, var_a3);
}
