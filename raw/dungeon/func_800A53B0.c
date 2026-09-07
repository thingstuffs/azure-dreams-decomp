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

s32 func_80042900(void *, s32);
s32 func_800A1C58(void *);
void func_800A1D4C(void *, s32);
void func_800A56E0(s32);
s32 func_800AAC8C(void);
void func_800C77D0(void *, s32, s32, s32);
extern u16 D_80013714;
extern s32 D_8007359C;
extern s8 D_80080A88;
extern s8 D_80080AA0;
extern M2C_UNK D_80083460;
extern s32 D_800E296C;

s32 func_800AAB10(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    s32 var_s1;
    u8 temp_a0;
    u8 *state;

    var_s1 = 0;
    if (D_800E296C & 0x100000) {
        state = (u8 *)&D_80083460;
        if (M2C_FIELD(state, s32 *, 0xC) != 0) {
            if (M2C_FIELD(state, s32 *, 0xC) == arg3) {
                if (M2C_FIELD(state, s16 *, 0xA) == 0) {
                    if (!(M2C_FIELD(state, u16 *, 2) & 8)) {
                        func_800C77D0((void *)(arg0 - 0x20), arg1, 8, 0x300);
                        func_800A1D4C(arg3, 1);
                        func_800A56E0(0x201);
                        if (!(D_80013714 & 2)) {
                            D_80080AA0 = 1;
                            D_80080A88 = 0;
                        }
                        if (!(M2C_FIELD(arg3, s32 *, 0x54) & 0x800000) && (M2C_FIELD(arg3, s32 *, 0x14) & 0x4000)) {
                            temp_a0 = M2C_FIELD(arg3, u8 *, 0x13);
                            if ((M2C_FIELD(((temp_a0 * 0x14) + D_8007359C), u16 *, -0x14) & 0x80) && (temp_a0 >= 2U) && ((u8) M2C_FIELD(arg3, u8 *, 0x11) >= 0x14U) && !(M2C_FIELD(arg3, s32 *, 0x1C) & 0x228) && ((func_80042900(arg3, 0x18) << 0x10) == 0)) {
                                var_s1 = 1;
                            }
                        }
                        if ((func_800A1C58(arg3) << 0x10) == 0) {
                            goto clear_state;
                        }
                        goto tail_call;
                    }
                }
            }
            return 0;
        }
        goto tail_call;
    }
    goto return_result;
tail_call:
    func_800AAC8C();
    return 0;
clear_state:
    M2C_FIELD(&D_80083460, s32 *, 0xC) = 0;
return_result:
    return var_s1;
}

/* MECHANISM: cdk-G0 holds D_80083460 in $v1 with the retail 0x20 frame and s0/s1 saves.
   The four-argument copy call preserves arg1 while setting a2/a3 in the retail slots.
   Lexical tail/store/return labels select SHAPE-C and make the outer false edge skip the store. */
