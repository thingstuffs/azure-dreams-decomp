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

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80067014();
M2C_UNK func_800671A8();
s32 func_80123200();
void func_80123928();
void func_801239B8();
void func_80123BF4(void) __attribute__((noreturn));
extern M2C_UNK D_8011ACD8;
extern M2C_UNK D_80126E98;

void func_80123A60(void *arg0) {
    s16 stack_values[4];
    s32 *var_s2;
    register s32 *temp_base ASM_REG("$3");
    s32 var_s0;
    register s32 var_s1 ASM_REG("$17");
    u8 temp_v0;
    u8 temp_v1;

    stack_values[0] = 0x180;
    stack_values[1] = 0x80;
    stack_values[2] = 0x36;
    stack_values[3] = 0x60;
    func_800671A8(stack_values, 0, 0, 0);
    func_801239B8(&D_8011ACD8, 0x192, 0xD0);
    func_80067014(0);
    var_s1 = 0;
    if (M2C_FIELD(arg0, u8 *, 0xF) == 3) {
        var_s1 = M2C_FIELD(arg0, u8 *, 0xF);
        var_s0 = var_s1 * 0x10;
        if (func_80123200(var_s0 & 0xF0) & 0xFF) {
            temp_base = &D_80126E98;
            func_80123928(*(((var_s1 * 0x20) + var_s0) + temp_base), 0x180, 0x80);
        }
        var_s0 += 1;
        if (func_80123200(var_s0 & 0xFF) & 0xFF) {
            temp_base = &D_80126E98;
            func_80123928(*((var_s0 * 3) + temp_base), 0x1A4, 0xA0);
            func_80123BF4();
        }
        func_80067014(0);
        return;
    }
    ASM_MEM_BARRIER();
    temp_v0 = M2C_FIELD(arg0, u8 *, 0xF);
    var_s0 = temp_v0 * 0x10;
    temp_base = &D_80126E98;
    var_s2 = ((temp_v0 * 0x20) + var_s0) + temp_base;
    do {
        if (func_80123200(var_s0 & 0xFF) & 0xFF) {
            func_80123928(*var_s2, (s16) (((var_s1 % 3) * 0x12) + 0x180), (s16) (((var_s1 / 3) * 0x10) + 0x80));
        }
        var_s1 += 1;
        var_s2 += 3;
        var_s0 += 1;
    } while (var_s1 < 0x10);
    func_80067014(0);
}
