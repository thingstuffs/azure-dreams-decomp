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

M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800A2DB8();                      /* extern */
M2C_UNK func_800A32A4();                      /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;

void func_800B2FAC(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 flags;
    u8 var_a0;
    u8 var_a1;
    s32 *global;

    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        global = &D_80083460;
        if (global[4] == (arg3 - 0x20)) {
            global[4] = global[4] & 0x7FFFFFFF;
        }
        func_800A2DB8(arg3);
        func_800A32A4(arg3);
        flags = M2C_FIELD(arg3, s32 *, 0x1C);
        var_a0 = M2C_FIELD(arg2, u8 *, 0x24);
        var_a1 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(var_a0, var_a1, var_a2);
        func_8009A028(arg3);
        M2C_FIELD(arg3, u16 *, -2) = (u16) (M2C_FIELD(arg3, u16 *, -2) | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}

/* MECHANISM: Four-argument ABI holds arg2/arg3 in s1/s0 and yields the retail 0x20 frame/save order.
   A named D_80083460 base forces cdk's split lui/addiu plus the 0x10 field displacement.
   Cached flag/byte locals expose retail load scheduling; a direct D_800814A0 update removes the extra address word. */
