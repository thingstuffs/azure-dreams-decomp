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

void *func_800196A8(void *, s32);                /* extern */
extern s8 D_8001DCCC[];

typedef struct {
    s32 unk0;
    void *unk4;
    s32 *unk8;
    s8 *unkC;
} Func8032EEE4Record;

Func8032EEE4Record *func_800196E4(void *arg0, Func8032EEE4Record *arg1) {
    s32 temp_s1;
    register s32 *temp_a0 ASM_REG("$4");
    register Func8032EEE4Record *temp_v0 ASM_REG("$5");

    temp_s1 = arg1->unk0 & 0x3FFF0000;
    temp_v0 = (Func8032EEE4Record *) func_800196A8(arg0, temp_s1);
    ASM_KEEP(temp_v0);
    if (temp_v0->unk4 == NULL) {
        register s32 temp_v1 ASM_REG("$3");
        register s32 temp_v0_base ASM_REG("$2");
        temp_a0 = arg1->unk8;
        ASM_KEEP(temp_a0);
        temp_v1 = (s32) arg1->unkC;
        ASM_KEEP(temp_v1);
        temp_v0_base = D_8001DCCC;
        ASM_KEEP(temp_v0_base);
        temp_v1 = temp_v1 - temp_v0_base;
        temp_v1 = temp_v1 + 4;
        *temp_a0 = temp_v1;
        temp_v0_base = (s32) arg1->unk8;
        ASM_KEEP(temp_v0_base);
        temp_v0->unk4 = (void *) temp_v0_base;
        temp_v0->unk0 = temp_s1;
        temp_v0->unkC = 0;
    }
    return temp_v0;
}
