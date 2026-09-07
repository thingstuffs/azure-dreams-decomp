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

s32 func_800352FC();                             /* extern */
M2C_UNK func_80053DA8();                     /* extern */
M2C_UNK func_800BF9CC();                            /* extern */
M2C_UNK func_800BF9D0();                            /* extern */
s32 func_800C2AB4();                          /* extern */
extern u8 D_80083780[];

void func_800BF8DC(void *arg0, s32 *arg1) {
    s16 temp_v1;
    s32 temp_a0;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x68);
    if (temp_v1 != 1) {
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                func_800BF9D0();
                return;
            }
            goto block_10;
        }
        if (temp_v1 != 2) {
            if (temp_v1 != 3) {
                func_800BF9D0();
                return;
            }
            goto block_17;
        }
block_10:
        {
            register s32 threshold ASM_REG("$3");
            register s32 distance ASM_REG("$2");

            distance = *(s32 *)D_80083780;
            temp_a0 = *arg1;
            distance -= temp_a0;
            threshold = 0x3FFFFF;
            ASM_KEEP(threshold);
            if (distance < 0) {
                distance = -distance;
            }
            ASM_KEEP(distance);
            threshold = threshold < distance;
            if ((threshold == 0) && (func_800352FC() != 0) && (func_800C2AB4(arg0) != 0)) {
                func_80053DA8(0x50B);
                distance = (u16)M2C_FIELD(arg0, s16 *, 0x68);
                ASM_KEEP(distance);
                threshold = 0x20;
                ASM_KEEP(distance);
                ASM_KEEP(threshold);
                M2C_FIELD(arg0, s16 *, 0x6C) = threshold;
                distance++;
                ASM_TAILSLOT_PIN_TIED(distance);
                func_800BF9CC();
            }
        }
    } else {
block_17:
        if ((func_800352FC() == 0) || (func_800C2AB4(arg0) == 0)) {
            M2C_FIELD(arg0, s16 *, 0x68) = (s16) (((u16) M2C_FIELD(arg0, s16 *, 0x68) + 1) & 3);
        }
    }
}

/* MECHANISM: The natural long-lived object pointer gives the retail 24-byte frame and sole s0 save.
   A wide global plus block-local v0 distance/v1 threshold lifetimes reproduces the load and compare order.
   The tied tail-slot pin sinks the kept state increment into func_800BF9CC's converted-j delay slot. */
