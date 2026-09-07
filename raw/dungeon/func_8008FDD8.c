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

M2C_UNK func_8008D388();    /* extern */
M2C_UNK func_800982A8();              /* extern */
M2C_UNK func_80098614();              /* extern */
s32 func_80098920(); /* extern */
s32 func_8009FADC();                             /* extern */
extern M2C_UNK D_80082EB0;

s32 func_80095538(void *arg0, s16 arg1, s16 arg2) {
    s32 temp_s3;
    s32 temp_s4;
    register s32 var_s5 ASM_REG("$21");
    s32 var_v0;
    u8 temp_v0;
    void *var_s1;
    void *var_a1;
    void *var_a1_2;

    var_s1 = arg0;
    temp_s3 = M2C_FIELD(var_s1, s32 *, -0x18);
    temp_s4 = M2C_FIELD(var_s1, s32 *, -0x14);
    var_s5 = 1;
    ASM_KEEP_NV(var_s5);
    M2C_FIELD(&D_80082EB0, s32 *, 0) = func_8009FADC(arg1);
    if (arg2 != 0) {
        M2C_FIELD(&D_80082EB0, s32 *, 4) = func_8009FADC(arg2);
    } else {
        M2C_FIELD(&D_80082EB0, s32 *, 4) = 0;
    }
    temp_v0 = M2C_FIELD(M2C_FIELD(&D_80082EB0, void **, 0), u8 *, 1);
    switch (temp_v0) {
    case 15:
    case 16:
        var_a1 = NULL;
        if (M2C_FIELD(&D_80082EB0, void **, 0) != M2C_FIELD(var_s1, s32 *, 0x4C)) {
            var_a1 = M2C_FIELD(&D_80082EB0, void **, 0);
        }
        func_800982A8(var_s1, var_a1);
        var_v0 = var_s5 << 0x10;
        goto return_lbl;
    case 17:
        var_a1_2 = NULL;
        if (M2C_FIELD(&D_80082EB0, void **, 0) != M2C_FIELD(var_s1, s32 *, 0x50)) {
            var_a1_2 = M2C_FIELD(&D_80082EB0, void **, 0);
        }
        func_80098614(var_s1, var_a1_2);
        var_v0 = var_s5 << 0x10;
        goto return_lbl;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        var_s5 = func_80098920(var_s1, M2C_FIELD(&D_80082EB0, void **, 0), 3, 0);
        goto block_13;
    case 18:
        M2C_FIELD(arg0, void **, 0xBC) = (void *) M2C_FIELD(&D_80082EB0, void **, 0);
        func_8008D388(arg0, temp_s3, temp_s4, var_s1);
        goto block_13;
    case 19:
    case 20:
    case 21:
    default:
        goto block_13;
    }
block_13:
    var_v0 = var_s5 << 0x10;
return_lbl:
    return var_v0 >> 0x10;
}

/* MECHANISM: Separate arg0 lifetimes hold the original in s6 and the working base in s1.
   A guarded s5 pin with ASM_KEEP_NV restores the retail save/color order without a sched barrier.
   The direct D_80082EB0 base and one shared post-switch shift remove the +1-word CFG cascade. */
