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
extern u8 D_800E3D40[];
extern s32 D_800DCF14;
void func_80099844();           /* extern */
s32 func_800A56E0();                     /* extern */
void func_800A6508();                          /* extern */
M2C_UNK func_800C5BBC(); /* extern */
s32 func_800C8C1C();        /* extern */
void func_800DC1B8();                         /* extern */
extern M2C_UNK D_800E1C03;

s32 func_800CD294(void *arg0) {
    /* fidelity: retail forwards $a0..$a3 into func_800A6508 untouched (it reads
       $a3, which this row never writes).  Name them at the call site through
       ASM_REG pins so the C says what retail does without emitting a byte. */
    register void *fwd_a0 ASM_REG("$4");
    register s32 fwd_a1 ASM_REG("$5");
    register s32 fwd_a2 ASM_REG("$6");
    register s32 fwd_a3 ASM_REG("$7");
    M2C_UNK var_a1;
    void *temp_v1;

    var_a1 = 0x40;
    if (*D_800E3D40 != 0) {
        var_a1 = 0x400;
    }
    if (func_800C8C1C(arg0, var_a1, 0x10) == 0) {
        if (M2C_FIELD(arg0, u8 *, 0x13) == 0) {
            func_800A6508(fwd_a0, fwd_a1, fwd_a2, fwd_a3);
            return 1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return 1;
    }
    func_80099844(arg0, &D_800E1C03);
    if (M2C_FIELD(arg0, u8 *, 0x13) == 0) {
        func_800DC1B8(D_800DCF14);
    }
    temp_v1 = M2C_FIELD(arg0, void **, -0x14);
    if (!(M2C_FIELD(temp_v1, u16 *, 0x14) & 0x8000)) {
        func_800C5BBC((M2C_FIELD(temp_v1, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(temp_v1, u8 *, 0x25) << 6) | 0x20, M2C_FIELD(arg0, s16 *, 0x88), 0xFFFFFF, 0x40, 0);
        func_800A56E0(0x612);
    }
    return 1;
}
