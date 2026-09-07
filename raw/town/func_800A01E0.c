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

void func_8009D940(void *arg0, void *arg1, void **arg2, void **arg3) {
    s32 temp_a0;
    s32 temp_t1;
    void **var_a2;
    void **var_a3;
    void *temp_t0;

    var_a2 = arg2;
    var_a3 = arg3;
    if (*var_a2 != NULL) {
        do {
            temp_t0 = *var_a2;
            temp_t1 = M2C_FIELD(temp_t0, s16 *, 0) + M2C_FIELD(temp_t0, s16 *, 4);
            if (M2C_FIELD(arg0, s16 *, 0) >= temp_t1) {
                temp_a0 = M2C_FIELD(temp_t0, s16 *, 2) + M2C_FIELD(temp_t0, s16 *, 6);
                if ((M2C_FIELD(arg0, s16 *, 2) >= temp_a0) && ((temp_t1 + M2C_FIELD(temp_t0, s16 *, 8)) >= M2C_FIELD(arg1, s16 *, 0)) && ((temp_a0 + M2C_FIELD(temp_t0, s16 *, 0xA)) >= M2C_FIELD(arg1, s16 *, 2))) {
                    *var_a3 = temp_t0;
                    var_a3 = (void **)((s8 *)((void **)((s8 *)var_a3 + 4)));
                }
            }
            var_a2 = (void **)((s8 *)((void **)((s8 *)var_a2 + 4)));
        } while (*var_a2 != NULL);
    }
    *var_a3 = NULL;
}
