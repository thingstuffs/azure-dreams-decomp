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
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

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

void func_800B3B18(u8 *arg0);                    /* extern */
void func_800B3CDC(void);                        /* extern */

void func_800B3C74(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 *table;
    s32 *entry;
    s32 var_s1;
    void *var_s2;
    void *var_s0;

    var_s2 = arg0;
    var_s1 = 2;
    var_s0 = var_s2 + 8;
loop_1:
    temp_v0 = M2C_FIELD(var_s0, s32 *, 0xC);
    if (temp_v0 != 0) {
        goto nonzero_count;
    }
    temp_v1 = var_s1 << 2;
    table = M2C_FIELD(var_s2, s32 **, 0x5C);
    entry = (s32 *)(temp_v1 + (s32)table);
    temp_v0 = *entry;
    ASM_USE(temp_v1);
    var_s0 += 4;
    func_800B3B18(M2C_FIELD((s32 *)temp_v0, u8 **, 4));
    ASM_USE(var_s0);
    ASM_USE(var_s1);
    ASM_USE(var_s2);
    func_800B3CDC();
    var_s1 += 1;
    ASM_USE(var_s1);
    return;

nonzero_count:
    ASM_MEM_BARRIER();
    temp_v0--;
    M2C_FIELD(var_s0, s32 *, 0xC) = temp_v0;
    var_s0 += 4;
    ASM_KEEP(var_s0);
    var_s1 += 1;
    if (var_s1 >= 5) {
        return;
    }
    goto loop_1;
}
