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

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_80024918;

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 word;
} Packed4;

typedef struct {
    s32 words[4];
} FourWords;

typedef struct {
    Packed4 part[2];
} Packed8;

void func_800249E4(s32 arg0, void *arg1, void *arg2, s16 arg3, FourWords arg4, FourWords arg8, Packed8 arg12) {
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 copy0;
    s32 copy1;
    s32 copy2;
    s32 copy3;
    s32 tail0;
    s32 tail1;
    void *temp_a0;
    register void *temp_v0 ASM_REG("$6");
    register u8 *stackbase ASM_REG("$29");

    temp_v0 = func_8003FC64(0x212);
    ASM_KEEP(temp_v0);
    if (temp_v0 != NULL) {
        temp_a0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024918;
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
        M2C_FIELD(temp_a0, s16 *, 0x74) = 0;
        M2C_FIELD(temp_a0, s16 *, 0x76) = arg3;
        temp_v0_2 = M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_a0, s32 *, 0x1C) = temp_v0_2;
        M2C_FIELD(temp_a0, s32 *, 0x34) = temp_v0_2;
        temp_v0_3 = M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_a0, s32 *, 0x20) = temp_v0_3;
        M2C_FIELD(temp_a0, s32 *, 0x38) = temp_v0_3;
        temp_v0_4 = M2C_FIELD(arg1, s32 *, 8);
        M2C_FIELD(temp_a0, s32 *, 0x24) = temp_v0_4;
        M2C_FIELD(temp_a0, s32 *, 0x3C) = temp_v0_4;
        M2C_FIELD(temp_a0, s32 *, 4) = (s32) M2C_FIELD(arg2, s32 *, 0);
        M2C_FIELD(temp_a0, s32 *, 8) = (s32) M2C_FIELD(arg2, s32 *, 4);
        M2C_FIELD(temp_a0, s32 *, 0xC) = (s32) M2C_FIELD(arg2, s32 *, 8);
        M2C_FIELD(temp_a0, s32 *, 0x40) = (s32) ((s32) (M2C_FIELD(arg2, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0)) >> 3);
        M2C_FIELD(temp_a0, s32 *, 0x44) = (s32) ((s32) (M2C_FIELD(arg2, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) >> 3);
        M2C_FIELD(temp_a0, s32 *, 0x48) = (s32) ((s32) (M2C_FIELD(arg2, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8)) >> 3);
        copy0 = arg4.words[0];
        copy1 = arg4.words[1];
        copy2 = arg4.words[2];
        copy3 = arg4.words[3];
        M2C_FIELD(temp_v0, s32 *, 0x6C) = copy0;
        M2C_FIELD(temp_v0, s32 *, 0x70) = copy1;
        M2C_FIELD(temp_v0, s32 *, 0x74) = copy2;
        M2C_FIELD(temp_v0, s32 *, 0x78) = copy3;
        copy0 = arg8.words[0];
        copy1 = arg8.words[1];
        copy2 = arg8.words[2];
        copy3 = arg8.words[3];
        M2C_FIELD(temp_v0, s32 *, 0x7C) = copy0;
        M2C_FIELD(temp_v0, s32 *, 0x80) = copy1;
        M2C_FIELD(temp_v0, s32 *, 0x84) = copy2;
        M2C_FIELD(temp_v0, s32 *, 0x88) = copy3;
        stackbase = (u8 *)&arg12 - 0x58;
        ASM_KEEP(stackbase);
        tail0 = M2C_FIELD(stackbase, Packed4 *, 0x58).word;
        tail1 = M2C_FIELD(stackbase, Packed4 *, 0x5C).word;
        M2C_FIELD(temp_v0, Packed4 *, 0x8C).word = tail0;
        M2C_FIELD(temp_v0, Packed4 *, 0x90).word = tail1;
    }
}

/* MECHANISM: Two 16-byte plus one packed 8-byte by-value args preserve the 0x28/s0-s3 hold set.
   Scalarized copy bursts color through v0,v1,a0,a1 while the allocation result is held in a2.
   A derived sp base with ASM_KEEP prevents packed tail loads folding from lwl/lwr pairs into lw;
   the paired tail source reads then also eliminate both downstream branch-displacement drifts. */
