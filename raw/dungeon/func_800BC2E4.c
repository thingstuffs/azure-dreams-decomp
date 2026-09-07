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

void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C();           /* extern */
extern s32 D_80045C34[4];
extern s32 D_80083498[4];
extern s32 D_800C1718[4];
extern s32 D_800DF3C0[4];

void *func_800C1A44(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_v0 = func_8003FD64(0x12, &D_80083498[0]);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800C1718[0];
        func_8004491C(temp_v0, &D_80045C34[0]);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, s16 *, 2) = (s16) (((s32) (arg0 << 0x10) >> 0xA) + 0x20);
        M2C_FIELD(temp_v1, s16 *, 6) = (s16) (((s32) (arg1 << 0x10) >> 0xA) + 0x20);
        M2C_FIELD(temp_v1, s16 *, 0xA) = arg2;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, M2C_UNK **, 8) = &D_800DF3C0[0];
        M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_v1_2, s16 *, 6) = 8;
        temp_v1_3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1_3, s16 *, 0x4C) = 8;
        M2C_FIELD(temp_v1_3, s16 *, 0x48) = 7;
    }
    return temp_v0;
}
