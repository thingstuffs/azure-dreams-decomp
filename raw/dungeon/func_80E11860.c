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

void func_8003DB94(void *, void *, s32);  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEA68;
extern M2C_UNK D_80174F64;

s32 func_80175060(void *arg0, void *arg1) {
    s32 color;
    s32 four;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80174F64;
        var_v0 = rand();
        temp_a0 = var_v0;
        temp_s0 = temp_v0 + 0x20;
        if (temp_a0 < 0) {
            var_v0 = temp_a0 + 0xFFF;
        }
        color = 0x606060;
        M2C_FIELD(temp_s0, s16 *, 4) = (s16) (temp_a0 - ((var_v0 >> 0xC) << 0xC));
        ASM_CLOBBER("$5");
        four = 4;
        ASM_KEEP(four);
        M2C_FIELD(temp_s0, s16 *, 8) = (s16) four;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s32 *, 0xC) = color;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20);
        func_8003DB94(temp_s0, &D_800DEA68, 0);
        func_800478B8(temp_s0);
        var_v0_2 = rand();
        temp_v1 = var_v0_2;
        if (temp_v1 < 0) {
            var_v0_2 = temp_v1 + 0xFFF;
        }
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (temp_v1 - ((var_v0_2 >> 0xC) << 0xC));
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        {
            register s32 copy0 ASM_REG("$2");
            register s32 copy1 ASM_REG("$4");
            register s32 copy2 ASM_REG("$5");
            register s32 copy3 ASM_REG("$6");

            temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
            ASM_KEEP(temp_v1_2);
            copy0 = M2C_FIELD(arg1, s32 *, 0);
            copy1 = M2C_FIELD(arg1, s32 *, 4);
            copy2 = M2C_FIELD(arg1, s32 *, 8);
            copy3 = M2C_FIELD(arg1, s32 *, 0xC);
            M2C_FIELD(temp_v1_2, s32 *, 0) = copy0;
            M2C_FIELD(temp_v1_2, s32 *, 4) = copy1;
            M2C_FIELD(temp_v1_2, s32 *, 8) = copy2;
            M2C_FIELD(temp_v1_2, s32 *, 0xC) = copy3;
            ASM_KEEP(copy2);
            ASM_KEEP(copy3);
            copy0 = M2C_FIELD(arg1, s32 *, 0x10);
            copy1 = M2C_FIELD(arg1, s32 *, 0x14);
            M2C_FIELD(temp_v1_2, s32 *, 0x10) = copy0;
            M2C_FIELD(temp_v1_2, s32 *, 0x14) = copy1;
            ASM_MEM_BARRIER();
            copy0 = M2C_FIELD(temp_v1_2, s32 *, 0);
            copy1 = M2C_FIELD(temp_v1_2, s32 *, 4);
            M2C_FIELD(temp_v1_2, s32 *, 0xC) = copy0;
            M2C_FIELD(temp_v1_2, s32 *, 0x10) = copy1;
            ASM_KEEP(copy0);
            ASM_KEEP(copy1);
        }
        M2C_FIELD(temp_v1_2, u16 *, 0xA) = M2C_FIELD(arg0, u16 *, 0x88);
        return (s32) temp_v0;
    }
    return 0;
}

/* MECHANISM: The true-space function and one shared scratch/child pointer produce the
   retail 0x28 frame and s3/s2/s1/s0 lifetimes; the success tail returns the object locally.
   Four guarded copy temporaries reproduce the 24-byte v0/a0/a1/a2 copy, with a memory fence.
   A color local, a1 clobber, and kept four order the final li/la/store triplet exactly. */
