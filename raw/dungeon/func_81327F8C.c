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

M2C_UNK func_80047784();         /* extern */
s32 func_8009A180();                     /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
M2C_UNK func_800AA258(); /* extern */
s32 func_800AA6B4(); /* extern */
M2C_UNK func_800AA888(); /* extern */
void func_8016FA60(void) __attribute__((noreturn));
M2C_UNK func_8016FA84();                            /* extern */
M2C_UNK func_8016FCE4(); /* extern */
s32 func_80170224(); /* extern */
M2C_UNK func_8017092C(); /* extern */
M2C_UNK func_80174320();     /* extern */
extern u16 D_80013714;
extern void *D_800814A8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174A2C[];
extern u8 D_80174A64[];

void func_8016F78C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    u8 stack_pad[8];
    u8 state;
    s32 state_id;

    if (D_80083462 & 0x1000) {
        M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
        func_8016FA84();
        func_8016FA60();
        return;
    }
    if (!(D_80083462 & 0x2000)) {
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_8016FA60();
            return;
        }
        state = M2C_FIELD(arg0, volatile u8 *, 0x9A);
        state_id = 0xE;
        if (state != state_id) {
            if (M2C_FIELD(arg2, u8 **, 0x2C) != D_80174A2C) {
                M2C_FIELD(arg2, u8 **, 0x2C) = D_80174A2C;
                func_80047784(arg2, D_80174A2C[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            }
            M2C_FIELD(arg0, u8 *, 0x9A) = state_id;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
        if ((M2C_FIELD(arg3, s16 *, 0x64) == 0) || (func_800AA6B4(arg0, arg1, arg2, D_80174A64) == 0)) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_8017092C(arg0, arg1, arg2, arg3);
                M2C_FIELD(arg2, u8 **, 0x2C) = D_80174A2C;
                func_80047784(arg2, D_80174A2C[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
                M2C_FIELD(arg0, s32 *, 0x90) = 0;
                func_8016FA60();
                return;
            }
            goto block_16;
        }
    } else {
block_16:
        M2C_FIELD(arg2, s8 *, 0x26) = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        if (M2C_FIELD(arg3, s8 *, 0x6D) > 0) {
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
                func_800A9A0C(arg3);
                func_8016FA60();
                return;
            }
            if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
                if (!(D_80083462 & 0x2000) || ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0)) {
                    if (D_80013714 & 8) {
                        func_80174320(arg0, arg1, arg2);
                        M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
                        func_800A9A0C(arg3);
                        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                        func_8016FA60();
                        return;
                    }
                    if ((func_80170224(arg0, arg1, arg2, 0) << 0x10) != 0) {
                        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) | 0x4000);
                        goto block_28;
                    }
                }
            } else {
block_28:
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
                func_800A9A0C(arg3);
                func_8016FCE4(arg0, arg1, arg2, arg3);
            }
        }
    }
}
