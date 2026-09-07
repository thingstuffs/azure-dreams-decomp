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

M2C_UNK func_8001A188();     /* extern */
M2C_UNK func_8001A2BC();                            /* extern */
extern void *D_80016000[3];
extern u8 D_8001791C[96];

void func_8001A200(void *arg0, s32 *arg1) {
    u8 *var_a2;
    s32 temp_a0;
    register s32 temp_s2 ASM_REG("$18");
    s32 temp_v1;
    void *temp_v0;
    s32 var_a1;
    s32 var_a3;
    register u8 *var_s3 ASM_REG("$19");
    register u8 *var_s1 ASM_REG("$17");
    register void *var_s0 ASM_REG("$16");
    register u8 *split_base ASM_REG("$2");
    register s32 final_status ASM_REG("$3");
    register s32 final_mask ASM_REG("$2");

    var_s0 = arg0;
    temp_v0 = M2C_FIELD(D_80016000[0], void **, 0x20);
    var_s1 = (u8 *)arg1;
    temp_s2 = *((M2C_FIELD(temp_v0, s32 (**)(M2C_UNK), 0x2D4)(0)) + (s32 *)var_s1);
    if ((M2C_FIELD(var_s0, u8 *, 1) & 0xC0) != 0x80) {
        split_base = (u8 *)0x80010000;
        ASM_KEEP(split_base);
        var_s3 = split_base + 0x791C;
        var_s1 = var_s0 + 1;
loop_2:
        var_a3 = 1;
        var_a1 = temp_s2 + 4;
        var_a2 = var_s3 + 0xC;
loop_3:
        temp_v1 = *(s32 *)var_a2;
        temp_a0 = M2C_FIELD(var_s1, s32 *, 0xB);
        if ((temp_v1 == temp_a0) || ((temp_v1 == 6) && (temp_a0 == 0x64))) {
            func_8001A188(var_s0, var_a1, var_a2, var_a3);
            func_8001A2BC();
            var_s1 += 0x14;
            ASM_KEEP(var_s1);
            return;
        }
        var_a1 += 4;
        var_a3 += 1;
        var_a2 += 0xC;
        if (var_a3 >= 8) {
            var_s1 += 0x14;
            var_s0 += 0x14;
            final_status = *var_s1;
            final_mask = 0x80;
            if ((final_status & 0xC0) == final_mask) {
            } else {
                goto loop_2;
            }
        } else {
            goto loop_3;
        }
    }
}
