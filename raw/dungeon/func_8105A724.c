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

void func_80047784(void *, u8, s32);
void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80173FB8[];

s32 func_80171F24(void *arg0, s32 arg1, void *arg2, void *arg3) {
    volatile s64 frame_pad;
    s32 result;
    u16 flags;
    u16 dead_mask;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (D_80083462 & 0x2000) {
        goto late_failure;
    }

    result = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24),
        M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x2A));

    if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x8000)) {
        goto no_flag;
    }
    if (result != 0) {
        goto checks;
    }
early_zero:
    return 0;

no_flag:
    if ((func_800A2CB8(arg3, result) << 0x10) == 0) {
        goto return_zero;
    }

checks:
    flags = D_80083462;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((u32)(((0 - func_800A0134(result, arg3)) + 0x40) & 0xFFFF) < 0x81U) {
        goto range_ok;
    }
return_zero:
    ASM_SCHED_BARRIER();
    return 0;

range_ok:
    if ((func_800A2B5C(arg3) << 0x10) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 0x10) == 0) {
        goto success;
    }

late_failure:
    return -1;

success:
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x11;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg3, s8 *, 0x84) = 0x7C;
    M2C_FIELD(arg3, s8 *, 0x85) = 0;
    dead_mask = M2C_FIELD(arg0, u16 *, 0x98) & 0x8000;
    ASM_KEEP(dead_mask);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80173FB8;
    func_80047784(arg2,
        D_80173FB8[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7],
        0);
    M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
    func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile s64 supplies retail's eight-byte frame object,
   while explicit CFG labels preserve the early-zero and shared late-failure blocks.
   The retained dead flag mask restores three tail words; a fence at the later
   zero-return join prevents jump-threading and closes the final return-slot residue. */
