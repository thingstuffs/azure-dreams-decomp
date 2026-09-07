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

M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();            /* extern */
s32 func_800C8B3C();                                /* extern */
M2C_UNK func_800C8B5C();      /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800C8B8C;
extern M2C_UNK D_800EE344;

s32 func_800C8A68(void *arg0) {
    void *temp_a1;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    s32 temp_v1;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        return 0;
    }
    temp_a1 = M2C_FIELD(temp_v0, void **, 8);
    temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
    temp_s0 = temp_v0 + 0x20;
    M2C_FIELD(temp_a1, volatile s32 *, 0) = M2C_FIELD(arg0, volatile s32 *, 0);
    M2C_FIELD(temp_a1, volatile s32 *, 4) = M2C_FIELD(arg0, volatile s32 *, 4);
    temp_v1 = M2C_FIELD(arg0, volatile s32 *, 8) + 0xFFDC0000;
    M2C_FIELD(temp_a1, s32 *, 0xC) = 0x100000;
    M2C_FIELD(temp_a1, s32 *, 0x10) = 0;
    M2C_FIELD(temp_a1, s32 *, 8) = temp_v1;
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800C8B8C;
    M2C_FIELD(temp_s0, s16 *, 0x90) = 2;
    func_800C8B5C(temp_s0, temp_a1, temp_s1);
    M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
    func_8003DB94(temp_s1, &D_800EE344, 0);
    func_80033CD8(temp_s0, &D_80045340);
    func_800C8B3C();
    return (s32) temp_v0;
}

/* MECHANISM: A guard-clause tail keeps the allocation in s2 for the live return,
   while defining base+0x20 after the child loads yields s3/s2/s1/s0 retail roles.
   Volatile scalar copies plus a named third word reproduce the exact record-store schedule. */
