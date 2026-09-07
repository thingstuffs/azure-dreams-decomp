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

void *func_8003FC64();                       /* extern */
M2C_UNK bzero();             /* extern */
s32 func_800AE500();                     /* extern */
s32 func_800AEFD8(); /* extern */
M2C_UNK func_800B06C4();                      /* extern */
extern M2C_UNK D_800B0490;

void *func_800B05DC(s32 arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_s0;
    void *var_s1;

    var_s1 = func_8003FC64(0);
    if (var_s1 != NULL) {
        temp_s0 = var_s1 + 0x20;
        M2C_FIELD(temp_s0, s32 *, 8) = arg0;
        M2C_FIELD(temp_s0, s32 *, 0xC) = arg4;
        M2C_FIELD(temp_s0, s32 *, 0x14) = arg1;
        bzero(temp_s0, 4);
        temp_v0 = func_800AE500(temp_s0, arg4);
        M2C_FIELD(temp_s0, s32 *, 0x18) = temp_v0;
        if (temp_v0 != 0) {
            M2C_FIELD(var_s1, M2C_UNK **, 0x10) = &D_800B0490;
            temp_v0_2 = func_800AEFD8(var_s1, arg2, arg3, arg1, M2C_FIELD(temp_s0, s32 *, 0x18), temp_s0);
            M2C_FIELD(temp_s0, s32 *, 4) = temp_v0_2;
            if (temp_v0_2 == 0) {
                func_800B06C4(temp_s0);
                var_s1 = NULL;
            }
        }
    }
    return var_s1;
}
