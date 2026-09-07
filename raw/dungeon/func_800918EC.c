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

M2C_UNK func_80095DD0(); /* extern */
M2C_UNK func_80097188();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80096384;

void func_8009704C(void *arg0, void *arg1, void *arg2, M2C_UNK arg3) {
    s16 temp_v0;
    u16 temp_v1;
    register s8 *state = (s8 *)&D_80083460;
    register M2C_UNK saved_arg3 ASM_REG("$19");
    ASM_KEEP(state);
    saved_arg3 = arg3;

    if (M2C_FIELD(state, u16 *, 2) & 0x80) {
        M2C_FIELD(state, s16 *, 4) = 0;
    }
    if (M2C_FIELD(state, s16 *, 4) != 0) {
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(state, s16 *, 4));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) ((((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(state, s16 *, 4));
    }
    do { temp_v1 = M2C_FIELD(arg0, u16 *, 0xA2); } while (0);
    if (!(temp_v1 & 0x10)) {
        M2C_FIELD(arg0, u16 *, 0xA2) = (u16) (temp_v1 | 1);
    }
    temp_v0 = (u16) M2C_FIELD(state, s16 *, 4) - 1;
    M2C_FIELD(state, s16 *, 4) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(state, s16 *, 4) = 0;
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x4000);
        if (M2C_FIELD(arg0, s16 *, 0x100) >= 0) {
            func_80095DD0(arg0, arg1, arg2, saved_arg3);
            func_80097188();
            return;
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80096384;
        ASM_KEEP(saved_arg3);
    }
}

/* MECHANISM: An early guarded keep makes &D_80083460 an opaque held base, preserving alias reloads.
   An explicit $s3 ABI local schedules arg3 into the first branch slot; its keep lives on the cold path.
   2.7.2-cdk-G0 supplies retail's v0-to-a1 split address materialization. */
