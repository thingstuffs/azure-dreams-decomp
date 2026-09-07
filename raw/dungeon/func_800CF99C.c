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

s32 rand();                                /* extern */
void func_800D5188(void) __attribute__((noreturn)); /* extern */
extern M2C_UNK D_800814A0;

void func_800D50FC(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    u16 temp_v0;
    u32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x1E) & 7;
    switch (temp_v1) {
    case 1:
    case 2:
    case 5:
    case 6:
        break;
    case 0:
    case 4:
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        temp_s0 = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        ASM_KEEP(arg0);
        ASM_KEEP(arg1);
        ASM_KEEP(arg2);
        M2C_FIELD(arg1, s32 *, 0x10) = temp_s0;
        func_800D5188();
    case 3:
    case 7:
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        break;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0xC) * (s16) M2C_FIELD(arg0, u16 *, 0x1E)) / (s16) M2C_FIELD(arg0, s16 *, 0x20));
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0xD) * (s16) M2C_FIELD(arg0, u16 *, 0x1E)) / (s16) M2C_FIELD(arg0, s16 *, 0x20));
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0xE) * (s16) M2C_FIELD(arg0, u16 *, 0x1E)) / (s16) M2C_FIELD(arg0, s16 *, 0x20));
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x1E) - 1;
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        register u32 page ASM_REG("$3");

        page = 0x80080000;
        ASM_KEEP(page);
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        M2C_FIELD(page, s32 *, 0x14A0) = M2C_FIELD(page, s32 *, 0x14A0) | 0x8000;
    }
}

/* MECHANISM: Split the second RNG result, then keep all three arguments live across both calls
   to preserve the 0x20 frame and s1/s0/ra/s2 save order while LEAD 18 forms the continuation j.
   A guarded $v1 page base emits the branch-slot lui and both 0x14A0($v1) accesses exactly. */
