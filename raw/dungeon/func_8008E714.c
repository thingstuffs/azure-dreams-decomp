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
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

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

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[3];
} Copy12;

typedef struct {
    s32 words[35];
} Copy140;

s32 func_80042900();                 /* extern */
void func_8009A3D0(u8, u8, s32);     /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];

void func_80093E74(s32 arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2_2;
    u8 var_a0_4;
    u8 var_a1_4;
    s32 temp_s0;
    register s32 temp_v0_3 ASM_REG("$2");
    register s32 temp_s3 ASM_REG("$19");
    register void **temp_base2 ASM_REG("$3");
    void **temp_s2;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_s1;
    void *temp_t0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    void *var_a2;
    void *var_a3;

    {
        register s32 temp_v1_byte ASM_REG("$3");
        register s32 temp_v0 ASM_REG("$2");
        register void *temp_a0 ASM_REG("$4");
        register void **temp_base ASM_REG("$2");
        u8 temp_s3_byte;

        temp_a0 = M2C_FIELD(((M2C_FIELD(arg3, s16 *, 0x8A) * 4) + arg0), void **, 0xD0);
        temp_v0 = M2C_FIELD(temp_a0, u8 *, 3);
        temp_v1_byte = temp_v0 & 0xDF;
        temp_v0 &= 0x1F;
        ASM_KEEP(temp_v0);
        temp_s3_byte = (u8)temp_v0;
        temp_s3 = temp_s3_byte;
        ASM_KEEP(temp_s3);
        temp_s0 = temp_s3;
        ASM_KEEP(temp_s0);
        temp_base = D_800E3DF0;
        M2C_FIELD(temp_a0, u8 *, 3) = (u8) temp_v1_byte;
        temp_s2 = temp_base + temp_s0;
        temp_s1 = *temp_s2;
    }
    if ((func_80042900(temp_s1, 0xA) << 0x10) != 0) {
        M2C_FIELD(temp_s1, u8 *, 0x13) = (u8) M2C_FIELD(temp_s1, u8 *, 0xA8);
    }
    temp_v0_2 = &D_800E3E48[((((temp_s0 * 8) + temp_s0) * 4) - temp_s0) * 4];
    *temp_s2 = temp_v0_2;
    *(Copy140 *) temp_v0_2 = *(Copy140 *) temp_s1;
    temp_base2 = D_800E3DF0;
    ASM_KEEP(temp_base2);
    temp_v0_3 = temp_s3 << 2;
    temp_v0_3 += (s32)temp_base2;
    temp_a0_2 = *(void **)temp_v0_3;
    M2C_FIELD(temp_a0_2, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 0x14) & ~0x4000);
    M2C_FIELD(((M2C_FIELD(arg3, s16 *, 0x8A) * 4) + arg0), s32 *, 0xD0) = 0;
    temp_a0_3 = M2C_FIELD(arg3, void **, 0x60);
    M2C_FIELD(temp_a0_3, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a0_3, s32 *, 0x1C) | 0x400000);
    temp_v1 = M2C_FIELD(arg3, void **, 0x60);
    temp_v1_2 = M2C_FIELD(temp_v1, void **, -0x14);
    var_a0_4 = M2C_FIELD(temp_v1_2, u8 *, 0x24);
    var_a1_4 = M2C_FIELD(temp_v1_2, u8 *, 0x25);
    var_a2_2 = 0x3000;
    if (M2C_FIELD(temp_v1, s32 *, 0x1C) & 0x2000) {
        var_a2_2 = 0x300;
    }
    func_8009A3D0(var_a0_4, var_a1_4, var_a2_2);
    func_800A56E0(0x704);
}
