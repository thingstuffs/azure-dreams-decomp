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

M2C_UNK func_80017684();                         /* extern */
M2C_UNK func_800176FC();                         /* extern */
s32 func_8001777C();                         /* extern */
s32 func_80017918();                                /* extern */
extern void *D_80016000;
extern s16 D_80017A6C;
extern s16 D_80017A74;

void func_80016100(void) {
    s16 *var_s0;
    s16 *var_s1;
    s32 temp_s3;
    s32 var_s2;

    temp_s3 = M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), s32 (**)(M2C_UNK), 0x330)(0);
    var_s2 = 0;
    var_s0 = &D_80017A6C;
    var_s1 = &D_80017A74;
loop_1:
    if (temp_s3 == *var_s1) {
        func_80017684(*var_s0++);
    } else {
        func_800176FC(*var_s0++);
    }
    var_s1 += 1;
    var_s2 += 1;
    if (var_s2 >= 4) {
        if (M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), s32 (**)(M2C_UNK), 0x334)(0) != 5) {
            func_80017684(0xBE0);
        } else {
            func_800176FC(0xBE0);
        }
        if ((func_80017918() < 5) || ((func_80017918() >= 5) && (func_8001777C(0x1460) != 0))) {
            func_80017684(0xBE1);
        } else {
            func_800176FC(0xBE1);
        }
        return;
    }
    goto loop_1;
}
