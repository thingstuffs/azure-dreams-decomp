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

extern M2C_UNK D_800AE600;

void func_800AE630(void *arg0) {
    register M2C_UNK (*temp_v0_2)(void) ASM_REG("$2");
    s32 temp_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    void *temp_a1;
    register void *obj ASM_REG("$4");

    obj = arg0;
    ASM_KEEP(obj);
    temp_a1 = M2C_FIELD(obj, void **, 0xCC);
    var_v1 = M2C_FIELD(obj, s16 *, 0x14) * M2C_FIELD(obj, s32 *, 0x24);
    if (var_v1 < 0) {
        var_v1 += 3;
    }
    M2C_FIELD(temp_a1, s16 *, 8) = (s16) (M2C_FIELD(obj, u16 *, 0xC) + (var_v1 >> 2));
    temp_a1 = M2C_FIELD(obj, void **, 0xCC);
    var_v1_2 = M2C_FIELD(obj, s16 *, 0x16) * M2C_FIELD(obj, s32 *, 0x24);
    if (var_v1_2 < 0) {
        var_v1_2 += 3;
    }
    M2C_FIELD(temp_a1, s16 *, 0xA) = (s16) (M2C_FIELD(obj, u16 *, 0xE) + (var_v1_2 >> 2));
    temp_a1 = M2C_FIELD(obj, void **, 0xCC);
    var_v1_3 = M2C_FIELD(obj, s16 *, 0x18) * M2C_FIELD(obj, s32 *, 0x24);
    if (var_v1_3 < 0) {
        var_v1_3 += 3;
    }
    M2C_FIELD(temp_a1, s16 *, 0xC) = (s16) (M2C_FIELD(obj, u16 *, 0x10) + (var_v1_3 >> 2));
    M2C_FIELD(M2C_FIELD(obj, void **, 0xD0), s16 *, 2) = (s16) ((M2C_FIELD(obj, s32 *, 0x24) << 8) - 0x400);
    temp_v0 = M2C_FIELD(obj, s32 *, 0x24) + 1;
    M2C_FIELD(obj, s32 *, 0x24) = temp_v0;
    if (temp_v0 >= 5) {
        register u8 *page;

        page = (u8 *)0x800B0000;
        ASM_KEEP_NV(page);
        M2C_FIELD(obj, M2C_UNK **, -0x10) = (M2C_UNK *)(page - 0x1A00);
    }
    temp_v0_2 = M2C_FIELD(obj, M2C_UNK (**)(void), 0);
    ASM_KEEP_NV(temp_v0_2);
    if (temp_v0_2 != NULL) {
        temp_v0_2();
    }
}

/* MECHANISM: The true-space function keeps the runtime object in $a0 and reloads
   a block-lived destination pointer before each multiply to occupy the latency slot.
   A kept page/offset split fills the conditional delay slot; the callback stays in $v0. */
