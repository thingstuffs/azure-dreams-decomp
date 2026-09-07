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

typedef struct {
    u8 pad0;
    u8 active;
    u8 pad2[2];
} ActiveEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 value;
    u8 pad6[6];
} PositionEntry;

extern void func_8009A350(s16, s16, s32, u16 *);
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

s32 func_800A70E4(s32 arg0, s32 arg1, s32 arg2) {
    register s32 held_x ASM_REG("$17");
    register s32 held_z ASM_REG("$18");
    register s32 held_y ASM_REG("$16");
    register s32 result ASM_REG("$2");
    register s32 var_a0 ASM_REG("$4");
    register s32 y ASM_REG("$5");
    u16 sp10;
    ActiveEntry *var_a2;
    PositionEntry *var_v1;
    s32 var_v0;
    s32 x;
    s32 z;

    held_x = arg0;
    held_z = arg2;
    func_8009A350((s16)(held_x - 1), (held_y = (s16)arg1), 0, &sp10);
    var_a0 = 0;
    if (sp10 & 0x800) {
        goto scan;
    }
    result = -1;
    goto done;
success:
    result = (s16)var_a0;
    goto done;
scan:
    x = (s16)held_x;
    y = held_y;
    z = (s16)held_z;
    result = 0x800E0000;
    ASM_KEEP(result);
    var_v1 = (PositionEntry *)(result + 0x36C8);
    result = 0x800E0000;
    ASM_KEEP(result);
    var_a2 = (ActiveEntry *)(result + 0x3548);
loop_6:
    if ((var_a2->active != 0) && (var_v1->x == x) && (var_v1->y == y)) {
        var_v0 = z - var_v1->value;
        if (var_v0 < 0) {
            var_v0 = 0 - var_v0;
        }
        if (var_v0 >= 0x40) {
            goto block_12;
        }
        goto success;
    }
block_12:
    var_v1++;
    var_a0 += 1;
    var_a2++;
    if (var_a0 >= 0x40) {
        result = -1;
        goto done;
    }
    goto loop_6;
done:
    ASM_KEEP(held_x);
    ASM_KEEP(held_z);
    ASM_KEEP(held_y);
    ASM_KEEP(var_a0);
    ASM_KEEP(y);
    return result;
}

/* MECHANISM: True-space epilogue targets are two pre-scan return trampolines; s32 formals
   plus guarded s1/s2/s0 carriers reproduce the raw/narrow argument lifetimes and 0x28 saves.
   Counter/y carriers fix volatile roles; v0 page keeps emit the split +36C8/+3548 bases. */
