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

M2C_UNK func_8009A21C();                 /* extern */
M2C_UNK func_8009A3D0();                 /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern struct {
    s8 pad0[10];
    u16 field_0x0A;
    s8 pad1[10];
} D_80083460;

void func_800AA258(void *arg0, void *arg1, void *arg2, void *arg3) {
    register s32 temp_v0 ASM_REG("$2");
    s32 temp_a0;
    s32 temp_s0;
    s32 var_s0;

    M2C_FIELD(arg0, s8 *, 0x9A) = 0xA;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    var_s0 = 0x3000;
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
        var_s0 = 0x300;
    }
    temp_s0 = var_s0 & 0xFFFF;
    func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), temp_s0);
    temp_a0 = ((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 8) & 0xE;
    temp_v0 = M2C_FIELD(arg2, u8 *, 0x24);
    temp_v0 = temp_v0 + (u8) *(temp_a0 + &D_8006CCD8);
    ASM_KEEP(temp_v0);
    M2C_FIELD(arg2, u8 *, 0x24) = (u8) temp_v0;
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + *(temp_a0 + &D_8006CCE8));
    func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, volatile u8 *, 0x25), temp_s0);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & ~0x100);
    M2C_FIELD(arg0, s16 *, 0x96) = 0x21;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    D_80083460.field_0x0A = (u16)(D_80083460.field_0x0A + 1);
}

/* MECHANISM: Natural argument liveness yields the retail 0x28 frame and s2/s1/s3/s0 save order.
   Byte-scaled s8 tables plus an unsigned load preserve srl 8 / mask 0xE and select lbu.
   A guarded v0 sum accumulator and post-store schedule barrier reproduce the table roles and store order. */
