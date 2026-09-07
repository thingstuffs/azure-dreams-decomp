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

s32 func_8008FAC0();              /* extern */
void func_800A0F88(void);          /* extern */
extern M2C_UNK D_800834B8;
extern M2C_UNK D_80091260;
extern M2C_UNK D_80091528;
extern M2C_UNK D_800CFCB4;

s32 func_800A0F10(void *arg0, M2C_UNK arg1) {
    if (func_8008FAC0(arg1, &D_800CFCB4) != 0) {
        s32 *global_base = &D_800834B8;
        register s32 global_angle ASM_REG("$3") = M2C_FIELD(global_base, u16 *, 0x10);
        s32 object_angle;

        ASM_KEEP(global_angle);
        object_angle = M2C_FIELD(arg0, u16 *, 0x72);

        if ((u32) (((object_angle & 0xFFF) - (global_angle & 0xFFF)) + 0x3FF) < 0x7FFU) {
            if ((D_800834B8 == (s32)&D_80091260) || (D_800834B8 == (s32)&D_80091528)) {
                func_800A0F88();
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

/* MECHANISM: The 24-byte frame keeps arg0 in s0 across the predicate call.
   Pinning global_angle to v1 and keeping it before the object read fixes load order and result coloring.
   The void tail call plus explicit return 1 preserves the retail j delay-slot constant. */
