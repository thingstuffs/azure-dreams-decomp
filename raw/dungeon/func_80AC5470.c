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

extern M2C_UNK D_800814A0;

void func_80AC5470(void *arg0, void *arg1) {
    s16 temp_v0;
    register s32 reg_v0 ASM_REG("$2");
    register s32 reg_v1 ASM_REG("$3");
    register s32 reg_a0 ASM_REG("$4");
    register s32 reg_a1 ASM_REG("$5");
    register s32 reg_a2 ASM_REG("$6");
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
    reg_v0 = M2C_FIELD(arg0, s32 *, 0x40);
    reg_v1 = M2C_FIELD(arg0, s32 *, 0x4C);
    reg_a0 = M2C_FIELD(arg0, s32 *, 0x50);
    reg_a2 = M2C_FIELD(arg0, s32 *, 0x54);
    reg_v0 += reg_v1;
    M2C_FIELD(arg0, s32 *, 0x40) = reg_v0;
    reg_v0 = M2C_FIELD(arg0, s32 *, 0x44);
    reg_v1 = M2C_FIELD(arg0, s32 *, 0x48);
    reg_v0 += reg_a0;
    M2C_FIELD(arg0, s32 *, 0x44) = reg_v0;
    reg_v0 = M2C_FIELD(arg0, s16 *, 0x36);
    reg_v1 += reg_a2;
    M2C_FIELD(arg0, s32 *, 0x48) = reg_v1;
    reg_v1 = M2C_FIELD(arg1, s16 *, 2);
    var_v0 = reg_v0 - reg_v1;
    if (var_v0 < 0) {
        var_v0 = 0 - var_v0;
    }
    if (var_v0 < 0x10) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
    reg_v1 = M2C_FIELD(arg0, u8 *, 0);
    ASM_MEM_BARRIER();
    reg_v0 = M2C_FIELD(arg0, s16 *, 0x32);
    reg_a0 = reg_v1 * reg_v0;
    if (reg_a0 < 0) {
        reg_a0 += 0xFF;
    }
    reg_v1 = M2C_FIELD(arg0, u8 *, 1);
    ASM_MEM_BARRIER();
    reg_v0 = M2C_FIELD(arg0, s16 *, 0x32);
    reg_a1 = reg_v1 * reg_v0;
    reg_v0 = reg_a0 >> 8;
    M2C_FIELD(arg0, s8 *, 4) = (s8) reg_v0;
    if (reg_a1 < 0) {
        reg_a1 += 0xFF;
    }
    reg_v1 = M2C_FIELD(arg0, u8 *, 2);
    ASM_MEM_BARRIER();
    reg_v0 = M2C_FIELD(arg0, s16 *, 0x32);
    reg_v1 *= reg_v0;
    reg_v0 = reg_a1 >> 8;
    M2C_FIELD(arg0, s8 *, 5) = (s8) reg_v0;
    if (reg_v1 < 0) {
        reg_v1 += 0xFF;
    }
    reg_v0 = reg_v1 >> 8;
    M2C_FIELD(arg0, s8 *, 6) = (s8) reg_v0;
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 8;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    M2C_FIELD(arg0, s32 *, 8) = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
/* MECHANISM: Frameless leaf holds arg0 in $a3; guarded short-lived $v0/$v1/$a0/$a1/$a2
   roles reproduce the interleaved accumulator and multiply schedules. Direct scalar
   global RMW removes the +1 cascade; memory barriers force signed-scale reloads, and
   $v0 shift temporaries plus the full-word +4 to +8 copy close the tail. */
