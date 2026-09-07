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

void *func_800A75B8();                         /* extern */
M2C_UNK func_800ABD74();               /* extern */
extern M2C_UNK D_800A70EC;
extern M2C_UNK D_800D0DD8;

void func_800A6F48(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 position[5];
    M2C_UNK *temp_v1;
    M2C_UNK *temp_v1_4;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_v0;
    void *temp_v0_2;
    register void *temp_v0_3 ASM_REG("$5");
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_5;

    M2C_FIELD(arg1, M2C_UNK **, 0xC) = &D_800D0DD8;
    temp_v0 = M2C_FIELD(&D_800D0DD8, s32 *, 4) + M2C_FIELD(&D_800D0DD8, s32 *, 0x10);
    position[0] = M2C_FIELD(arg2, s32 *, 0) + ((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1);
    temp_v1 = M2C_FIELD(arg1, M2C_UNK **, 0xC);
    position[1] = M2C_FIELD(arg2, s32 *, 4) + M2C_FIELD(temp_v1, s32 *, 4) + M2C_FIELD(temp_v1, s32 *, 0x10);
    position[2] = M2C_FIELD(arg2, s32 *, 8);
    temp_v0_2 = func_800A75B8(position);
    M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 8), s32 *, 0xC) = 0x10000;
    temp_v1_2 = M2C_FIELD(temp_v0_2, void **, 8);
    var_v0 = M2C_FIELD(temp_v1_2, s32 *, 0x10);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    M2C_FIELD(temp_v1_2, s32 *, 0x10) = (s32) (var_v0 >> 2);
    temp_v1_3 = M2C_FIELD(temp_v0_2, void **, 8);
    var_v0_2 = M2C_FIELD(temp_v1_3, s32 *, 0x14);
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    M2C_FIELD(temp_v1_3, s32 *, 0x14) = (s32) (var_v0_2 >> 2);
    M2C_FIELD(temp_v0_2, s16 *, 0xB0) = 0;
    func_800ABD74(position, temp_v0_2);
    temp_v1_4 = M2C_FIELD(arg1, M2C_UNK **, 0xC);
    position[0] = M2C_FIELD(arg2, s32 *, 0) - ((M2C_FIELD(temp_v1_4, s32 *, 4) + M2C_FIELD(temp_v1_4, s32 *, 0x10)) / 3);
    temp_v0_3 = func_800A75B8(position);
    ASM_KEEP(temp_v0_3);
    M2C_FIELD(M2C_FIELD(temp_v0_3, void **, 8), s32 *, 0xC) = -0x8000;
    temp_v1_5 = M2C_FIELD(temp_v0_3, void **, 8);
    M2C_FIELD(temp_v1_5, s32 *, 0x10) = (s32) (M2C_FIELD(temp_v1_5, s32 *, 0x10) / 3);
    M2C_FIELD(temp_v0_3, s16 *, 0xB0) = 0;
    func_800ABD74(position, temp_v0_3);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800A70EC;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0xA;
    M2C_FIELD(arg3, u8 *, 0xE) = 0x80;
    M2C_FIELD(arg3, u8 *, 0xD) = 0x80;
    M2C_FIELD(arg3, u8 *, 0xC) = 0x80;
}

/* MECHANISM: A five-word position array exposes all three initialized siblings and
   supplies the retail 0x40 frame; the four arguments naturally occupy s3/s0/s1/s2.
   A guarded $a1 pin holds the second factory result across its field updates, while
   unsigned byte lvalues preserve the retail li 0x80 before the final sb sequence. */
