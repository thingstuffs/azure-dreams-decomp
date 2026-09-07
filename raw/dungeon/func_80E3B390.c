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

void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047784();    /* extern */
extern M2C_UNK D_8017474C;
extern M2C_UNK D_80175540;

void func_80174B90(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x100, arg0);
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8017474C;
        M2C_FIELD(temp_s0, void **, 0x14) = (void *) M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_s0, void **, 0x18) = (void *) M2C_FIELD(arg0, void **, 8);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
        M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x14), s32 *, 0x28);
        M2C_FIELD(temp_a0, u16 *, 0x12) = (u16) M2C_FIELD(M2C_FIELD(temp_s0, void **, 0x14), u16 *, 0x12);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 2) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 6) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        func_80047784(temp_a0, 0x46, 0);
        func_8004491C(temp_v0, &D_80175540);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg1;
        M2C_FIELD(temp_s0, s32 *, 4) = arg2;
        M2C_FIELD(temp_s0, s32 *, 8) = arg3;
        M2C_FIELD(temp_s0, void **, 0xC) = arg0;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    }
}
