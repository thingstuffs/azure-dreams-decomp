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
typedef struct Packed12 {
    u8 bytes[12];
} Packed12;

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
s32 func_80167088(s32);
extern u8 D_80045C34[];
extern M2C_UNK D_80165AB8;
extern Packed12 D_80173B34;

void func_8016604C(void *arg0) {
    s32 temp_coord;
    s32 temp_coord2;
    s32 temp_rand2;
    s32 temp_v1;
    s32 var_s2;
    s32 var_s3;
    void *temp_s0;
    M2C_UNK *temp_s5;
    void *temp_v0;
    void *temp_v0_2;

    var_s3 = -2;
    temp_s5 = &D_80165AB8;
    do {
        var_s2 = -5;
        do {
            if (!(rand() & 7)) {
                temp_v0 = func_8003FC64(0x12);
                if (temp_v0 != NULL) {
                    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = temp_s5;
                    temp_v1 = rand();
                    temp_coord = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) + (var_s3 << 6);
                    temp_coord -= 0x20;
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) = (s16) (temp_coord + (temp_v1 & 0x3F));
                    temp_rand2 = rand();
                    temp_coord2 = M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6) + (var_s2 << 6);
                    temp_coord2 -= 0x20;
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) = (s16) (temp_coord2 + (temp_rand2 & 0x3F));
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) - 0x100);
                    temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
                    M2C_FIELD(temp_v0_2, s32 *, 0x10) = 0;
                    M2C_FIELD(temp_v0_2, s32 *, 0xC) = 0;
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = 0x200000;
                    func_8004491C(temp_v0, &D_80045C34);
                    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
                    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) & 0xFFF3);
                    temp_v1 = 0x1000 / (s32) (func_80167088(5) + 6);
                    M2C_FIELD(temp_s0, u8 *, 0xC) = 0xFF;
                    M2C_FIELD(temp_s0, s8 *, 0xE) = 0x20;
                    M2C_FIELD(temp_s0, s8 *, 0xD) = 0x20;
                    M2C_FIELD(temp_s0, s16 *, 0x1E) = (s16) temp_v1;
                    M2C_FIELD(temp_s0, s16 *, 0x1C) = (s16) temp_v1;
                    M2C_FIELD(temp_v0, Packed12 *, 0x56) = D_80173B34;
                    M2C_FIELD(temp_s0, void **, 8) = (void *) (temp_v0 + 0x56);
                }
            }
            var_s2 += 1;
        } while (var_s2 <= 0);
        var_s3 += 1;
    } while (var_s3 < 3);
}

/* MECHANISM: True-space nested loops plus a held D_80165AB8 base produce the exact 0x30 frame and s5/s4/s3/s2 roles at cdk-G0.
   A byte-aligned 12-byte aggregate produces the retail lwl/lwr/swl/swr copy; distinct RNG/coordinate locals preserve v1/a0 allocation.
   The final 0xFF field is u8 so GCC materializes 0xff rather than canonicalizing it to -1. */
