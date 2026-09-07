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

M2C_UNK func_800211C4();      /* extern */
M2C_UNK func_80022F34();              /* extern */
M2C_UNK func_800239A0();            /* extern */
M2C_UNK func_80047784();         /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();              /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800ABD74();                 /* extern */
s16 func_800C2AE8();                      /* extern */
typedef struct {
    void *ptr;
    s16 field4;
    u16 flags;
    s16 field8;
    s16 padA;
} Record12;

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} Stack24;

extern Record12 D_800242D8[];
extern s32 D_80081458[];
extern s16 D_80083228;
extern u8 D_800D2388[];

void func_80023260(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_s0_2;
    s32 temp_v1;
    s16 temp_v1_4;
    s16 temp_v1_5;
    s16 temp_v1_6;
    register s32 temp_v1_7 ASM_REG("$3");
    register s32 temp_v1_8 ASM_REG("$3");
    s32 var_a2;
    s32 var_v0_4;
    s32 temp_a0_6;
    s32 temp_a1_2;
    register s32 temp_a1_3 ASM_REG("$5");
    s32 temp_fp;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_9;
    s32 constant2;
    register s32 old_c ASM_REG("$2");
    register s32 old_10 ASM_REG("$3");
    register s32 angle_obj ASM_REG("$3");
    register s32 angle_base ASM_REG("$2");
    register s32 final_kind ASM_REG("$2");
    s32 case_value;
    register s32 var_a1 ASM_REG("$5");
    s32 var_a3;
    register s32 var_s0 ASM_REG("$16");
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_a0;
    u16 temp_a1;
    register s32 temp_v1_3 ASM_REG("$3");
    register s32 var_v0_3 ASM_REG("$2");
    Record12 *record_base;
    void *temp_s0;
    void *temp_s2;
    void *temp_s5;
    u8 *case_base;

    temp_s5 = arg0;
    record_base = D_800242D8;
    temp_fp = M2C_FIELD(arg0, s32 *, 0);
    temp_s2 = record_base[M2C_FIELD(arg0, s16 *, 0x22)].ptr + (M2C_FIELD(arg0, s16 *, 0x1C) * 8);
    func_800478B8(arg2);
    temp_s0 = arg0 + 0x14;
    func_80022F34(arg1, temp_s0);
    func_800239A0(temp_fp, temp_s0, M2C_FIELD(arg0, s16 *, 0x24));
    func_8009539C(arg1);
    var_s0 = 0;
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x10));
    old_c = M2C_FIELD(arg0, volatile s32 *, 0xC);
    old_10 = M2C_FIELD(arg0, volatile s32 *, 0x10);
    temp_a0 = M2C_FIELD(arg0, volatile u16 *, 0x18);
    M2C_FIELD(arg0, s32 *, 0x10) = old_10 >> 1;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x18);
    M2C_FIELD(arg0, s32 *, 0xC) = old_c >> 1;
    constant2 = 2;
    if (temp_v1 == constant2) {
        goto block_69;
    }
    if (temp_v1 >= 3) {
        goto check_high;
    }
    if (temp_v1 == 0) {
        goto kind_0;
    }
    if (temp_v1 == 1) {
        goto kind_1;
    }
    goto block_69;
check_high:
    if (temp_v1 == 0x100) {
        goto kind_100;
    }
    if (temp_v1 > 0x100) {
        goto block_69;
    }
    if (temp_v1 == 3) {
        goto kind_3;
    }
    goto block_69;
kind_0:
    M2C_FIELD(arg0, u16 *, 0x18) = temp_a0 + 1;
    return;
kind_1:
    M2C_FIELD(arg0, s16 *, 0x2A) = 0x800;
    case_value = D_80081458[0];
    case_base = D_800D2388;
    M2C_FIELD(arg2, u8 **, 0x2C) = case_base;
    M2C_FIELD(arg2, s32 *, 0x28) = case_value;
    func_80047784(arg2, D_800D2388[((D_80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + 1);
    goto block_69;
kind_3:
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800D2388 - 8;
    func_80047784(arg2, (D_800D2388 - 8)[((D_80083228 + M2C_FIELD(arg0, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x18) = constant2;
    goto block_69;
kind_100:
            temp_a1 = M2C_FIELD(arg0, u16 *, 0x1A) + 1;
            M2C_FIELD(arg0, u16 *, 0x1A) = temp_a1;
            if ((M2C_FIELD(arg0, s32 *, 4) <= 0x200000) && (M2C_FIELD(temp_s2, u16 *, 6) & 2)) {
                if (((s16) temp_a1 % (s16) record_base[M2C_FIELD(arg0, s16 *, 0x22)].flags) == 0) {
                    func_800ABD74(arg1);
                    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 0x80000);
                }
            }
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 4);
            if ((temp_v1_2 <= 0xFFFFF) && (M2C_FIELD(temp_s2, u16 *, 6) & 1)) {
                M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_v1_2 + 0x20000);
            }
            angle_obj = M2C_FIELD(temp_s5, s16 *, 0x2A);
            angle_base = M2C_FIELD(temp_s2, s16 *, 4);
            var_a1 = angle_obj - angle_base;
            var_a3 = 0;
            while (var_a1 >= 0x801) {
                var_a1 -= 0x1000;
            }
            while (var_a1 < -0x800) {
                var_a1 += 0x1000;
            }
            temp_a1_2 = var_a1;
            temp_v1_3 = M2C_FIELD(temp_s2, u16 *, 6);
            temp_v0 = temp_v1_3 & 8;
            if (temp_v0 != 0) {
                temp_v0 = temp_v1_3 & 0x10;
                if (temp_v0 != 0) {
                    temp_a0_2 = M2C_FIELD(temp_s2, s16 *, 0);
                    var_a2 = D_800242D8[M2C_FIELD(arg0, s16 *, 0x22)].field8;
                    if (M2C_FIELD(arg1, s16 *, 2) >= temp_a0_2) {
                        var_s0 = 1;
                    }
                    goto block_38;
                }
                var_a2 = 0 - D_800242D8[M2C_FIELD(arg0, s16 *, 0x22)].field8;
                if (M2C_FIELD(arg1, s16 *, 2) <= M2C_FIELD(temp_s2, s16 *, 0)) {
                    var_s0 = 1;
                }
block_38:
                temp_a0_3 = M2C_FIELD(temp_s2, s16 *, 2);
                temp_v1_4 = M2C_FIELD(arg1, s16 *, 6);
                var_v0 = temp_a0_3 - temp_v1_4;
                if (var_v0 < 0) {
                    var_v0 = 0 - var_v0;
                }
                if (var_v0 >= 5) {
                    var_a3 = 0x20;
                    if (temp_v1_4 >= temp_a0_3) {
                        if ((0 - var_a2) < temp_a1_2) {
                            var_a3 = -0x20;
                        }
                        goto block_58;
                    }
                    goto block_56;
                }
                goto block_58;
            }
            temp_v0 = temp_v1_3 & 0x10;
            if (temp_v0 != 0) {
                temp_a0_4 = M2C_FIELD(temp_s2, s16 *, 2);
                var_a2 = D_800242D8[M2C_FIELD(arg0, s16 *, 0x22)].field8;
                if (M2C_FIELD(arg1, s16 *, 6) >= temp_a0_4) {
                    var_s0 = 1;
                }
                goto block_50;
            }
            var_a2 = 0 - D_800242D8[M2C_FIELD(arg0, s16 *, 0x22)].field8;
            if (M2C_FIELD(arg1, s16 *, 6) <= M2C_FIELD(temp_s2, s16 *, 2)) {
                var_s0 = 1;
            }
block_50:
            temp_a0_5 = M2C_FIELD(temp_s2, s16 *, 0);
            temp_v1_5 = M2C_FIELD(arg1, s16 *, 2);
            var_v0_2 = temp_a0_5 - temp_v1_5;
            if (var_v0_2 < 0) {
                var_v0_2 = 0 - var_v0_2;
            }
            if (var_v0_2 >= 5) {
                var_a3 = 0x20;
                if (temp_v1_5 < temp_a0_5) {
                    if ((0 - var_a2) < temp_a1_2) {
                        var_a3 = -0x20;
                    }
                    goto block_58;
                }
block_56:
                if (var_a2 < temp_a1_2) {
                    var_a3 = -0x20;
                }
                goto block_58;
            }
block_58:
            if ((M2C_FIELD(temp_s2, u16 *, 6) & 4) && (var_s0 != 0)) {
                M2C_FIELD(arg1, s32 *, 0x14) = -0x140000;
            }
            temp_a0_6 = var_a3 >> 4;
            M2C_FIELD(temp_s5, s16 *, 0x2A) = (s16) ((u16) M2C_FIELD(temp_s5, s16 *, 0x2A) + var_a3);
            M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) + temp_a0_6);
            M2C_FIELD(arg0, s16 *, 0x1C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1C) + var_s0);
            if ((var_s0 != 0) && (M2C_FIELD(temp_s2, u16 *, 6) & 0x20)) {
                if (rand(temp_a0_6, temp_a1_2, var_a2, var_a3) & 1) {
                    M2C_FIELD(temp_s2, u16 *, 0xE) = (u16) (M2C_FIELD(temp_s2, u16 *, 0xE) | 2);
                    goto block_67;
                }
                M2C_FIELD(temp_s2, u16 *, 0xE) = (u16) (M2C_FIELD(temp_s2, u16 *, 0xE) & 0xFFFD);
                goto block_67;
            }
block_67:
            if (M2C_FIELD(arg0, s16 *, 0x1C) >= 0xF) {
                M2C_FIELD(arg0, u16 *, 0x1A) = 0U;
                M2C_FIELD(arg0, s16 *, 0x1C) = 0;
            }
            goto block_69;
block_69:
        temp_v1_6 = (s16) M2C_FIELD(arg0, u16 *, 0x1E);
        if (temp_v1_6 > 0) {
            M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) - 1);
        } else if (temp_v1_6 < 0) {
            M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) + 1);
        }
        temp_v1_7 = (s16) M2C_FIELD(arg0, u16 *, 0x1E);
        if (temp_v1_7 < -9) {
            var_v0_3 = -9;
            goto clamp_store;
        }
        var_v0_3 = temp_v1_7 < 0xA;
        if (var_v0_3 != 0) {
            goto clamp_done;
        }
        var_v0_3 = 9;
clamp_store:
        M2C_FIELD(arg0, u16 *, 0x1E) = var_v0_3;
clamp_done:
        var_v0_4 = (s16) M2C_FIELD(arg0, u16 *, 0x1E);
        if (var_v0_4 < 0) {
            var_v0_4 = 0 - var_v0_4;
        }
        if ((var_v0_4 >= 6) && (((u16) M2C_FIELD(arg0, u16 *, 0x1A) >> 1) & 1)) {
            func_800ABD74(arg1);
        }
        {
        Stack24 sp = *(Stack24 *)arg1;
        temp_v1_8 = M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x24) * 2) + temp_fp), s16 *, 0x3C);
        if ((temp_v1_8 == 2) || (temp_v1_8 == 6)) {
            sp.field8 = 0xFE000000;
        }
        temp_s0_2 = func_800C2AE8(&sp);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584(M2C_FIELD(temp_s5, s16 *, 0x2A)) * ((s32) M2C_FIELD(arg0, s32 *, 4) >> 0xC));
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8(M2C_FIELD(temp_s5, s16 *, 0x2A)) * ((s32) M2C_FIELD(arg0, s32 *, 4) >> 0xC));
        if (temp_s0_2 < M2C_FIELD(arg1, s16 *, 0xA)) {
            M2C_FIELD(arg1, s16 *, 0xA) = temp_s0_2;
            if (M2C_FIELD(arg1, s32 *, 0x14) >= 0) {
                M2C_FIELD(arg1, s32 *, 0x14) = 0;
            }
            if (M2C_FIELD(arg0, s32 *, 8) & 1) {
                func_800ABD74(arg1);
            }
            M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & -2);
        } else {
            M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) | 1);
        }
        temp_v1_9 = M2C_FIELD(arg0, s32 *, 4);
        if (temp_v1_9 < -0x10000) {
            M2C_FIELD(arg0, s32 *, 4) = temp_v1_9 + 0x10000;
        } else if (temp_v1_9 > 0x10000) {
            M2C_FIELD(arg0, s32 *, 4) = temp_v1_9 - 0x10000;
        } else {
            M2C_FIELD(arg0, s32 *, 4) = 0;
        }
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x20000);
        final_kind = M2C_FIELD(arg0, s16 *, 0x18);
        ASM_KEEP_NV(final_kind);
        if (final_kind != 0) {
            func_800211C4(temp_s5, arg0, arg2);
        }
        }
}
