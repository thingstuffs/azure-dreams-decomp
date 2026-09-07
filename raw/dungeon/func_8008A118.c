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

s32 func_8004CAE8();                    /* extern */
M2C_UNK func_8008F9F8();                            /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_8009A350();          /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_80081484;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern M2C_UNK D_800DD25C;
extern s32 D_800E3540;

void func_8008F878(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp10;
    M2C_UNK var_a0;
    s32 temp_v1;
    s32 temp_saved;
    void *temp_v0;
    void *temp_v1_2;
    void *temp_s0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 >= 2) {
        goto done;
    }
    if (temp_v1 != 0) {
        goto done;
    }
    if (func_8004CAE8(M2C_FIELD(arg2, s32 *, 8), 0) == 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0x124);
        M2C_FIELD(&D_800DD25C, void **, 0) = temp_v0;
        if (M2C_FIELD(temp_v0, s8 *, 0x13) <= 0) {
            M2C_FIELD(&D_800DD25C, s32 *, 0) = 0;
        }
        temp_v1_2 = M2C_FIELD(arg0, void **, 0x124);
        M2C_FIELD(temp_v1_2, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x1C) & 0xFFF7FFFF);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFEFFFFF);
        func_8009A350(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7, &sp10);
        var_a0 = 0x50C;
        if (sp10 & 0x400) {
            var_a0 = 0x517;
        }
        func_800A56E0(var_a0);
        temp_saved = M2C_FIELD(&D_80081484, s32 *, 0);
        M2C_FIELD(&D_80081484, s32 *, 0) = 0;
        D_800E3540 = temp_saved;
        M2C_FIELD(arg0, u8 *, 0x9B)++;
        func_8008F9F8();
        return;
    }
    return;
state_1:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u8 *, 0x9B) = 2U;
        temp_s0 = &D_80083460;
        M2C_FIELD(temp_s0, u16 *, 2) = (u16) (M2C_FIELD(temp_s0, u16 *, 2) | 0x412);
        func_80099F70(M2C_FIELD(arg3, s32 *, 0x5C));
        func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
        if (M2C_FIELD(&D_800DD25C, void **, 0) != NULL) {
            M2C_FIELD(M2C_FIELD(&D_800DD25C, void **, 0), s8 *, 0x6D) = 0;
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
        M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s0, u16 *, 0xA) - 1);
    }
done:
    return;
}
/* MECHANISM: A dead arg1 restores the live arg0/arg2/arg3 ABI roles in s1/s0/s2.
   Signed explicit state dispatch reproduces the CFG and exact save-store ordering.
   Separate old-value transfer plus a held D_80083460 base closes the +1-word cascade. */
