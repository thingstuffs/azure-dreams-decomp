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

s32 func_80033B2C();                         /* extern */
M2C_UNK func_80094088();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_80094414();     /* extern */
M2C_UNK func_80094474();     /* extern */
M2C_UNK func_800944BC();     /* extern */
M2C_UNK func_8009451C();     /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
s32 func_8009567C(void *);            /* extern */
s32 func_80095840();               /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800CFCEF;
extern M2C_UNK D_800FE488;

void func_80092320(void *arg0, void *arg1, M2C_UNK arg2) {
    u8 *state = D_80083160;
    s16 temp_v0;
    s32 temp_v0_3;
    u16 temp_v0_2;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80095094(arg1);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if ((temp_v0 - M2C_FIELD(arg1, s16 *, 0xA)) >= 4) {
        if (M2C_FIELD(&D_800CFCEF, u8 *, 0) == 0) {
            func_80094378(arg0, arg1, arg2);
            goto block_end;
        }
        goto block_6;
    }
    if (M2C_FIELD(&D_800CFCEF, u8 *, 0) == 0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
    }
block_6:
    if (M2C_FIELD(state, s32 *, 0x10) & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        goto block_end;
    }
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_2;
    if ((s16) temp_v0_2 < 0) {
        func_80094414(arg0, arg1, arg2);
        goto block_end;
    }
    if (M2C_FIELD(state, s32 *, 0x10) & 0x40) {
        temp_v0_3 = func_80095840(arg0, &D_800CFCB4);
        if (temp_v0_3 != 0) {
            if (temp_v0_3 == 2) {
                func_8009451C(arg0, arg1, arg2);
                goto block_end;
            }
            func_800944BC(arg0, arg1, arg2);
            goto block_end;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(arg0, arg1, arg2);
            goto block_end;
        }
    } else if (func_8009567C(&D_800CFCB4) <= 0) {
        func_80094474(arg0, arg1, arg2);
    }
block_end:
    return;
}

/* MECHANISM: A held D_80083160 base supplies s4 and the exact 0x28 frame/save contract.
   Shared D_800CFCEF addressing and a signed s16 timer test reproduce the body operations.
   Correct one-argument func_8009567C ABI removes the dead a1 word and its displacement cascade. */
