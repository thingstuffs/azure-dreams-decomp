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

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                       /* extern */
extern M2C_UNK D_800244E4;
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083780;
extern M2C_UNK D_800DE870;

void func_8196B2F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_rand;
    register s32 temp_v0_coords ASM_REG("$2");
    s32 temp_v1;
    register s32 temp_v1_coords ASM_REG("$3");
    s16 temp_v0_2;
    register u16 temp_flags ASM_REG("$3");
    register u16 temp_v0_3 ASM_REG("$2");
    void *temp_a0;
    void *temp_a0_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        temp_v0_2 = (rand() & 7) + 0x20;
        M2C_FIELD(temp_s1, s16 *, 0x2C) = temp_v0_2;
        M2C_FIELD(temp_s1, s16 *, 0x2E) = temp_v0_2;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800244E4;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v0_3 = M2C_FIELD(temp_a0, u16 *, 0x14);
        M2C_FIELD(temp_a0, s16 *, 6) = 0;
        temp_v0_3 |= 0xC;
        ASM_KEEP(temp_v0_3);
        M2C_FIELD(temp_a0, u16 *, 0x14) = temp_v0_3;
        ASM_KEEP(temp_v0_3);
        ASM_CLOBBER("$3");
        temp_flags = temp_v0_3;
        ASM_KEEP(temp_flags);
        temp_v0_3 = 0x60;
        temp_flags |= 2;
        ASM_KEEP(temp_flags);
        ASM_KEEP(temp_v0_3);
        M2C_FIELD(temp_a0, s16 *, 0x10) = temp_v0_3;
        M2C_FIELD(temp_a0, u16 *, 0x14) = temp_flags;
        temp_a0 = (void *) 0x80080000;
        ASM_KEEP(temp_a0);
        temp_s0 = M2C_FIELD(temp_v0, void **, 8);
        temp_a0 = (void *) ((u8 *) temp_a0 + 0x3780);
        M2C_FIELD(temp_s0, u16 *, 2) = arg3;
        M2C_FIELD(temp_s0, u16 *, 6) = (u16) arg4;
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) arg5;
        temp_v1_coords = M2C_FIELD(temp_a0, u16 *, 2);
        ASM_KEEP(temp_v1_coords);
        temp_v0_coords = arg3;
        ASM_KEEP(temp_v0_coords);
        temp_v0_coords += temp_v1_coords;
        ASM_KEEP(temp_v0_coords);
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) temp_v0_coords;
        temp_v1_coords = M2C_FIELD(temp_a0, u16 *, 6);
        ASM_KEEP(temp_v1_coords);
        temp_v0_coords = arg4;
        ASM_KEEP(temp_v0_coords);
        temp_v0_coords += temp_v1_coords;
        ASM_KEEP(temp_v0_coords);
        M2C_FIELD(temp_s0, u16 *, 6) = (u16) temp_v0_coords;
        temp_v1_coords = M2C_FIELD(temp_a0, u16 *, 0xA);
        ASM_KEEP(temp_v1_coords);
        temp_v0_coords = arg5;
        ASM_KEEP(temp_v0_coords);
        temp_v0_coords += temp_v1_coords;
        ASM_KEEP(temp_v0_coords);
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) temp_v0_coords;
        temp_rand = rand() & 0x1F;
        temp_v1 = M2C_FIELD(temp_s0, u16 *, 2);
        temp_v1 -= 0x10;
        temp_v1 += temp_rand;
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) temp_v1;
        temp_rand = rand() & 0x1F;
        temp_v1 = M2C_FIELD(temp_s0, u16 *, 6);
        temp_v1 -= 0x10;
        temp_v1 += temp_rand;
        M2C_FIELD(temp_s0, u16 *, 6) = (u16) temp_v1;
        temp_rand = rand() & 0x1F;
        temp_v1 = M2C_FIELD(temp_s0, u16 *, 0xA);
        temp_v1 -= 0x10;
        temp_v1 += temp_rand;
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) temp_v1;
        M2C_FIELD(temp_s1, s32 *, 0x94) = rand();
        M2C_FIELD(temp_s1, s32 *, 0xA0) = 0x1000;
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0xC00;
        M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0xC00;
        M2C_FIELD(temp_a0_2, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_a0_2, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_a0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0_2, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_a0_2, &D_800DE870, 0);
    }
}

/* MECHANISM: The s32 fourth-argument ABI and split RMW live ranges recover the seven-register 0x30 frame.
   Guarded v0/v1 seams preserve the two flag updates and coordinate accumulation order.
   A fenced 0x80080000 page base around the independent s0 load emits retail's lui/lw/addiu sequence. */
