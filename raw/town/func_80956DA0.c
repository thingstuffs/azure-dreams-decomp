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
extern M2C_UNK D_80023E64;
extern M2C_UNK D_80044BB0;
extern M2C_UNK D_80079438;

void func_80956DA0(s32 arg0) {
    void *temp_v0;
    void *temp_v1;
    void *temp_v2;
    s32 temp_v3;

    temp_v0 = func_8003FC64(0x15);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80023E64;
        func_8004491C(temp_v0, &D_80044BB0);
        temp_v3 = 0x800000;
        ASM_KEEP(temp_v3);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        ASM_KEEP(temp_v1);
        temp_v2 = (u8 *)temp_v0 + 0x20;
        ASM_KEEP(temp_v2);
        M2C_FIELD(temp_v2, s32 *, 4) = arg0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = 0xF0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = 0xAC;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = 0;
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 6) = 0x10;
        M2C_FIELD(temp_v1, M2C_UNK **, 8) = &D_80079438;
        M2C_FIELD(temp_v1, s8 *, 4) = 0;
        M2C_FIELD(temp_v1, s8 *, 5) = 0;
        temp_v3 |= 0x8080;
        M2C_FIELD(temp_v1, s32 *, 0xC) = temp_v3;
        M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) | 0xC);
    }
}
