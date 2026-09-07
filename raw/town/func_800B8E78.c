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

s32 func_80048DA0();                         /* extern */
s32 func_80048DCC();                             /* extern */
s32 func_80048DE8();                             /* extern */
M2C_UNK func_800B6580();                    /* extern */
M2C_UNK func_800B6688();                            /* extern */
extern u8 D_80089344[];

void func_800B65D8(void *arg0, s32 arg1) {
    register void *base ASM_REG("$23");
    register s32 mode ASM_REG("$21");
    register s32 var_s3 ASM_REG("$19");
    register s32 var_s2 ASM_REG("$18");
    u8 *lookup;
    register void *var_s4 ASM_REG("$20");
    register s32 temp_v0_2 ASM_REG("$2");
    register s32 temp_v0 ASM_REG("$5");
    s32 var_a1;
    s32 var_s0;
    void *temp_s1;
    register void *temp_ptr ASM_REG("$3");

    base = arg0;
    mode = arg1;
    var_s2 = (var_s3 = 0);
    lookup = D_80089344;
    var_s4 = base;
    ASM_KEEP(var_s4);
    ASM_KEEP(lookup);
    ASM_KEEP(base);
    ASM_KEEP(mode);
    ASM_KEEP(var_s3);
    do {
        temp_s1 = M2C_FIELD(var_s4, void **, 0x50);
        var_s0 = func_80048DA0(mode, *(u8 *)((s32)var_s2 + (s32)lookup));
        if ((var_s2 == 0) && (mode == 4)) {
            var_s0 -= 1;
        }
        M2C_FIELD(temp_s1, s32 *, 0) = func_80048DCC(var_s0);
        temp_v0 = func_80048DE8(var_s0);
        ASM_KEEP(temp_v0);
        if (temp_v0 == 0x10) {
            M2C_FIELD(M2C_FIELD(temp_s1, void **, 4), s16 *, 0xA) = 0;
            func_800B6688();
            return;
        }
        temp_v0_2 = var_s3 - (var_s2 * 8);
        ASM_KEEP(temp_v0_2);
        temp_ptr = M2C_FIELD(temp_s1, void **, 4);
        ASM_KEEP(temp_ptr);
        var_s3 += temp_v0;
        M2C_FIELD(temp_ptr, s16 *, 0xA) = temp_v0_2;
        ASM_KEEP(temp_ptr);
        var_s2 += 1;
        var_s4 += 4;
    } while (var_s2 < 2);
    ASM_KEEP(var_s2);
    ASM_KEEP(var_s4);
    var_a1 = 0;
    if (var_s3 != 0) {
        var_a1 = var_s3 - 0x14;
    }
    func_800B6580(*M2C_FIELD(base, s32 **, 0x5C), var_a1);
}
