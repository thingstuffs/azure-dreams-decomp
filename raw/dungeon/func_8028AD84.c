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
#define M2C_SYNC() 0

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

/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_80083350[5];
typedef struct {
    s16 unk0;
    u16 value;
    s16 unk4;
} D_800EA000_Record;
extern D_800EA000_Record D_800EA000[];

s16 func_8001DD84(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4) {
    s32 var_a2 = arg2 - 1;
    s16 shift = D_80083350[0];
    s16 step;
    u16 var_t1;
    D_800EA000_Record *temp_t0;

    temp_t0 = &D_800EA000[((arg1 << shift) + arg0)];
    arg0 += arg3;
    step = arg4;
    arg1 += step;
    var_t1 = temp_t0->value;
    if (var_a2 > 0) {
        s16 loop_shift = shift;
        do {
            temp_t0 = &D_800EA000[((arg1 << loop_shift) + arg0)];
            if ((s16) temp_t0->value < (s16) var_t1) {
                var_t1 = temp_t0->value;
            }
            arg0 += arg3;
            var_a2 -= 1;
            arg1 += step;
        } while (var_a2 > 0);
    }
    return (s16) var_t1;
}
