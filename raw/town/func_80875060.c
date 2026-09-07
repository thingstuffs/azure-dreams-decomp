/* cfail-repair: tf7-phase1-cache-v3 */
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

typedef void (*TownCallback)(s32, void *, s16 *, s32);

extern u8 D_80700000[];
extern u8 D_80700BB4[];
extern s32 D_80701968[];

void func_80875060(s32 arg0, s32 arg1, s16 *arg2, s32 arg3) {
    TownCallback sp[3];
    s16 *var_a2;
    register s32 var_v0 ASM_REG("$2");
    register s32 var_a0 ASM_REG("$4");
    register s32 var_a3 ASM_REG("$7");
    register void *var_a1 ASM_REG("$5");
    register s32 *var_v1 ASM_REG("$3");
    register s32 var_t0 ASM_REG("$8");
    register s32 zero ASM_REG("$0");

    ASM_SCHED_BARRIER();
    var_a1 = (void *)(D_80700000 + 0xBC8);
    ASM_KEEP(var_a1);
    var_v0 = ((s32 *)var_a1)[0];
    ASM_SCHED_BARRIER();
    var_v1 = ((s32 *)var_a1)[1];
    ASM_SCHED_BARRIER();
    var_a0 = ((s32 *)var_a1)[2];
    sp[0] = (TownCallback)var_v0;
    sp[1] = (TownCallback)var_v1;
    sp[2] = (TownCallback)var_a0;
    ASM_SCHED_BARRIER();
    var_a2 = arg2;
    var_a3 = arg3;
    var_v1 = (s32 *)(D_80700BB4 + 8);
    ASM_KEEP(var_v1);
    var_a0 = 0;
    if (*(s16 *)var_v1 != 0) {
        var_a3 = D_80701968[0];
        var_t0 = zero | 1;
        ASM_KEEP(var_t0);
        var_a2 = (s16 *)var_v1;
loop_2:
        var_a1 = (void *) *var_a2;
        if ((s32)var_a1 < 0) {
            var_v0 = (s32)var_a1 + 0x1F;
        } else {
            var_v0 = (s32)var_a1;
        }
        var_v0 >>= 5;
        ASM_KEEP(var_v0);
        var_v1 = (s32 *)((var_v0 * 4) + var_a3);
        ASM_KEEP(var_v1);
        var_v0 <<= 5;
        var_v0 = (s32)var_a1 - var_v0;
        var_v1 = (s32 *)*var_v1;
        var_v0 = var_t0 << var_v0;
        var_a2 += 1;
        if (var_v0 & (s32)var_v1) {
            var_a0 += 1;
            if (*var_a2 != 0) {
                goto loop_2;
            }
        }
    }
    sp[var_a0](var_a0, var_a1, var_a2, var_a3);
}
