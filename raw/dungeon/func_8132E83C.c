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
typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;

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
s32 rand(void);
extern u8 D_80045340;
extern u8 D_801654F0[];
extern M2C_UNK D_80173B34[3];

void func_8016583C(void *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;
    register s16 arg1_hold ASM_REG("$22") = arg1;
    register s32 arg2_hold ASM_REG("$21") = arg2;
    register s32 arg4_hold ASM_REG("$19") = arg4;
    register s32 arg3_hold ASM_REG("$16") = arg3;
    register s32 arg5_hold ASM_REG("$20") = arg5;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801654F0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + arg3_hold);
        ASM_KEEP(arg3_hold);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + arg4_hold);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) + arg5_hold);
        temp_s0 = temp_v0 + 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x42) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(temp_s0, u16 *, 0x44) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(temp_s0, u16 *, 0x46) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0xC) = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x10) = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = arg6;
        M2C_FIELD(temp_s0, s16 *, 0x14) = arg1_hold;
        M2C_FIELD(temp_s0, s16 *, 0x32) = 8;
        M2C_FIELD(temp_s0, s16 *, 0x34) = 8;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x200;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x200;
        M2C_FIELD(temp_a0, s32 *, 0xC) = arg2_hold;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) & 0xFFF3);
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg2_hold;
        M2C_FIELD(temp_s0, s32 *, 4) = arg2_hold;
        M2C_FIELD(temp_s0, s32 *, 8) = arg2_hold;
        M2C_FIELD(temp_v0, Copy12 *, 0x56) =
            M2C_FIELD(D_80173B34, Copy12 *, 0);
        M2C_FIELD(temp_a0, void **, 8) = (void *) (temp_v0 + 0x56);
        ASM_KEEP(arg1_hold);
        ASM_KEEP(arg2_hold);
        ASM_KEEP(arg4_hold);
        ASM_KEEP(arg5_hold);
    }
}

/* MECHANISM: Explicit s0/s3-s6 argument roles reproduce the 0x30 frame, save order,
   and held stack-argument lifetimes at the true-space func_8016583C entry.
   One packed 12-byte assignment emits the retail lwl/lwr plus swl/swr copy sequence. */
