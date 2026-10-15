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

s32 func_8003E240();                         /* extern */
M2C_UNK func_8005A4E8();   /* extern */
M2C_UNK func_8005A56C();           /* extern */
M2C_UNK func_8005FE18();                     /* extern */
M2C_UNK func_8006124C();          /* extern */
M2C_UNK func_80063538();                            /* extern */
M2C_UNK func_8006636C(); /* extern */
M2C_UNK func_80066424(); /* extern */
M2C_UNK func_80066F78();                     /* extern */
M2C_UNK func_80067688();                         /* extern */
M2C_UNK func_800678E0();                   /* extern */
M2C_UNK func_80176B60();        /* extern */
M2C_UNK func_80176BEC(); /* extern */
s32 func_80176E90();                          /* extern */
M2C_UNK func_801770BC();             /* extern */
s32 func_80177240(); /* extern */
s32 func_80177354();                                /* extern */
s32 func_8017748C();                                /* extern */
s32 func_80177504();                                /* extern */
s32 func_801775AC();                         /* extern */
s32 func_80177614();                             /* extern */
M2C_UNK func_80177844();                    /* extern */
M2C_UNK func_801778C0();                    /* extern */
extern u8 D_80082E6B;
extern s32 D_80083160;
extern M2C_UNK D_80176CA8;
extern s32 D_801781D0;
extern s32 D_801781D4;
extern s32 D_801781E0;
extern M2C_UNK *D_80189390;
extern M2C_UNK D_80189398;

s32 func_8004099C(s32 arg1, M2C_UNK arg2, s32 arg3) {
    M2C_UNK sp18;
    s16 sp1C;
    s8 sp29;
    M2C_UNK sp30;
    M2C_UNK **var_v0;
    M2C_UNK *var_a0_3;
    s16 temp_a1;
    s32 *var_v0_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s2;
    s32 var_s4;
    s32 var_s7;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    u32 temp_lo;
    u32 var_s6;
    void *temp_v0;
    void *temp_v0_2;

    var_s4 = 0;
    var_s6 = 1;
    var_s7 = 0;
    D_801781D4 = arg1 - 8;
    D_801781D0 = 0;
    M2C_FIELD(&D_80189390, M2C_UNK **, 0) = &D_80189398;
    func_8006124C(arg2, &D_80189398);
    if (arg3 != 0) {
        return func_80177240(M2C_FIELD(&D_80189390, void **, -0x6C70), 0, 0, 0);
    }
    func_80176BEC(M2C_FIELD(&D_80189390, void **, -0x6C70) + 4, 0, 0, 0, 0xE0);
    func_80176B60(M2C_FIELD(&D_80189390, M2C_UNK **, 0), &D_80176CA8);
    var_v0 = (M2C_UNK **)0x80190000;
    if (func_80176E90(M2C_FIELD(&D_80189390, void **, -0x6C70) + 4) != 0) {
        func_80066F78(1);
        var_v0_2 = (s32 *)0x80180000;
        if (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x3C) >= 0xE1) {
            func_80066424(&sp18, M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x1C), M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x1E), M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x20), (s32) M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x22));
            func_8006636C(&sp30, M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x1C), M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x1E), M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x20), (s32) M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x22));
            var_v0_2 = &D_801781E0;
        }
        if (*var_v0_2 & 1) {
            sp29 = 1;
            sp1C = (sp1C * 2) / 3;
        }
        if (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x3C) >= 0xE1) {
            func_800678E0(&sp18);
            return func_80177354();
        }
        func_800678E0(D_80083160 + 0x5C);
        var_s2 = 0;
        func_80067688(D_80083160);
loop_12:
        func_80177844(M2C_FIELD(((M2C_FIELD(M2C_FIELD(&D_80189390, M2C_UNK **, 0), s32 *, 0xC) * 4) + M2C_FIELD(&D_80189390, M2C_UNK **, 0)), s32 *, 4), (D_801781E0 & 1) | 2);
        temp_lo = M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x2C) * M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s16 *, 0x2E);
        func_801778C0(M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x10), (s32) (temp_lo + (temp_lo >> 0x1F)) >> 1);
        if (func_80176E90(M2C_FIELD(&D_80189390, void **, -0x6C70) + 4) != 0) {
            func_801770BC(M2C_FIELD(&D_80189390, void **, -0x6C70) + 4, 0);
            func_8005FE18(2);
            if (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x3C) >= 0xE1) {
                temp_s0 = (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x24) == 0) * 8;
                temp_v0 = M2C_FIELD(&D_80189390, void **, -0x6C70) + temp_s0;
                func_80066424(&sp18, M2C_FIELD(temp_v0, s16 *, 0x14), M2C_FIELD(temp_v0, s16 *, 0x16), M2C_FIELD(temp_v0, s16 *, 0x18), (s32) M2C_FIELD(temp_v0, s16 *, 0x1A));
                temp_v0_2 = M2C_FIELD(&D_80189390, void **, -0x6C70) + temp_s0;
                func_8006636C(&sp30, M2C_FIELD(temp_v0_2, s16 *, 0x14), M2C_FIELD(temp_v0_2, s16 *, 0x16), M2C_FIELD(temp_v0_2, s16 *, 0x18), (s32) M2C_FIELD(temp_v0_2, s16 *, 0x1A));
                return func_8017748C();
            }
            var_a0_2 = 0x801D0000;
            if (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x24) != 0) {
                var_a0_2 = 0x801E08D4;
            }
            D_80083160 = var_a0_2;
            if (D_801781E0 & 1) {
                sp29 = 1;
                sp1C = (sp1C * 2) / 3;
            }
            if (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x3C) >= 0xE1) {
                func_800678E0(&sp18);
                return func_80177504();
            }
            func_800678E0(D_80083160 + 0x5C);
            func_80067688(D_80083160);
            if ((D_801781D0 < (arg1 - 8)) && (var_s7 < (arg1 - 3))) {
                var_s7 += 1;
                if (M2C_FIELD(M2C_FIELD(&D_80189390, void **, -0x6C70), s32 *, 0x34) != 1) {
                    var_v0_3 = var_s6 << 0x10;
                    if (var_s4 == 0) {
                        temp_s0_2 = var_s2;
                        var_s2 = func_8003E240(1);
                        var_a0 = 0;
                        if ((D_80082E6B == 0x1E) || (D_80082E6B == 0x20) || (D_80082E6B == 1)) {
                            var_v0_4 = 0;
                            if (var_s2 != 0) {
                                return func_801775AC(0);
                            }
                            goto block_35;
                        }
                        var_v0_4 = 0;
                        if (~temp_s0_2 & var_s2 & 0x9F0) {
                            var_a0 = 1;
                            var_v0_4 = 1;
                        }
block_35:
                        if (var_v0_4 != 0) {
                            return func_80177614(var_a0);
                        }
                        if (D_801781D0 >= (arg1 - 0x14)) {
                            temp_v1 = *(s32 *)0x801B8EBC;
                            var_v0_5 = temp_v1 + 7;
                            var_s4 = 1;
                            if (var_v0_5 < 0) {
                                var_v0_5 = temp_v1 + 0xE;
                            }
                            var_s6 = (u32) var_v0_5 >> 3;
                        }
                        var_v0_3 = var_s6 << 0x10;
                        if (var_s4 != 0) {
                            goto block_43;
                        }
                        goto loop_12;
                    }
block_43:
                    temp_v1_2 = *(s32 *)0x801B8EBC - (var_v0_3 >> 0x10);
                    *(s32 *)0x801B8EBC = temp_v1_2;
                    if (temp_v1_2 < 0) {
                        *(s32 *)0x801B8EBC = 0;
                    }
                    temp_a1 = (s16) *(s32 *)0x801B8EBC;
                    func_8005A56C(0, temp_a1, temp_a1);
                    if (*(s32 *)0x801B8EBC == 0) {
                        func_8005A4E8(0, 0, 0);
                        goto block_47;
                    }
                    goto loop_12;
                }
            }
            goto block_47;
        }
block_47:
        var_v0 = &D_80189390;
        goto block_48;
    }
block_48:
    sp29 = 0;
    var_a0_3 = &sp18;
    if (M2C_FIELD(*var_v0, s32 *, 0x3C) < 0xE1) {
        var_a0_3 = D_80083160 + 0x5C;
    }
    func_800678E0(var_a0_3);
    func_80063538();
    return 0;
}
