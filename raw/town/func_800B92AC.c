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
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_8004B248();                      /* extern */
s32 func_800B677C();                             /* extern */
M2C_UNK func_800B691C(); /* extern */
s32 func_800B6990();                 /* extern */
void func_800B6AE8();                               /* extern */
extern M2C_UNK D_8004CAA0;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_800B6754;

void *func_800B6A0C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3, s32 arg4) {
    void *temp_s1;
    void *var_s0;

    var_s0 = func_8003FC64(0);
    temp_s1 = var_s0 + 0x20;
    if (var_s0 != NULL) {
        if (func_800B6990(temp_s1, 0x18) != 0) {
            M2C_FIELD(var_s0, void **, 0xC) = (void *) (var_s0 + 0xA8);
            M2C_FIELD(temp_s1, s32 *, 0x94) = func_800B677C(M2C_FIELD(temp_s1, s32 *, 0x98));
            func_800B691C(temp_s1, arg0, arg1, arg2, arg3, arg4);
            M2C_FIELD(var_s0, M2C_UNK **, 0x10) = &D_800B6754;
            func_8004491C(var_s0, &D_8004CAA0);
            func_800B6AE8();
            return var_s0;
        }
        func_8004B248(var_s0 + 0xBC);
        M2C_FIELD(var_s0, u16 *, 0x1E) = (u16) (M2C_FIELD(var_s0, u16 *, 0x1E) | 0x8000);
        var_s0 = NULL;
        D_800814A0 = (s32) (D_800814A0 | 0x8000);
    }
    return var_s0;
}
/* MECHANISM: Four incoming args stay live into the six-arg initializer, producing the retail
   s2/s4/s5/s3 holds while the allocation and its +0x20 base occupy s0/s1.
   Discarding the tail helper result returns s0; one shared fallthrough return removes the
   extra jump and its +1-word branch-displacement cascade after the direct global RMW. */
