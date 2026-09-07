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

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                        /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8016E4E8;
extern void *D_80175D78;

void func_8016E998(void *arg0) {
    s32 temp_a1_2;
    s32 temp_s1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    register s32 temp_v0_7 ASM_REG("$2");
    register s32 temp_v0_8 ASM_REG("$2");
    register s32 temp_a0_4 ASM_REG("$4");
    register void *temp_a0_5 ASM_REG("$4");
    register s32 temp_v1_2 ASM_REG("$3");
    register u16 temp_v1_3 ASM_REG("$3");
    s32 var_s3;
    s32 var_s4;
    u16 temp_v0_2;
    M2C_UNK *temp_s7;
    void **var_s5;
    register void *temp_a1 ASM_REG("$5");
    void *temp_a1_3;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;

    var_s4 = 0;
    temp_s7 = &D_8016E4E8;
    var_s5 = &D_80175D78;
    var_s3 = 0x100;
    do {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            temp_a0_5 = temp_v0;
            ASM_KEEP(temp_a0_5);
            ASM_SCHED_BARRIER();
            temp_s0 = temp_v0 + 0x20;
            ASM_KEEP(temp_s0);
            temp_v0_8 = 0x32;
            ASM_KEEP(temp_v0_8);
            ASM_SCHED_BARRIER();
            M2C_FIELD(temp_s0, s16 *, 0x18) = (s16) temp_v0_8;
            M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) temp_v0_8;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = temp_s7;
            func_8004491C(temp_a0_5, &D_80045340);
            temp_a1 = M2C_FIELD(temp_v0, void **, 0xC);
            temp_v0_2 = M2C_FIELD(temp_a1, u16 *, 0x14) | 0xC;
            M2C_FIELD(temp_a1, u16 *, 0x14) = temp_v0_2;
            ASM_SCHED_BARRIER();
            ASM_KEEP(temp_v0_2);
            temp_v1_3 = temp_v0_2;
            ASM_KEEP(temp_v1_3);
            M2C_FIELD(temp_a1, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a1, u16 *, 0x14) = (u16) (temp_v1_3 | 0x80);
            temp_v1 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_v1, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
            M2C_FIELD(temp_v1, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
            temp_a1_2 = M2C_FIELD(arg0, s32 *, 8);
            M2C_FIELD(temp_v1, u16 *, 6) = (u16) (M2C_FIELD(temp_v1, u16 *, 6) - 0x440);
            M2C_FIELD(temp_v1, s32 *, 8) = temp_a1_2;
            M2C_FIELD(temp_s0, s16 *, 0x7E) = -0x40;
            M2C_FIELD(temp_s0, s16 *, 0x78) = -0x40;
            M2C_FIELD(temp_s0, s16 *, 0x8A) = 0;
            M2C_FIELD(temp_s0, s16 *, 0x84) = 0;
            temp_s1 = var_s4 << 8;
            temp_v0_3 = (s32) (func_80064584(var_s3, temp_a1_2) << 5) >> 0xC;
            M2C_FIELD(temp_s0, s16 *, 0x80) = (s16) temp_v0_3;
            M2C_FIELD(temp_s0, s16 *, 0x74) = (s16) temp_v0_3;
            temp_v0_4 = (s32) (func_80064584(temp_s1) << 5) >> 0xC;
            M2C_FIELD(temp_s0, s16 *, 0x86) = (s16) temp_v0_4;
            M2C_FIELD(temp_s0, s16 *, 0x7A) = (s16) temp_v0_4;
            temp_v0_5 = (s32) (func_800644B8(var_s3) << 5) >> 0xC;
            M2C_FIELD(temp_s0, s16 *, 0x82) = (s16) temp_v0_5;
            M2C_FIELD(temp_s0, s16 *, 0x76) = (s16) temp_v0_5;
            temp_v0_6 = (s32) (func_800644B8(temp_s1) << 5) >> 0xC;
            ASM_SCHED_BARRIER();
            temp_v1_2 = 0x40;
            ASM_KEEP(temp_v1_2);
            M2C_FIELD(temp_s0, s16 *, 0x88) = (s16) temp_v0_6;
            M2C_FIELD(temp_s0, s16 *, 0x7C) = (s16) temp_v0_6;
            ASM_SCHED_BARRIER();
            temp_a1_3 = M2C_FIELD(temp_v0, void **, 0xC);
            ASM_SCHED_BARRIER();
            temp_v0_7 = 0x1000;
            ASM_KEEP(temp_v0_7);
            M2C_FIELD(temp_a1_3, s8 *, 0xC) = (s8) temp_v1_2;
            ASM_SCHED_BARRIER();
            temp_a0_4 = temp_v1_2;
            ASM_KEEP(temp_a0_4);
            M2C_FIELD(temp_a1_3, s16 *, 0x1E) = (s16) temp_v0_7;
            M2C_FIELD(temp_a1_3, s16 *, 0x1C) = (s16) temp_v0_7;
            M2C_FIELD(temp_a1_3, u8 *, 0xD) = (u8) temp_v1_2;
            M2C_FIELD(temp_a1_3, u8 *, 0xE) = (u8) temp_v1_2;
            M2C_FIELD(temp_v0, s8 *, 0x20) = (s8) temp_a0_4;
            M2C_FIELD(temp_s0, u8 *, 1) = (u8) M2C_FIELD(temp_a1_3, u8 *, 0xD);
            M2C_FIELD(temp_s0, u8 *, 2) = (u8) M2C_FIELD(temp_a1_3, u8 *, 0xE);
            *var_s5 = temp_v0;
        }
        var_s5 = (void **)((s8 *)((void **)((s8 *)var_s5 + 4)));
        var_s4 += 1;
        var_s3 += 0x100;
    } while (var_s4 < 0x10);
}

/* MECHANISM: Held global bases and caller-saved constant pins restore the 0x38
   s0-s7 prologue; split RMW names and schedule seams preserve retail copies,
   delay-slot fills, and tail store order. */
