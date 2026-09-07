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

s32 func_8004A618();                             /* extern */
M2C_UNK func_8004A638();                         /* extern */
s32 func_8004A658();                          /* extern */
s32 func_8004AC3C();                      /* extern */
s32 func_8004DC14();                        /* extern */
M2C_UNK func_8004E5A0();     /* extern */
M2C_UNK func_8004E69C();                   /* extern */
s32 func_8004E928();              /* extern */
M2C_UNK strcat();        /* extern */
M2C_UNK func_800B0BD0();                      /* extern */
M2C_UNK func_800B0D7C();                      /* extern */
s32 func_800B0F30();                             /* extern */
s32 func_800B0F94();                             /* extern */
M2C_UNK func_800B10D4();                            /* extern */
M2C_UNK func_800B15B8();                            /* extern */
extern M2C_UNK D_800D1600;

void func_800B0FD4(void *arg0) {
    register void *ctx ASM_REG("$17") = arg0;
    M2C_UNK sp10[8];
    s32 sp30;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    void *temp_v0;

    func_800B15B8();
    ASM_KEEP(ctx);
    var_s4 = 0;
    temp_v1 = M2C_FIELD(ctx, s32 *, 0x10);
    var_s2 = 0;
    var_s3 = temp_v1 * 5;
    var_s0 = temp_v1 * 0x14;
loop_1:
    if (var_s3 < M2C_FIELD(ctx, s32 *, 0xC)) {
        temp_v0 = var_s0 + M2C_FIELD(ctx, s32 *, 0x24);
        *M2C_FIELD((var_s2 + M2C_FIELD(ctx, s32 *, 0xCC)), s32 **, 0x10) = func_8004A658(M2C_FIELD(temp_v0, u8 *, 1), M2C_FIELD(temp_v0, u8 *, 0));
        *M2C_FIELD((var_s2 + M2C_FIELD(ctx, s32 *, 0xCC)), s32 **, 0x38) = func_8004DC14(func_8004AC3C(M2C_FIELD(ctx, s32 *, 0x24) + var_s0, &sp30), sp30);
        if (func_800B0F94(M2C_FIELD(ctx, s32 *, 0x24) + var_s0) != 0) {
            if (M2C_FIELD(ctx, s32 *, 0x18) == 0) {
                func_800B10D4(func_8004A638(M2C_FIELD(ctx, s32 *, 0x24) + var_s0));
                return;
            }
            func_8004E5A0(func_8004A618(M2C_FIELD(ctx, s32 *, 0x24) + var_s0), 8, &sp10);
            func_8004E69C(&sp10);
            strcat(&sp10, &D_800D1600);
            *M2C_FIELD((var_s2 + M2C_FIELD(ctx, s32 *, 0xCC)), s32 **, 0x4C) = func_8004E928(&sp10, 0);
            goto block_7;
        }
block_7:
        var_s4 += 1;
        var_s3 += 1;
        temp_v0_2 = func_800B0F30(M2C_FIELD(ctx, s32 *, 0x24) + var_s0);
        var_s0 += 4;
        *M2C_FIELD((var_s2 + M2C_FIELD(ctx, s32 *, 0xCC)), s32 **, 0x60) = temp_v0_2;
        var_s2 += 4;
        if (var_s4 >= 5) {
            /* Duplicate return node #8. Try simplifying control flow for better match */
            func_800B0D7C(ctx);
            func_800B0BD0(ctx);
            return;
        }
        goto loop_1;
    }
    func_800B0D7C(ctx);
    func_800B0BD0(ctx);
}
/* MECHANISM: An eight-word stack buffer plus sp30 produces the retail 0x50 frame.
   The guarded $s1 context pin leaves the byte offset in $s0; its post-call keep
   preserves the prologue delay slot. The A638 result feeds the B10D4 tail ABI. */
