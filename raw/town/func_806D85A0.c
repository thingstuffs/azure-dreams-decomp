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

void *func_80017024();                 /* extern */
s32 func_8001876C();                         /* extern */
extern volatile M2C_UNK D_80016000;
extern M2C_UNK D_80018FE0;

void func_806D85A0(void) {
    s32 temp_a0;
    s32 temp_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_s1;
    register s32 var_s2 ASM_REG("$18");
    s32 var_s4;
    s32 var_s5;
    register s32 var_s7 ASM_REG("$23");
    s32 temp_v0;
    register s32 call_a0 ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register void *temp_v1 ASM_REG("$3");
    register void *temp_func ASM_REG("$2");
    void *temp_s0;
    register void *temp_s3 ASM_REG("$19");
    void *var_s6;

    temp_s0 = M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x38);
    if (func_8001876C(1) == 0) {
        temp_v0 = func_8001876C(2);
        var_s7 = 2;
        if (temp_v0 != 0) {
            var_s7 = 1;
        }
    } else {
        var_s7 = 0;
    }
    call_a0 = 4;
    ASM_KEEP_NV(call_a0);
    call_a1 = call_a0;
    call_a2 = 0;
    ASM_KEEP_NV(call_a1);
    ASM_KEEP_NV(call_a2);
    temp_func = (void *)0x80010000;
    ASM_KEEP_NV(temp_func);
    temp_v1 = M2C_FIELD(temp_func, void **, 0x6000);
    ASM_KEEP(temp_v1);
    var_s4 = call_a2;
    temp_func = M2C_FIELD(temp_v1, void **, 0x20);
    ASM_KEEP_NV(temp_func);
    var_s5 = var_s7 * 8;
    temp_func = M2C_FIELD(temp_func, void **, 0x2D0);
    ASM_KEEP(temp_func);
    var_s6 = temp_s0;
    ((M2C_UNK (*)(M2C_UNK, M2C_UNK, M2C_UNK))temp_func)(call_a0, call_a1, call_a2);
    do {
        var_s2 = 0;
        if (M2C_FIELD(&D_80018FE0, s16 *, var_s5) > 0) {
            s16 *temp_fp;

            temp_func = (void *)0x80020000;
            ASM_KEEP_NV(temp_func);
            temp_fp = (s16 *)((s8 *)temp_func - 0x7020);
loop_6:
            if (M2C_FIELD(var_s6 + var_s2, u8 *, 0x3640) != 0) {
                temp_s3 = func_80017024(var_s4, var_s2, var_s7);
                if (var_s4 == 0) {
                    var_s1 = 0;
                    do {
                        var_s0 = 0;
loop_10:
                        var_a2 = var_s1 + var_s0;
                        temp_a0 = M2C_FIELD(temp_s3, s16 *, 0) + var_s1;
                        temp_a1 = M2C_FIELD(temp_s3, s16 *, 2) + var_s0;
                        M2C_FIELD(M2C_FIELD(M2C_FIELD(&D_80016000, void **, 0), void **, 0x20), M2C_UNK (**)(s32, s32, s32), 0x2D0)(temp_a0, temp_a1, var_a2);
                        var_s0 += 1;
                        if (var_s0 < 2) {
                            goto loop_10;
                        }
                        var_s1 += 1;
                    } while (var_s1 < 2);
                }
                var_s2 += 1;
                if (var_s2 < M2C_FIELD((s8 *)(u32)var_s5, s16 *, (s32)temp_fp)) {
                    goto loop_6;
                }
            }
        }
        var_s5 += 0x18;
        var_s4 += 1;
        var_s6 += 0xC;
    } while (var_s4 < 0x10);
}
