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

M2C_UNK func_800A06E8();                            /* extern */
M2C_UNK func_800A06EC();                            /* extern */
extern M2C_UNK D_800A0708;
extern M2C_UNK D_800A07A4;
extern M2C_UNK D_800A0AC8;
extern M2C_UNK D_800A0BE4;
extern M2C_UNK D_800D09E0;

void func_800A06A4(void *arg0, s32 arg1) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x94);
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800A0708;
    if (temp_v1 == 1) {
        register M2C_UNK *next ASM_REG("$2");

        M2C_FIELD(arg0, s16 *, 0x90) = 2;
        next = &D_800A0BE4;
        ASM_TAILSLOT_PIN(next);
        func_800A06E8();
        return;
    }
    if (temp_v1 == 0) {
        register M2C_UNK *next ASM_REG("$2");

        next = &D_800A0AC8;
        ASM_TAILSLOT_PIN(next);
        func_800A06EC();
        return;
    }
    {
        M2C_UNK *handler;

        ASM_SCHED_BARRIER();
        handler = &D_800A07A4;
        ASM_KEEP(handler);
        M2C_FIELD(arg0, s16 *, 0x6E) = 0;
        ASM_MEM_BARRIER();
        M2C_FIELD(arg0, M2C_UNK **, 0x50) = handler;
    }
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_800D09E0;
    M2C_FIELD(arg0, s16 *, 0x68) = 0;
}

/* MECHANISM: Frameless leaf CFG with guarded $v0 continuation-address pins preserves both shared-entry tail jumps.
   A block-entry schedule barrier selects the fall-through lui for the branch slot; a held callback pointer
   plus memory fence fixes the sh-before-sw order. The length-exact lineage is 2.95.2-G0. */
