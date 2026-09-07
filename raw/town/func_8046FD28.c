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

s32 func_8001628C();           /* extern */
s32 func_80017E98();                                /* extern */
s32 func_80019A04();         /* extern */
s32 func_80019ABC(); /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_8001A97C;
extern M2C_UNK D_8001B1FC;
extern M2C_UNK D_8001B63C;
extern M2C_UNK D_8001CDF2;

s32 func_80016D28(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_s1;

    if (func_80017E98() != 0) {
        register s32 page ASM_REG("$2");

        page = (s32) 0x80020000;
        ASM_KEEP(page);
        return page - 0x49C4;
    }
    var_s1 = func_80019ABC(&D_8001A97C, &D_8001B1FC, arg0, arg2);
    if (func_80019A04(&D_8001A97C, arg0, arg2) != 0) {
        if (func_8001A510(0x799) != 0) {
            register s32 page ASM_REG("$2");

            page = (s32) 0x80020000;
            ASM_KEEP(page);
            var_s1 = page - 0x320E;
        } else {
            var_s1 = func_8001628C(arg0, arg1, arg2);
        }
    }
    return var_s1;
}

/* MECHANISM: The true-space name makes the in-row targets local CFG joins instead of phantom calls.
   Short-lived guarded v0 page carriers produce the split 0x80020000/addiu constants in delay slots.
   One s1 result live range across both arms preserves the 0x28 frame and fallback copy/join. */
