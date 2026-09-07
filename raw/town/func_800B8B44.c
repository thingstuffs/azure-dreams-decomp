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

M2C_UNK bzero();            /* extern */
M2C_UNK func_800B58B8();             /* extern */
M2C_UNK func_800B6094();            /* extern */
M2C_UNK func_800B61C0();            /* extern */

void func_800B62A4(void *arg0, s32 arg1) {
    void *sp10[3];
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");
    register s32 var_s3 ASM_REG("$19");
    s32 var_v0;
    void *temp_a0;
    register s32 *temp_v0 ASM_REG("$2");
    void *var_a1;
    register void *var_s2 ASM_REG("$18");

    var_s1 = 0;
    var_s0 = var_s1;
    var_s3 = 8;
    var_s2 = arg0;
    ASM_KEEP(var_s1);
    ASM_KEEP(var_s3);
    ASM_KEEP(var_s2);
    do {
        if (M2C_FIELD(var_s2, u8 *, 8) != 0) {
            func_800B6094(arg0 + var_s3, arg1, var_s1);
            var_s1 += 1;
        }
        var_s3 += 3;
        var_s0 += 1;
        var_s2 += 3;
    } while (var_s0 < 3);
    bzero(sp10, 0xC);
    func_800B58B8(sp10, arg0);
    var_s0 = 0;
    var_v0 = var_s1 < 3;
    var_s3 = var_s1;
    if (var_v0 != 0) {
        var_s2 = sp10;
        do {
            temp_a0 = *(void **)var_s2;
            if (temp_a0 != NULL) {
                func_800B61C0(temp_a0, arg1, var_s1);
                var_s1 += 1;
            }
            var_s0 += 1;
            var_s2 = (void *)((s8 *)var_s2 + 4);
        } while ((var_s0 + var_s3) < 3);
        var_v0 = var_s1 < 3;
    }
    var_s0 = var_s1;
    if ((var_v0 != 0) && (M2C_FIELD(arg0, u8 *, 0x49) != 0)) {
        func_800B61C0(arg0 + 0x48, arg1, var_s1);
        var_s1 += 1;
        ASM_KEEP(var_s1);
        var_s0 = var_s1;
    }
    if (var_s0 < 3) {
        var_a1 = (var_s0 * 4) + arg1;
        do {
            temp_v0 = M2C_FIELD(var_a1, s32 * volatile *, 0x38);
            var_s0 += 1;
            *temp_v0 = 0;
            ASM_KEEP(temp_v0);
            var_a1 += 4;
        } while (var_s0 < 3);
    }
}
/* MECHANISM: A 3-pointer stack array forces the retail 0x40 frame; unified loop-role
   live ranges plus guarded $s1/$s3/$s2 pins reproduce the hold set.
   cdk-G0's zero-equivalence copy and a volatile $v0 tail load with post-store keep fence
   place $s0++ in the load delay and preserve the retail loop schedule. */
