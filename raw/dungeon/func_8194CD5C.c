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

M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_800649A0();                            /* extern */
M2C_UNK func_80064A40();                            /* extern */
M2C_UNK func_80064B30();        /* extern */
extern M2C_UNK D_800814A0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} InputVector;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} OutputVector;

void func_8002455C(void *arg0, void *arg1, void *arg2) {
    InputVector sp10;
    OutputVector sp18;
    s32 temp_lo;
    u16 temp_v0_2;
    u8 temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x1A) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x1A) + 1);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + 0x100);
    M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
    sp10.x = (s16) ((s32) ((func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x2E)) >> 4) * M2C_FIELD(arg0, s16 *, 0x2C)) >> 8);
    temp_lo = (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x2E)) >> 4) * M2C_FIELD(arg0, s16 *, 0x2C);
    sp10.z = 0;
    sp10.y = (s16) (temp_lo >> 8);
    func_800649A0();
    func_80064B30(arg0 + 4, &sp10, &sp18);
    func_80064A40();
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + sp18.x);
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + sp18.y);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + sp18.z);
    if (M2C_FIELD(arg0, u8 *, 0x30) != 0) {
        M2C_FIELD(arg0, u8 *, 0x30) = 0U;
    }
    temp_v0 = M2C_FIELD(arg2, u8 *, 0xE) - 8;
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
    if (!(temp_v0 & 0xFF) || (temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x100, M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_2, M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_2, M2C_FIELD(arg2, u16 *, 0x1A) = (u16) M2C_FIELD(arg0, u16 *, 0x2E), func_800478B8(arg2), ((M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) != 0))) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Two six-byte vector aggregates force stack slots sp+0x10..0x14 and sp+0x18..0x1C,
   restoring the 0x30 frame and the s0/s1/s2-only save set.
   cdk -G0 plus a direct scalar D_800814A0 RMW removes the extra address addiu and closes the residue. */
