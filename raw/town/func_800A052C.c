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

M2C_UNK func_8003DB94();        /* extern */
M2C_UNK func_80047784();        /* extern */
void func_8009DD28();                                /* extern */
extern s32 D_80081458[];
extern M2C_UNK D_800D07A4[];
extern s16 D_800D07AC;

void func_8009DC8C(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    if (arg2 == 2) {
        M2C_FIELD(arg0, s8 *, 0x93) = 1;
        M2C_FIELD(arg1, s32 *, 0x28) = D_80081458[0];
        func_80047784(arg1, D_800D07AC, 0);
        func_8009DD28();
        return;
    }
    func_8003DB94(arg1, D_800D07A4[arg2], 0);
    if (arg3 & 2) {
        M2C_FIELD(arg1, s16 *, 0x12) = 0x100;
        func_8009DD28();
        ASM_MEM_BARRIER();
        return;
    }
    if (arg3 & 4) {
        M2C_FIELD(arg1, s16 *, 0x12) = 0x200;
        func_8009DD28();
        return;
    }
    M2C_FIELD(arg1, s16 *, 0x12) = 0;
}

/* MECHANISM: Void tail-call ABI preserves the three retail jumps and their delay slots.
   A one-sided ASM_MEM_BARRIER prevents merging the twin flag-store tails.
   Word-array indexing emits sll(a2,2); natural liveness yields the 0x20 s0/s1 frame. */
