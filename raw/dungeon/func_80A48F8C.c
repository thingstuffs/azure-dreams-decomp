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

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_8017140C[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_8017587C;
extern s16 D_80083228[5];
extern s32 func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(u32);
extern void func_800AD594(void *, s32);
extern void func_80047784(void *, u8, s32);

void func_8017278C(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 temp_v0;
    s32 one;
    s32 status;
    u8 *table;

    one = 1;
    status = M2C_FIELD(arg0, u8 *, 0x9B);
    if (status == one) {
        goto state_1;
    }
    if (status < 2) {
        if (status == 0) {
            goto state_0_set;
        }
        goto cleanup;
    } else {
        if (status == 2) {
            goto state_2;
        }
        if (status != 3) {
            goto cleanup;
        }
        goto state_3;
    }

state_0_set:
    M2C_FIELD(arg0, u8 *, 0x9B) = one;

state_1:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
        func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
        goto cleanup;
    }

state_0:
    table = &D_8017587C;
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg2, u8 **, 0x2C) = table;
    func_80047784(arg2, table[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x96) = 9;
    M2C_FIELD(arg0, u8 *, 0x9B)++;
    goto cleanup;

state_2:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto cleanup;
    }
    func_800A56E0(0x804);
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    M2C_FIELD(arg0, u8 *, 0x9B)++;
    goto cleanup;

state_3:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800AD594(arg3, 0x100);
        M2C_FIELD(arg0, u8 **, 0x8C) = D_8017140C;
        *D_8008346C = 0;
        func_800A4ACC(arg3);
        if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        } else {
            *D_800E3DE8 = arg3 - 0x20;
        }
    }

cleanup:
    return;
}
