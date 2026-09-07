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

M2C_UNK func_8009C12C(); /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800AD594();             /* extern */
M2C_UNK func_80172A3C();                      /* extern */
extern s32 D_8008346C;
extern M2C_UNK D_80170E5C;

void func_801728B4(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *obj = arg0;
    void *entity = arg2;
    void *actor = arg3;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(obj, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        if (M2C_FIELD(entity, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(obj, u8 *, 0x9B) = 2U;
            M2C_FIELD(entity, u16 *, 0x14) =
                (u16)(M2C_FIELD(entity, u16 *, 0x14) | 0x6000);
            func_8009C12C(actor, entity, M2C_FIELD(actor, s16 *, 0x2A), 1);
            return;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        M2C_FIELD(obj, u8 *, 0x9B) =
            (u8)(M2C_FIELD(obj, u8 *, 0x9B) + 1);
        return;

    case 1:
        if ((M2C_FIELD(entity, s8 *, 4) == 7) &&
            (M2C_FIELD(entity, u16 *, 0x14) & 0x1000)) {
            func_800A56E0(0x808);
        }
        if (((M2C_FIELD(entity, s8 *, 4) == 9) &&
             (M2C_FIELD(entity, u16 *, 0x14) & 0x1000)) ||
            (M2C_FIELD(entity, u16 *, 0x14) & 0xE000)) {
            func_8009C12C(actor, entity, M2C_FIELD(actor, s16 *, 0x2A), 1);
            M2C_FIELD(obj, u8 *, 0x9B) =
                (u8)(M2C_FIELD(obj, u8 *, 0x9B) + 1);
        } else {
            return;
        }
        /* fall through */

    case 2:
        if (!(M2C_FIELD(entity, u16 *, 0x14) & 0xE000)) {
            return;
        }
        func_800AD594(actor, 0x100);
        M2C_FIELD(obj, M2C_UNK **, 0x8C) = &D_80170E5C;
        D_8008346C = 0;
        M2C_FIELD(actor, u16 *, 0x46) =
            (u16)(M2C_FIELD(actor, u16 *, 0x46) & 0x7FFF);
        func_800A4ACC(actor);
        break;

    default:
        break;
    }
    
    
}

/* MECHANISM: Guarded s1/s0 pins hold obj/entity while natural actor allocation gives s2.
   A signed s32 state local preserves lbu+slti, and the natural 0/1/2 switch restores
   the local epilogue edges, case-0 increment, exact CFG, and all branch displacements. */
