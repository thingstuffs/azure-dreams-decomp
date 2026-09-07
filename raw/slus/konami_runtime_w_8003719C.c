#include "common.h"

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

M2C_UNK func_80033C1C();                 /* extern */
M2C_UNK func_800350B0();                 /* extern */
M2C_UNK func_80036C7C(); /* extern */
M2C_UNK func_80037394();         /* extern */
void *func_8003FF2C(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8006A988;
extern M2C_UNK D_8006A994;
extern M2C_UNK D_8006A9A0;
extern M2C_UNK D_8006A9AC;
extern M2C_UNK D_8006A9B8;
extern M2C_UNK D_8006A9C4;
extern M2C_UNK D_80081E90;
extern M2C_UNK D_80081EA0;
extern M2C_UNK D_80082B80;
extern M2C_UNK D_80082B90;
extern M2C_UNK D_80082BA0;
extern M2C_UNK D_80082BB0;
extern M2C_UNK D_80082BC0;
extern M2C_UNK func_80033D54;

void func_8003719C(s32 arg0, void *arg1, s32 *arg2, s16 arg3, s32 arg4, s32 arg5) {
    s32 temp_s7;
    void *temp_s1;
    void *temp_s4;
    void *temp_v0;

    temp_v0 = func_8003FF2C(0x11, arg0, 0x49, &D_80082BC0);
    M2C_FIELD(temp_v0, M2C_UNK (**)(void *, s32, void *), 0x10) = func_80037394;
    func_8004491C(temp_v0, &func_80033D54);
    temp_s1 = temp_v0 + 0x20;
    temp_s7 = M2C_FIELD(temp_v0, s32 *, 8);
    temp_s4 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_s1, s32 **, 0x44) = arg2;
    M2C_FIELD(temp_s1, s8 *, 0x48) = 1;
    M2C_FIELD(temp_s1, s16 *, 0x4A) = arg3;
    func_80033C1C(arg1, *arg2);
    M2C_FIELD(temp_v0, void **, 0x20) = arg1;
    M2C_FIELD(arg1, s32 *, 0x60) = 6;
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x20), s32 *, 0x10) = 0x47;
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x20), s32 *, 0x14) = 2;
    M2C_FIELD(temp_s1, s32 *, 4) = 0;
    M2C_FIELD(temp_s1, s32 *, 8) = 0;
    func_800350B0(arg5, temp_s1);
    M2C_FIELD(temp_s4, s32 *, 0xC) = 0xC0C0C0;
    func_80036C7C(M2C_FIELD(temp_s1, s32 **, 0x44) + 3, &D_8006A988, &D_80082B80);
    func_80036C7C(M2C_FIELD(temp_s1, s32 **, 0x44) + 3, &D_8006A994, &D_80082B90);
    func_80036C7C(M2C_FIELD(temp_s1, s32 **, 0x44) + 3, &D_8006A9A0, &D_80082BA0);
    func_80036C7C(M2C_FIELD(temp_s1, s32 **, 0x44) + 3, &D_8006A9AC, &D_80082BB0);
    func_80036C7C(M2C_FIELD(temp_s1, s32 **, 0x44) + 3, &D_8006A9B8, &D_80081E90);
    func_80036C7C(M2C_FIELD(temp_s1, s32 **, 0x44) + 3, &D_8006A9C4, &D_80081EA0);
    M2C_FIELD(temp_s4, M2C_UNK **, 8) = &D_80082B90;
    M2C_FIELD(temp_s4, s32 *, 0) = 0;
    M2C_FIELD(temp_s4, s8 *, 4) = 0;
    M2C_FIELD(temp_s4, s8 *, 5) = 0;
    M2C_FIELD(temp_s4, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s4, u16 *, 0x14) | 0x1C);
    M2C_FIELD(temp_s1, s16 *, 0x66) = (s16) arg4;
    func_80037394(temp_s1, temp_s7, temp_s4);
}
