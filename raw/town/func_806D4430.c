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

M2C_UNK *func_80016E00();                        /* extern */
s32 func_800178A8();             /* extern */
M2C_UNK *func_80017960(); /* extern */
s32 func_8001868C();                         /* extern */
s32 func_80018868();                /* extern */
M2C_UNK func_800188E8();       /* extern */
extern M2C_UNK D_800189BC;
extern M2C_UNK D_80018B94;
extern M2C_UNK D_8001A04A;

M2C_UNK *func_806D4430(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK *result;
    s32 temp_s0;

    result = func_80016E00(arg2);
    if (result != NULL) {
        return result;
    }
    result = func_80017960(&D_800189BC, &D_80018B94, arg0, arg2);
    temp_s0 = func_80018868(0x990, 2);
    if (func_8001868C(0x997) == 0) {
        temp_s0++;
        if (temp_s0 == 3) {
            temp_s0 = 0;
        }
        func_800188E8(0x990, temp_s0, 2);
    }
    if ((arg2 == 0xB) && (func_800178A8(&D_800189BC, arg0, 0xB) != 0)) {
        result = &D_8001A04A;
    }
    return result;
}

/* MECHANISM: Preserve the unused middle ABI argument so arg2 arrives in a2 and
   merge both result paths into s1 and mutate the cursor directly in s0.
   The cdk schedule fills the early branch slot and preserves the 0x28 frame. */
