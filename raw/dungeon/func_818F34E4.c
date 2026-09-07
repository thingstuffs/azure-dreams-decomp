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
typedef struct Block24 {
    s32 word[6];
} Block24;
typedef union Product64 {
    s64 value;
    struct {
        s32 hi;
        u32 lo;
    } word;
} Product64;

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

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083780[12];
extern int D_800814A8[4];
extern s32 D_800814A0[3];
void func_80024E0C() __attribute__((noreturn));
s32 func_800644B8(s16);           /* extern */
s16 func_800BCB04();              /* extern */
extern s16 D_800259AC;

void func_80024CE4(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s16 temp_init;
    s16 temp_a0;
    s16 temp_v0_2;
    s16 temp_v0_4;
    s16 temp_v1;
    s16 var_a0_2;
    s16 var_a1_2;
    s16 var_v1;
    s32 temp_dividend;
    s32 temp_lo;
    s32 temp_v0_3;
    s8 temp_v1_2;
    u16 temp_a2;
    u16 temp_v0;
    u16 temp_v1_3;
    void *var_a0;
    void *temp_base;
    void *temp_s0;
    void *temp_s2;
    void *temp_s3;
    void *var_a1;
    Product64 temp_product;

    var_a1 = arg1;
    temp_s2 = var_a1;
    D_800259AC = 1;
    temp_base = &D_80083178;
    temp_s3 = (u8 *) temp_base + 0xB8;
    temp_init = M2C_FIELD(arg0, s16 *, 0);
    var_a0 = (void *) (u32) M2C_FIELD(arg0, u16 *, 0);
    if (temp_init == 0) {
        M2C_FIELD(arg0, s16 *, 0) = (s16) ((u32) var_a0 + 1);
        temp_s0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), void **, -0x18);
        M2C_FIELD(arg0, Block24 *, 0x44) = M2C_FIELD(temp_s0, Block24 *, 0);
        ASM_KEEP_NV(temp_s2);
        var_a0 = arg0 + 0x44;
        if ((M2C_FIELD(temp_s3, u8 **, 0x20) == D_80083780) && (M2C_FIELD(arg0, void **, 0x2C) == *D_800814A8)) {
            M2C_FIELD(temp_s3, u8 **, 0x20) = (u8 *) var_a0;
            M2C_FIELD(arg0, s16 *, 0xA) = 9;
        }
    }
    M2C_FIELD(arg0, u16 *, 0x3C) = 0x40U;
    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) - 1);
    M2C_FIELD(arg0, u16 *, 0x3A) = (u16) (M2C_FIELD(arg0, u16 *, 0x3A) + 0x96);
    temp_v1 = M2C_FIELD(arg0, s16 *, 2);
    if (temp_v1 >= 0x51) {
        M2C_FIELD(arg0, u16 *, 0x38) = (u16) (M2C_FIELD(arg0, u16 *, 0x38) + 4);
        func_80024E0C();
        return;
    }
    if (temp_v1 < 0x32) {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x38) - 5;
        M2C_FIELD(arg0, u16 *, 0x38) = temp_v0;
        if ((s16) temp_v0 < 0) {
            M2C_FIELD(arg0, u16 *, 0x38) = 0U;
        }
    }
    ASM_KEEP(arg3);
    temp_a0 = (s16) M2C_FIELD(arg0, u16 *, 2);
    if (temp_a0 < 0x14) {
        temp_dividend = temp_a0 << 7;
        {
            register s32 hi_pin ASM_REG("$7");
            {
                register s32 magic_pin ASM_REG("$3");
                magic_pin = 0x66666667;
                ASM_KEEP_NV(magic_pin);
                temp_product.value = (s64) temp_dividend * magic_pin;
                ASM_KEEP_NV(temp_product.word.hi);
                hi_pin = temp_product.word.hi;
                ASM_KEEP_NV(hi_pin);
            }
            {
                register s32 sh_pin ASM_REG("$3");
                sh_pin = (hi_pin >> 3) - (temp_dividend >> 31);
                ASM_KEEP_NV(sh_pin);
                temp_v1_2 = sh_pin;
            }
        }
        M2C_FIELD(arg2, s8 *, 0xE) = temp_v1_2;
        M2C_FIELD(arg2, s8 *, 0xD) = temp_v1_2;
        M2C_FIELD(arg2, s8 *, 0xC) = temp_v1_2;
    }
    temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x1C);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x10);
    if (temp_v1_3 < 0x1000U) {
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (temp_v1_3 + 0x100);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) + 0x100);
    }
    do {
        var_a1_2 = 0;
    } while (0);
    var_a0_2 = M2C_FIELD(arg0, u16 *, 0x3A);
    temp_a2 = M2C_FIELD(arg0, u16 *, 0x3C);
    var_v1 = var_a0_2 + temp_a2;
    do {
        if (var_v1 >= 0x1001) {
            var_a0_2 = var_v1 - 0x1000;
        } else {
            var_a0_2 = var_v1;
        }
        temp_v0_2 = var_a1_2 + 1;
        var_a1_2 = temp_v0_2;
        var_v1 = var_a0_2 + temp_a2;
    } while (temp_v0_2 < 0x20);
    temp_s0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), void **, -0x18);
    temp_lo = func_800644B8(var_a0_2) * (s16) M2C_FIELD(arg0, u16 *, 0x38);
    temp_v0_3 = temp_lo * 2;
    M2C_FIELD(temp_s0, s32 *, 8) = temp_v0_3;
    M2C_FIELD(temp_s0, s32 *, 8) = (s32) (temp_v0_3 + M2C_FIELD(arg0, s32 *, 0x40));
    temp_v0_4 = func_800BCB04(M2C_FIELD(temp_s2, u16 *, 2), M2C_FIELD(temp_s2, u16 *, 6), M2C_FIELD(temp_s2, s16 *, 0xA), temp_lo);
    if (temp_v0_4 < M2C_FIELD(temp_s0, s16 *, 0xA)) {
        M2C_FIELD(temp_s0, s16 *, 0xA) = temp_v0_4;
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 2) <= 0) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s16 *, 0x9C) = 1;
        if (M2C_FIELD(arg0, s16 *, 0xA) == 9) {
            M2C_FIELD(temp_s3, u8 **, 0x20) = D_80083780;
        }
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
