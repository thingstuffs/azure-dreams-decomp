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

s32 func_80016164();                                /* extern */
s32 func_800161C8();                         /* extern */
s32 func_80016224();                /* extern */
M2C_UNK func_8001A418();                     /* extern */
s32 func_8001A510();                         /* extern */
s32 func_8001A7F8();                                /* extern */
extern M2C_UNK D_8001E2F8;
extern M2C_UNK D_8001E634;
extern M2C_UNK D_8001E79C;
extern M2C_UNK D_8001E9C0;
extern M2C_UNK D_8001EB10;
extern M2C_UNK D_8001EC04;

M2C_UNK *func_8001628C(void) {
    M2C_UNK *var_s0;
    s32 temp_s0;

    if (func_80016164() != 0) {
        var_s0 = &D_8001EC04;
        goto done;
    }
    temp_s0 = func_8001A7F8();
    if ((func_8001A510(0x79A) == 0) && ((temp_s0 < 5) || (func_80016224(0x47E, 0x79A) != 0))) {
        var_s0 = &D_8001E2F8;
        goto selected;
    }
    if ((func_8001A510(0x79B) == 0) && ((temp_s0 < 0xA) || (func_80016224(0x47E, 0x79B) != 0))) {
        var_s0 = &D_8001E634;
        goto selected;
    }
    if ((func_8001A510(0x79C) == 0) && ((temp_s0 < 0xF) || (func_80016224(0x47E, 0x79C) != 0))) {
        var_s0 = &D_8001E79C;
        goto selected;
    }
    if (func_8001A510(0x79D) != 0) {
        goto use_default;
    }
    if ((temp_s0 < 0x19) && (func_800161C8() != 0)) {
        goto select_last;
    }
    if (func_80016224(0x47E, 0x79D) != 0) {
        goto select_last;
    }
    goto use_default;
select_last:
    var_s0 = &D_8001E9C0;
selected:
    func_8001A418(0x47E);
    goto finalize;
use_default:
    var_s0 = &D_8001EB10;
finalize:
    func_8001A418(0x7A3);
done:
    return var_s0;
}
/* MECHANISM: The true-space CFG turns apparent func_80016398/B0/B8 calls into local joins.
   One s0 result pointer and shared selection labels reproduce the 0x18 frame and tail layout.
   Omitting func_800161C8's explicit arg reuses the branch-delay a0 setup and closes word 58. */
