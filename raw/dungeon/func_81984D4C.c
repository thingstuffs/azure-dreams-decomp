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

struct S_81984D4C_local {
    /* 0x00 */ char pad0[0x94];
    /* 0x94 */ u16 unk94;                           /* inferred */
    /* 0x96 */ u16 unk96;                           /* inferred */
    /* 0x98 */ s16 unk98;                           /* inferred */
    /* 0x9A */ char pad9A[0xA];                     /* maybe part of unk98[6]? */
    /* 0xA4 */ s16 unkA4;                           /* inferred */
    /* 0xA6 */ s16 unkA6;                           /* inferred */
    /* 0xA8 */ s16 unkA8;                           /* inferred */
    /* 0xAA */ char padAA[0xA];                     /* maybe part of unkA8[6]? */
    /* 0xB4 */ void (*callback)();
    /* 0xB8 */ void *field_B8;
    /* 0xBC */ char padBC[0x1C];                    /* maybe part of field_B8[8]? */
    /* 0xD8 */ void *ptr;
};                                                  /* size = 0xDC */

extern u8 D_80026BE4[16];
extern u8 D_800E3D20[16];

void func_81984D4C(void *arg0) {
    s16 temp_a0;
    s16 temp_v0;
    void *temp_v1;
    u8 *state;
    u8 *timer;
    u8 *flag;

    temp_a0 = M2C_FIELD(arg0, s16 *, 0x24);
    state = (u8 *)&D_80083178;
    if (temp_a0 > 0) {
        M2C_FIELD(state, u16 *, 0x98) = (u16) M2C_FIELD(state, u16 *, 0x98) + ((s32) (M2C_FIELD(arg0, s16 *, 0x26) - M2C_FIELD(state, s16 *, 0x98)) / temp_a0);
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x24) - 1;
    M2C_FIELD(arg0, s16 *, 0x24) = temp_v0;
    if (temp_v0 < -0x80) {
        M2C_FIELD(arg0, s16 *, 0x24) = -0x80;
    }
    timer = D_800E3D20;
    if (M2C_FIELD(timer, u8 *, 0) != 0) {
        M2C_FIELD(timer, s8 *, 0) = (s8) (M2C_FIELD(timer, u8 *, 0) - 1);
    }
    temp_v1 = M2C_FIELD(arg0, void * volatile *, 0xC);
    M2C_FIELD(arg0, u16 *, 4) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), u16 *, 2);
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(temp_v1, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(temp_v1, u16 *, 0xA);
    M2C_FIELD(state, u16 *, 0xA4) = (u16) M2C_FIELD(state, u16 *, 0xA4) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 4) - M2C_FIELD(state, s16 *, 0xA4)) >> 2);
    M2C_FIELD(state, u16 *, 0xA6) = (u16) M2C_FIELD(state, u16 *, 0xA6) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 6) - M2C_FIELD(state, s16 *, 0xA6)) >> 2);
    flag = D_80026BE4;
    if (M2C_FIELD(flag, u8 *, 0) != 0) {
        M2C_FIELD(state, u16 *, 0xA8) = (u16) M2C_FIELD(state, u16 *, 0xA8) + ((s32) ((s16) M2C_FIELD(arg0, u16 *, 8) - M2C_FIELD(state, s16 *, 0xA8)) >> 2);
    }
    M2C_FIELD(flag, s8 *, 0) = (s8) (M2C_FIELD(state, s16 *, 0xA8) != (s16) M2C_FIELD(arg0, u16 *, 8));
    M2C_FIELD(state, u16 *, 0x94) = (u16) ((s32) (M2C_FIELD(state, u16 *, 0x94) << 0x10) >> 0x12);
    M2C_FIELD(state, u16 *, 0x96) = (u16) ((s32) (M2C_FIELD(state, u16 *, 0x96) << 0x10) >> 0x12);
}

/* MECHANISM: Frameless leaf; arg0 stays in a1 and D_80083178 in a2 across the CFG.
   A volatile cached read of arg0+0xC prevents CSE with the direct first-use load,
   producing retail's paired lw v0/v1 and keeping v1 live for offsets 6/0xA. */
