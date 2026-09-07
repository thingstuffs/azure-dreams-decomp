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

void func_800256B8(void) __attribute__((noreturn)); /* extern */
void func_800256F0(void) __attribute__((noreturn)); /* extern */
void *func_8003FC64(s32);                         /* extern */
void func_8004491C(void *, void *);                /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
extern M2C_UNK D_80025528;
extern u8 D_800C95C0[12];

void *func_81959E04(s16 arg0, s16 arg1, s16 arg2) {
    register s32 var_s0 ASM_REG("$16");
    register void *temp_s1 ASM_REG("$17");
    register void *temp_v0 ASM_REG("$18");
    register s32 var_s3 ASM_REG("$19");
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s5 ASM_REG("$21");
    register s16 var_s6 ASM_REG("$22");
    register s16 var_s7 ASM_REG("$23");
    s16 var_fp;
    register void *temp_v1 ASM_REG("$3");
    register void *call_arg1 ASM_REG("$5");

    var_s6 = arg0;
    var_s7 = arg1;
    var_fp = arg2;
    var_s3 = 0;
    ASM_KEEP_NV(var_s3);
    var_s5 = -0x800;
    var_s4 = 0x20;
    var_s0 = var_s3;
loop_1:
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        register void *call_arg0 ASM_REG("$4");
        register void *field_ptr ASM_REG("$7");
#ifdef NON_MATCHING
        call_arg1 = D_800C95C0;
#else
        call_arg1 = (void *)0x800D0000;
        ASM_KEEP_NV(call_arg1);
#endif
        call_arg0 = temp_v0;
        field_ptr = &D_80025528;
#ifndef NON_MATCHING
        call_arg1 = (u8 *)call_arg1 - 0x6A40;
#endif
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = field_ptr;
        func_8004491C(call_arg0, call_arg1);
        temp_s1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s1, s16 *, 2) = var_s6;
        M2C_FIELD(temp_s1, s16 *, 6) = var_s7;
        M2C_FIELD(temp_s1, s16 *, 0xA) = var_fp;
        if (func_80064584(var_s0) & 0x800) {
            register s32 tail_value ASM_REG("$2");
            tail_value = func_80064584(var_s0) | var_s5;
            ASM_TAILSLOT_PIN_TIED(tail_value);
            func_800256B8();
        }
        M2C_FIELD(temp_s1, s32 *, 0xC) = (s32) ((func_80064584(var_s0) & 0x7FF) << 0xB);
        if (func_800644B8(var_s0) & 0x800) {
            register s32 tail_value ASM_REG("$2");
            tail_value = func_800644B8(var_s0) | var_s5;
            ASM_TAILSLOT_PIN_TIED(tail_value);
            func_800256F0();
        }
        M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) ((func_800644B8(var_s0) & 0x7FF) << 0xB);
        M2C_FIELD(temp_s1, s32 *, 0x14) = 0xFFFE0000;
        temp_v1 = temp_v0 + 0x20;
        ASM_KEEP_NV(temp_v1);
        M2C_FIELD(temp_v0, s16 *, 0x20) = var_s4;
        M2C_FIELD(temp_v1, s16 *, 2) = var_s4;
        M2C_FIELD(temp_v1, s16 *, 4) = 1;
        M2C_FIELD(temp_v1, s16 *, 6) = 0;
        M2C_FIELD(temp_v1, s16 *, 0x30) = var_s4;
        goto block_9;
    }
block_9:
    var_s3 += 1;
    var_s0 += 0x80;
    if (var_s3 >= 0x20) {
        return temp_v0;
    }
    goto loop_1;
}
/* MECHANISM: The 0x38 frame comes from ten held roles: s6/s7/fp args, s3/s0 loop state,
   s5/s4 constants, and s2/s1 object bases; a kept s3 preserves move s0,s3.
   Tied tail-slot pins sink both dead v0|s5 values into noreturn j delays.
   A kept a1 page/low split plus fixed a0/a3 emits the call setup in retail order. */
