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
extern u8 D_80045340[];
extern u32 D_80083208[3];
extern u8 D_800DEAE0[];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
void func_8003DB94();                    /* extern */
s32 func_800BCB04();               /* extern */
extern M2C_UNK D_800F6070;

void func_800F6090(s16 arg0, s16 arg1) {
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v0;
    u32 temp_v1;

    temp_v0 = func_8003FC64(0x16);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800F6070;
        func_8004491C(temp_v0, D_80045340);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v1 = (u32) *D_80083208;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, u32 *, 0xC) = temp_v1;
        func_8003DB94(temp_s0, D_800DEAE0, 0);
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x14) = 0xC;
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_s0_2, s16 *, 2) = arg0;
        M2C_FIELD(temp_s0_2, s16 *, 6) = arg1;
        M2C_FIELD(temp_s0_2, s16 *, 0xA) = (s16) (func_800BCB04(arg0 & 0xFFFF, arg1 & 0xFFFF, -0x400) - 8);
    }
}
