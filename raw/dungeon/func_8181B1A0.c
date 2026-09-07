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
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80024878;
extern M2C_UNK D_80025908[];
extern M2C_UNK D_80045340;

void func_8181B1A0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register s32 saved_arg4 ASM_REG("$18") = arg4;
    register void *temp_a3 ASM_REG("$7");
    register void *temp_s0 ASM_REG("$16");
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    temp_s0 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        ASM_KEEP(temp_s0);
        M2C_FIELD(temp_s0, s16 *, 2) = (s16) saved_arg4;
        M2C_FIELD(temp_s0, s32 *, 0x60) = (s32) ((rand() & 0x1FFFF) + 0x10000);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024878;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a3, u16 *, 0x14) | 0xC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + arg1);
        M2C_FIELD(temp_v1, s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + arg2);
        M2C_FIELD(temp_v1, s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + arg3);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a3, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a3, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a3, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a3, u8 *, 0xC) = 0x80;
        memcpy((u8 *) temp_v0 + 0x40, &D_80025908, 12);
        M2C_FIELD(temp_a3, void **, 8) = (void *) (temp_v0 + 0x40);
    }
}

/* MECHANISM: The 48-byte frame holds arg0-arg3 in s3-s6, stack arg4 in pinned s2,
   the allocation result in s1, and a pinned +0x20 base in s0 with an entry-block fence.
   One pinned a3 name spans the two record-pointer live ranges; u8 fields preserve li 0x80.
   Fixed-size memcpy plus 2.7.2-cdk-G0 selects retail's 12-byte unaligned-copy temp colors. */
