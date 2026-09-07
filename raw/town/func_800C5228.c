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

M2C_UNK func_8008F074();         /* extern */
s32 func_800C296C();                         /* extern */
M2C_UNK func_800C29C0();                            /* extern */
extern s32 D_8006ADD4;
extern M2C_UNK D_800C2A10;

void func_800C2988(void *arg0, void *arg1) {
    register void *object ASM_REG("$17") = arg0;
    register void *motion ASM_REG("$16") = arg1;

    if (D_8006ADD4 == 0x17000C) {
        register u32 page ASM_REG("$2") = 0xFF600000;

        ASM_PAGEBASE_PIN(page);
        func_800C29C0();
        return;
    }
    M2C_FIELD(motion, s32 *, 8) = 0xFFE00000;
    ASM_SCHED_BARRIER();
    func_8008F074(object, motion, func_800C296C(0));
    M2C_FIELD(object, M2C_UNK **, 0x50) = &D_800C2A10;
    M2C_FIELD(object, s16 *, 0x16) = (s16) ((M2C_FIELD(object, u16 *, 0x72) - 0x800) & 0xFFF);
    ASM_KEEP(object);
    ASM_KEEP(motion);
}

/* MECHANISM: Guarded s1/s0 pins encode the retail arg0/arg1 callee-saved roles and 0x20 frame.
   ASM_PAGEBASE_PIN preserves the dead 0xFF600000 page in the sibcall delay slot.
   A post-store scheduling fence restores retail's lui;sw;jal;move emission order. */
