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

M2C_UNK func_80060D90();          /* extern */
s32 func_80063828();                  /* extern */
s32 func_80177054();        /* extern */
s32 func_801770A0();                           /* extern */
extern u32 D_801781D0;
extern u32 D_801781D4;
extern s32 D_801781E0;
extern M2C_UNK D_80189388;
extern void *D_80189390;

s32 func_8004072C(void *arg0) {
    s32 sp10;
    void *sp14;
    s32 *var_v0;
    s32 temp_v0_3;
    s32 var_s0;
    s32 var_v1;
    u16 temp_a3;
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_a0;

    var_s0 = 0x800000;
loop_1:
    if (func_80063828(&sp10, &sp14) != 0) {
        func_80060D90(1, &D_80189388);
        var_s0 -= 1;
        if (!(M2C_FIELD(&D_80189388, u8 *, -0x6C78) & 0x10)) {
            if (var_s0 == 0) {
                return func_801770A0(&sp10);
            }
            goto loop_1;
        }
        return func_801770A0();
    }
    if ((u32) M2C_FIELD(sp14, u32 *, 8) >= (u32) D_801781D4) {
        M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x34) = 1;
    }
    temp_a0 = M2C_FIELD(sp14, u32 *, 8);
    temp_a3 = M2C_FIELD(sp14, u16 *, 0x10);
    D_801781D0 = temp_a0;
    if ((M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x38) != temp_a3) || (var_v0 = (s32 *)0x80180000, (M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x3C) != M2C_FIELD(sp14, u16 *, 0x12)))) {
        M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x38) = (s32) temp_a3;
        M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x3C) = (s32) M2C_FIELD(sp14, u16 *, 0x12);
        var_v0 = &D_801781E0;
    }
    if (*var_v0 & 1) {
        return func_80177054(temp_a0, M2C_FIELD(&D_80189390, void **, 0), sp14, temp_a3);
    }
    temp_v0 = M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), u16 *, 0x38);
    M2C_FIELD(arg0, u16 *, 0x1C) = temp_v0;
    M2C_FIELD(arg0, u16 *, 0x14) = temp_v0;
    temp_v0_2 = (u16) M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x3C);
    M2C_FIELD(arg0, u16 *, 0x1E) = temp_v0_2;
    M2C_FIELD(arg0, u16 *, 0x16) = temp_v0_2;
    temp_v0_3 = M2C_FIELD(M2C_FIELD(&D_80189390, void **, 0), s32 *, 0x3C);
    var_v1 = temp_v0_3 + 0xF;
    if (var_v1 < 0) {
        var_v1 = temp_v0_3 + 0x1E;
    }
    M2C_FIELD(arg0, s16 *, 0x2A) = (s16) (var_v1 & 0xFFF0);
    return sp10;
}
