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

s16 func_8002458C();                         /* extern */
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_8002615C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;

void func_8002626C(
    s32 unused0, s32 unused1, s32 unused2, s32 unused3,
    s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 temp_v1;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    register s32 held_arg4 ASM_REG("$22") = arg4;
    register s32 held_arg5 ASM_REG("$23") = arg5;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x28) = 0x14;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8002615C;
        func_8004491C(temp_v0, &D_80045340);
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s16 *, 0x10) = 0x40;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x14) | 0xC);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) =
            (s16) (s32) &((s8 *) arg7)[held_arg4];
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) =
            (s16) (s32) &((s8 *) arg8)[held_arg5];
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (arg9 + arg6);
        M2C_FIELD(temp_s0, s32 *, 0x88) = (s32) (0 - ((s32) (held_arg4 << 0x10) >> 7));
        M2C_FIELD(temp_s0, s32 *, 0x8C) = (s32) (0 - ((s32) (held_arg5 << 0x10) >> 7));
        M2C_FIELD(temp_s0, s16 *, 0x2C) = (s16) arg7;
        M2C_FIELD(temp_s0, s16 *, 0x2E) = (s16) arg8;
        M2C_FIELD(temp_s0, s16 *, 0x30) = (s16) arg9;
        M2C_FIELD(temp_s0, s32 *, 0x90) = (s32) (0 - ((s32) (arg6 << 0x10) >> 7));
        temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x3000;
        M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x3000;
        temp_v1 = func_8002458C(3);
        M2C_FIELD(temp_s1, s8 *, 0xE) = 0;
        M2C_FIELD(temp_s1, s8 *, 0xD) = 0;
        M2C_FIELD(temp_s1, s8 *, 0xC) = 0;
        if (temp_v1 == 0) {
            M2C_FIELD(temp_s1, s8 *, 0xC) = 0x10;
        }
        if (temp_v1 == 1) {
            M2C_FIELD(temp_s1, s8 *, 0xD) = 0x10;
        }
        if (temp_v1 == 2) {
            M2C_FIELD(temp_s1, s8 *, 0xE) = 0x10;
        }
        M2C_FIELD(temp_s1, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_s1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_s1, &D_800DE870, 0);
        ASM_KEEP(held_arg4);
        ASM_KEEP(held_arg5);
    }
}
/* MECHANISM: The ten-argument ABI and reused pointer local produce the retail
   0x38 frame, full hold set, and reload seam. Tail-kept s6/s7 pins preserve
   scheduling; byte-pointer BASE[index] sums select retail addu operand order. */
