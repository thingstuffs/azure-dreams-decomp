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

M2C_UNK func_80047784();         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_80170854[];
extern u8 D_80173FD0[];

void func_80173AD4(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 temp_v0;
    s32 temp_ret;
    register void *temp_a0 ASM_REG("$4");
    register s32 temp_a1 ASM_REG("$5");
    u8 temp_byte;
    u8 call_a0;
    u8 call_a1;
    s32 call_flags;
    register void *var_s1 ASM_REG("$17") = arg3;
    register void *var_s0 ASM_REG("$16");
    register void *var_s2 ASM_REG("$18");
    u8 *var_s3;

    temp_byte = M2C_FIELD(var_s1, u8 *, 0x71);
    var_s0 = arg0;
    M2C_FIELD(var_s1, u8 *, 0x71) = temp_byte & 0x7F;
    ASM_SCHED_BARRIER();
    var_s3 = (u8 *)&D_80083460;
    var_s2 = arg2;
    if (!(M2C_FIELD(var_s3, u16 *, 2) & 0x2000) && ((func_800A2BDC(var_s1) << 0x10) == 0)) {
        M2C_FIELD(var_s0, s32 *, 0x8C) = 0;
        M2C_FIELD(var_s0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(var_s0, s8 *, 0x9B) = 0;
        M2C_FIELD(var_s0, s16 *, 0x96) = 0;
        if (!(M2C_FIELD(var_s0, u16 *, 0x98) & 0x8000)) {
            M2C_FIELD(var_s0, u16 *, 0xA6) = (u16) M2C_FIELD(var_s2, u16 *, 0x12);
            M2C_FIELD(var_s0, s16 *, 0xAA) = (s16) (M2C_FIELD(var_s1, u16 *, 0x14) & 7);
        }
        ASM_KEEP(var_s0);
        M2C_FIELD(var_s3, u16 *, 0xA) = (u16) (M2C_FIELD(var_s3, u16 *, 0xA) + 1);
        ASM_KEEP(var_s3);
        M2C_FIELD(var_s1, u8 *, 0x6D) = (u8) (M2C_FIELD(var_s1, u8 *, 0x6D) - 1);
        call_flags = M2C_FIELD(var_s1, s32 *, 0x1C) & 0x2000;
        call_a0 = M2C_FIELD(var_s2, u8 *, 0x24);
        call_a1 = M2C_FIELD(var_s2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (call_flags) {
            var_a2 = 0x300;
        }
        func_8009A3D0(call_a0, call_a1, var_a2);
        M2C_FIELD(var_s1, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s1, s32 *, 0x1C) & ~0x2000);
        func_8009A21C(M2C_FIELD(var_s2, u8 *, 0x24), M2C_FIELD(var_s2, u8 *, 0x25), 0x3000);
        M2C_FIELD(var_s2, u8 **, 0x2C) = D_80173FD0;
        func_80047784(var_s2, D_80173FD0[((D_80083228 + M2C_FIELD(var_s1, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        ASM_KEEP(var_s2);
        temp_ret = func_800990FC();
        temp_a0 = var_s1;
        ASM_KEEP(temp_a0);
        temp_a1 = temp_ret;
        ASM_KEEP(temp_a1);
        temp_v0 = temp_a1;
        func_80099290(func_80099194(&D_80170854, func_80099734(temp_a0, temp_a1)));
        ASM_KEEP(var_s1);
        func_800A5720(temp_v0);
    }
}

/* MECHANISM: The true-space four-argument ABI pins a3/s1, a0/s0, and a2/s2;
   a named scheduling seam holds D_80083460 in s3 and orders the flag/call loads.
   Splitting the final return into v0, then fenced a0/a1 live ranges, yields
   move a0,s1; move a1,v0; jal; move s0,a1 exactly. */
