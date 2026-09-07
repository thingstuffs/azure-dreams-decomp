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

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
void func_800A56E0(s32, void *);
extern M2C_UNK D_80046398;
extern void *D_800814A8;
extern s8 D_80083160[];
extern s8 D_800B1F34[];

void func_800B2074(s32 arg0, s32 arg1) {
    register s32 temp_s0 ASM_REG("$16");
    register void *temp_v0 ASM_REG("$17");
    register s32 temp_s2 ASM_REG("$18");
    register s32 temp_s3 ASM_REG("$19");
    register void *temp_call0 ASM_REG("$4");
    register void *temp_call1 ASM_REG("$5");
    register void *temp_callback ASM_REG("$2");
    register void *temp_dest ASM_REG("$2");
    register u16 temp_tail ASM_REG("$3");
    s8 *temp_s4;
    void *temp_a1;
    void *temp_v1;

    temp_s2 = arg0;
    temp_s3 = arg1;
    temp_s4 = D_80083160;
    temp_s0 = M2C_FIELD(temp_s4, s32 *, 0x1DC);
    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        temp_call0 = temp_v0;
        ASM_KEEP(temp_call0);
        temp_callback = D_800B1F34;
        ASM_KEEP(temp_callback);
        temp_call1 = &D_80046398;
        ASM_KEEP(temp_call1);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = temp_callback;
        func_8004491C(temp_call0, temp_call1);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, s16 *, 0x20) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s32 *, 8) = 2;
        M2C_FIELD(temp_v1, s32 *, 0xC) = 0x808080;
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a1, s16 *, 0x16) = 6;
        M2C_FIELD(temp_a1, s16 *, 2) = temp_s2;
        M2C_FIELD(temp_a1, s16 *, 6) = temp_s3;
        temp_s0 += (((s32) (temp_s2 << 0xA) >> 0x10) + (((s32) (temp_s3 << 0xA) >> 0x10) << M2C_FIELD(temp_s4, s16 *, 0x1F0))) * 6;
        ASM_KEEP(temp_s3);
        ASM_KEEP(temp_s2);
        ASM_KEEP(temp_s0);
        M2C_FIELD(temp_v0, u16 **, 0x20) = (u16 *) (temp_s0 + 2);
        M2C_FIELD(temp_s0, s16 *, 0) = 3;
        M2C_FIELD(temp_a1, s16 *, 0xA) = (s16) (0 - *M2C_FIELD(temp_v0, u16 **, 0x20));
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) + 0x20);
        M2C_FIELD(temp_s0, u16 *, 4) = (u16) (M2C_FIELD(temp_s0, u16 *, 4) | 1);
        func_800A56E0(0x603, temp_a1);
        temp_dest = D_800814A8;
        ASM_KEEP(temp_dest);
        temp_tail = M2C_FIELD(temp_dest, u16 *, 0x2A);
        temp_dest = temp_v0 + 0x20;
        ASM_KEEP(temp_tail);
        ASM_KEEP(temp_dest);
        M2C_FIELD(temp_dest, u16 *, 0xE) = temp_tail;
        ASM_KEEP(temp_v0);
    }
}

/* MECHANISM: The 0x28 frame comes from a held D_80083160 base; s0 mutates into the selected record.
   Guarded roles fix s0/s1/s2/s3 and the short v0/v1 tail lifetimes.
   Ordered a0/v0/a1 keeps force the callback page before the call-argument page.
   Split tail source/destination reproduces the final lhu/addiu/store schedule. */
