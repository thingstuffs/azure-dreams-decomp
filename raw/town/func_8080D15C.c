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

s32 func_80052374();                             /* extern */
M2C_UNK func_80058F88();        /* extern */
s32 func_8006A3A4();                             /* extern */
s32 func_8006A470();                             /* extern */
M2C_UNK func_802441A4();                       /* extern */
M2C_UNK func_80244588();                  /* extern */
M2C_UNK func_802445FC();                     /* extern */
M2C_UNK func_80244660();                     /* extern */
M2C_UNK func_8025E01C();                     /* extern */
M2C_UNK func_80526BFC();              /* extern */
M2C_UNK func_80526D34();                      /* extern */
M2C_UNK func_80526E4C(); /* extern */
M2C_UNK func_80528998();                      /* extern */
extern s32 D_80084D5C;
extern u8 D_80095AA0[8];
extern u8 D_801328E8[0x14];
extern u8 D_80132AE8[0x18];
extern u16 D_80530658[];
extern u16 D_805306C8[];
M2C_UNK func_802483B8();                      /* extern */
M2C_UNK func_80529134();                      /* extern */
M2C_UNK func_80290318();                      /* extern */
M2C_UNK func_80528950();                      /* extern */
M2C_UNK func_80528910();                      /* extern */
M2C_UNK func_80526B18();                      /* extern */
M2C_UNK func_80243A38();                      /* extern */

void func_80527D5C(void *arg0) {
    u8 first[0x30];
    u8 second[0x28];
    M2C_UNK var_a0;
    s16 temp_v0_4;
    s16 temp_v1;
    s32 var_v0_3;
    s32 var_v0_5;
    u16 state5_v1;
    s32 state5_angle;
    u16 state5_carry;
    s32 state5_next;
    s32 temp_a0_3;
    s32 temp_ret;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    void *temp_a0;
    u16 temp_a2;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v1_3;
    u16 state0_v0;
    u16 state0_v1;
    u16 state255_flag;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_s2;
    void *second_ptr;
    u16 *state2_base;
    void *temp_s3;
    void *temp_s4;
    s32 tail_dead;
    s32 toggle_saved;
    s32 record_color;
    s32 record_offset;
    s32 record_index0;
    s32 record_index1;
    u16 state255_state;
    s32 orphan_next;
    s32 state8_origin_x;
    s32 state8_origin_y;
    s32 state8_item_addr;

    temp_a0 = M2C_FIELD(arg0, void **, 4);
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x36);
    temp_s2 = M2C_FIELD(temp_a0, void **, 8);
    temp_s3 = D_801328E8;
    temp_s4 = (u8 *) temp_a0 + 0x20;
    if (temp_v1 == 6) {
        goto block_state6;
    }
    if (temp_v1 < 7) {
        if (temp_v1 == 2) {
            goto block_state2;
        }
        if (temp_v1 < 3) {
            if (temp_v1 == 0) {
                goto block_state0;
            }
            if (temp_v1 == 1) {
                goto block_state1;
            }
            goto block_107;
        }
        if (temp_v1 == 4) {
            goto block_state4;
        }
        if (temp_v1 >= 5) {
            goto block_state5;
        }
        goto block_orphan;
    }
    if (temp_v1 == 9) {
        goto block_state9;
    }
    if (temp_v1 < 0xA) {
        if (temp_v1 == 7) {
            goto block_state7;
        }
        if (temp_v1 == 8) {
            goto block_state8;
        }
        goto block_107;
    }
    if (temp_v1 == 0xFF) {
        goto block_state255;
    }
    if (temp_v1 < 0x100) {
        if (temp_v1 == 0xA) {
            goto block_state10;
        }
        goto block_107;
    }
    if (temp_v1 != 0x100) {
        goto block_107;
    }
    goto block_state256;
block_state0:
    state0_v0 = M2C_FIELD(&D_80132AE8, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0x30) = state0_v0;
    state0_v1 = M2C_FIELD(&D_80132AE8, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 0x28) = 4U;
    M2C_FIELD(arg0, s16 *, 0x36) = 1;
    M2C_FIELD(arg0, u16 *, 0x32) = state0_v1;
    M2C_FIELD(&D_80132AE8, s32 *, 20) = 0xFFE00000;
    M2C_FIELD(&D_80132AE8, s32 *, 16) = -0x200000;
    M2C_FIELD(&D_80132AE8, s32 *, 12) = -0x200000;
    M2C_FIELD(temp_s3, s32 *, 0) = (s32) &func_802483B8;
    M2C_FIELD(&D_801328E8, s32 *, 4) = (s32) &func_80529134;
block_state1:
    M2C_FIELD(temp_s3, u16 *, 0x10) = (u16) ((M2C_FIELD(temp_s3, u16 *, 0x10) + 0x200) & 0xFFF);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x28) - 1;
    M2C_FIELD(arg0, u16 *, 0x28) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, 0x28) = 0x10U;
        M2C_FIELD(arg0, s16 *, 0x36) = 2;
        M2C_FIELD(&D_80132AE8, s32 *, 12) = (s32) ((0x420 - (s16) M2C_FIELD(arg0, u16 *, 0x30)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x28);
        M2C_FIELD(&D_80132AE8, s32 *, 16) = (s32) ((0x460 - (s16) M2C_FIELD(arg0, u16 *, 0x32)) << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x28);
        M2C_FIELD(&D_80132AE8, s32 *, 20) = 0xFFF40000;
        goto block_107;
    }
    goto block_107;
block_state2:
                state2_base = (u16 *)((s8 *)&D_80132AE8 + 2);
                M2C_FIELD(&D_801328E8, s16 *, 0x10) = ((u16) M2C_FIELD(&D_801328E8, s16 *, 0x10) + 0x200) & 0xFFF;
                if ((s16) *state2_base < 0x420) {
                    *state2_base = 0x420;
                }
                temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x28) - 1;
                M2C_FIELD(arg0, u16 *, 0x28) = temp_v0_2;
                if ((temp_v0_2 << 0x10) <= 0) {
                    M2C_FIELD(&D_80132AE8, s32 *, 16) = 0;
                    M2C_FIELD(&D_80132AE8, s32 *, 12) = 0;
                    M2C_FIELD(arg0, s16 *, 0x36) = 3;
                    goto block_107;
                }
                goto block_107;
block_orphan:
                {
                    s32 *orphan_value = (s32 *)((s8 *)&D_80132AE8 + 4);
                    s32 value = *orphan_value;

                    if (value <= 0x44FFFFF) {
                        orphan_next = ((0x4500000 - value) >> 1) + value;
                        *orphan_value = orphan_next;
                    }
                    value = *orphan_value;
                    if (value > 0x4700000) {
                        orphan_next = ((0x4700000 - value) >> 1) + value;
                        *orphan_value = orphan_next;
                    }
                    temp_s2 = orphan_value - 1;
                    M2C_FIELD(temp_s3, u16 *, 0x10) =
                        (u16) ((M2C_FIELD(temp_s3, u16 *, 0x10) + 0x200) & 0xFFF);
                    var_s0 = (s16) func_8025E01C(temp_s2);
                    if (M2C_FIELD(&D_80132AE8, s16 *, 10) < var_s0) {
                        goto block_107;
                    }
                    if (M2C_FIELD(temp_s3, s16 *, 0x10) != 0x800) {
                        goto block_107;
                    }
                    M2C_FIELD(arg0, s16 *, 0x36) = 4;
                    func_80526D34(arg0);
                    func_80244660(temp_s3, temp_s2, D_80095AA0);
                    goto block_107;
                }
block_state4:
                if (M2C_FIELD(temp_a0, s16 *, 0x88) == 7) {
                    M2C_FIELD(arg0, s16 *, 0x36) = 5;
                    goto block_107;
                }
                goto block_107;
block_state5:
                    state5_angle = M2C_FIELD(&D_801328E8, s16 *, 0x10);
                    if (state5_angle >= 0x801) {
                        M2C_FIELD(&D_801328E8, u16 *, 0x10) =
                            M2C_FIELD(&D_801328E8, u16 *, 0x10) - 0x200;
                    } else if (state5_angle < 0x800) {
                        M2C_FIELD(&D_801328E8, u16 *, 0x10) =
                            M2C_FIELD(&D_801328E8, u16 *, 0x10) + 0x200;
                    }
                    if ((func_80052374(state5_angle) == 0) && (M2C_FIELD(temp_s4, s16 *, 0x68) == 8)) {
                        M2C_FIELD(temp_s3, u16 *, 0x10) = 0x800U;
                        ((M2C_UNK (*)(void))func_80244588)();
                        func_802445FC((s32) &func_80290318);
                        M2C_FIELD(arg0, u16 *, 0x30) = (u16) M2C_FIELD(&D_80132AE8, u16 *, 2);
                        state5_v1 = (u16) M2C_FIELD(&D_80132AE8, u16 *, 6);
                        M2C_FIELD(arg0, u16 *, 0x2C) = 0U;
                        M2C_FIELD(arg0, u16 *, 0x2A) = (u16) (M2C_FIELD(arg0, u16 *, 0x2A) & 0x7FFF);
                        M2C_FIELD(arg0, s16 *, 0x36) = 6;
                        M2C_FIELD(arg0, u16 *, 0x32) = state5_v1;
                        goto block_107;
                    }
                    goto block_107;

block_state6:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x2A) & 0x8000) {
            M2C_FIELD(arg0, u16 *, 0x2C) -= 0x20;
        } else {
            M2C_FIELD(arg0, u16 *, 0x2C) += 0x20;
        }
        var_v0_5 = M2C_FIELD(arg0, s16 *, 0x2C);
        if (var_v0_5 < 0) {
            var_v0_5 = 0 - var_v0_5;
        }
        if (var_v0_5 >= 0x200) {
            tail_dead = M2C_FIELD(arg0, s16 *, 0x2A);
            toggle_saved = tail_dead;
            tail_dead &= 0x8000;
            if (tail_dead) {
                tail_dead = toggle_saved & 0x7FFF;
            } else {
                tail_dead = toggle_saved | 0x8000;
            }
            M2C_FIELD(arg0, u16 *, 0x2A) = tail_dead;
        }
        M2C_FIELD(second, s16 *, 0xC) = 0;
        M2C_FIELD(second, s16 *, 4) = 0;
        M2C_FIELD(second, u16 *, 0) = M2C_FIELD(arg0, u16 *, 0x30);
        M2C_FIELD(second, u16 *, 2) = M2C_FIELD(arg0, u16 *, 0x32);
        temp_a0_3 = func_8006A3A4((s16) M2C_FIELD(arg0, u16 *, 0x2C)) / 24;
        M2C_FIELD(second, s16 *, 8) = M2C_FIELD(arg0, u16 *, 0x30) + temp_a0_3;
        temp_ret = func_8006A470((s16) M2C_FIELD(arg0, u16 *, 0x2C));
        temp_a0_3 = temp_ret / 24;
        M2C_FIELD(second, s32 *, 0x14) = 0x202020;
        M2C_FIELD(second, s32 *, 0x10) = 0x202020;
        M2C_FIELD(second, s16 *, 0xA) = M2C_FIELD(arg0, u16 *, 0x32) - temp_a0_3;
        if (M2C_FIELD(temp_s4, s16 *, 0x68) == 9) {
            func_80244588();
            func_802445FC((s32) &func_80290318);
            func_80526E4C((s32) &func_80528950, second, second + 0x10, arg0);
            M2C_FIELD(arg0, u16 *, 0x28) = 0x200U;
            M2C_FIELD(arg0, u16 *, 0x2E) = 0U;
            M2C_FIELD(arg0, s16 *, 0x36) = 7;
            M2C_FIELD(arg0, u16 *, 0x2A) &= 0x7FFF;
            goto block_107;
        }
        func_80526E4C((s32) &func_80528910, second, second + 0x10, arg0);
        goto block_107;
block_state7:
                if ((s16) M2C_FIELD(arg0, u16 *, 0x2A) & 0x8000) {
                    M2C_FIELD(arg0, u16 *, 0x2E) -= 4;
                } else {
                    M2C_FIELD(arg0, u16 *, 0x2E) += 4;
                }
                var_v0_3 = M2C_FIELD(arg0, s16 *, 0x2E);
                if (var_v0_3 < 0) {
                    var_v0_3 = 0 - var_v0_3;
                }
                if (var_v0_3 >= 0x100) {
                    tail_dead = M2C_FIELD(arg0, s16 *, 0x2A);
                    toggle_saved = tail_dead;
                    tail_dead &= 0x8000;
                    if (tail_dead) {
                        tail_dead = toggle_saved & 0x7FFF;
                    } else {
                        tail_dead = toggle_saved | 0x8000;
                    }
                    M2C_FIELD(arg0, u16 *, 0x2A) = tail_dead;
                }
                M2C_FIELD(arg0, u16 *, 0x28) = (u16) ((M2C_FIELD(arg0, u16 *, 0x28) + M2C_FIELD(arg0, u16 *, 0x2E) + 0x1000) & 0xFFF);
                func_80528998(arg0);
                if (M2C_FIELD(temp_s4, s16 *, 0x68) == 0xA) {
                    func_802441A4();
                    record_color = 0x808080;
                    M2C_FIELD(temp_s3, s32 *, 0) = (s32) &func_80243A38;
                    record_offset = M2C_FIELD(arg0, s16 *, 0x34);
                    M2C_FIELD(first, s16 *, 0x16) = 0xB6;
                    M2C_FIELD(first, s16 *, 0x18) = 3;
                    M2C_FIELD(first, s32 *, 0x10) = record_color;
                    M2C_FIELD(first, s16 *, 0x1A) = 0x7C80;
                    M2C_FIELD(first, s16 *, 0x14) = (record_offset * 0x10) + 0x64;
                    M2C_FIELD(first, u16 *, 0x1C) &= 0xFFFE;
                    record_index0 = M2C_FIELD(arg0, s16 *, 0x34) * 2;
                    record_index0 += (s32) D_805306C8;
                    M2C_FIELD(first, s32 *, 4) = record_index0;
                    record_index1 = M2C_FIELD(arg0, s16 *, 0x34) * 2;
                    M2C_FIELD(first, s16 *, 0) = 0;
                    M2C_FIELD(first, void **, 0xC) = arg0;
                    record_index1 += (s32) D_80530658;
                    M2C_FIELD(first, s32 *, 8) = record_index1;
                    func_80526BFC((s32) &func_80526B18, first);
                    M2C_FIELD(arg0, s16 *, 0x36) = 8;
                    goto block_107;
                }
                goto block_107;
block_state8:
                    temp_s3 = D_80530658;
                    for (var_s0 = 7; var_s0 >= 0; var_s0--) {
                        state8_item_addr = (var_s0 << 2) + (s32) arg0;
                        temp_a1 = M2C_FIELD(state8_item_addr, void **, 8);
                        temp_a2 = M2C_FIELD(temp_a1, u16 *, 0x28);
                        {
                            union {
                                void *ptr;
                                s32 value;
                            } state8_a0;

                            state8_a0.ptr = M2C_FIELD(temp_a1, void **, 8);
                            if (!(temp_a2 & 3)) {
                                s32 delta0;
                                s32 delta1;
                                union {
                                    s32 x_origin;
                                    s32 y_position;
                                } state8_v1;
                                s32 state8_v0;

                                state8_v0 = M2C_FIELD(state8_a0.ptr, s16 *, 2);
                                state8_v1.x_origin = M2C_FIELD(temp_s2, s16 *, 2);
                                state8_v0 -= state8_v1.x_origin;
                                state8_v1.y_position = M2C_FIELD(state8_a0.ptr, s16 *, 6);
                                delta1 = state8_v1.y_position;
                                state8_a0.value = M2C_FIELD(temp_s2, s16 *, 6);
                                delta0 = __builtin_abs(state8_v0);
                                delta1 -= state8_a0.value;
                                if (delta1 < 0) {
                                    delta1 = -delta1;
                                }
                                if ((delta0 + delta1) < 0x20) {
                                    M2C_FIELD(temp_a1, u16 *, 0x28) = (u16) (temp_a2 | 1);
                                    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x34) * 2;
                                    temp_v1_2 += (s32) temp_s3;
                                    M2C_FIELD(temp_v1_2, u16 *, 0) = (u16) (M2C_FIELD(temp_v1_2, u16 *, 0) + 1);
                                    state8_a0.value = 0x703;
                                    if (M2C_FIELD(temp_s3, s16 *, (M2C_FIELD(arg0, s16 *, 0x34) * 2)) < 7) {
                                        state8_a0.value = 0x702;
                                    }
                                    func_80058F88(state8_a0.value, temp_a1, temp_a2);
                                }
                            }
                        }
                    }
                    if (M2C_FIELD(temp_s4, s16 *, 0x68) == 0xB) {
                        M2C_FIELD(arg0, u16 *, 0x28) = 0x1EU;
                        M2C_FIELD(arg0, s16 *, 0x36) = 9;
                        goto block_107;
                    }
                    goto block_107;

block_state9:
            temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x28) - 1;
            M2C_FIELD(arg0, u16 *, 0x28) = temp_v0_6;
            if ((temp_v0_6 << 0x10) <= 0) {
                M2C_FIELD(arg0, s16 *, 0x36) = 0xA;
                goto block_107;
            }
            goto block_107;
block_state10:
                    temp_v1_3 = M2C_FIELD(arg0, u16 *, 0x2A);
                    if (temp_v1_3 & 2) {
                        M2C_FIELD(arg0, u16 *, 0x2A) = (u16) (temp_v1_3 & 0xFFFD);
                        func_802441A4();
                        temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0x34) + 1;
                        M2C_FIELD(arg0, s16 *, 0x34) = temp_v0_4;
                        if (temp_v0_4 == 8) {
                            M2C_FIELD(arg0, u16 *, 0x28) = 0x1EU;
                            M2C_FIELD(arg0, s16 *, 0x36) = 0xFF;
                            goto block_107;
                        }
                        func_80526D34(arg0);
                        M2C_FIELD(arg0, s16 *, 0x36) = 4;
                        goto block_107;
                    }
                    goto block_107;

block_state255:
                temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x28) - 1;
                M2C_FIELD(arg0, u16 *, 0x28) = temp_v0_5;
                if ((temp_v0_5 << 0x10) <= 0) {
                    state255_state = M2C_FIELD(arg0, u16 *, 0x36);
                    state255_flag = M2C_FIELD(arg0, u16 *, 0x2A);
                    state255_state++;
                    state255_flag |= 1;
                    M2C_FIELD(arg0, u16 *, 0x2A) = state255_flag;
                    M2C_FIELD(arg0, u16 *, 0x36) = state255_state;
                    goto block_107;
                }
                goto block_107;
block_state256:
                M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
                D_80084D5C |= 0x8000;
                goto block_107;
block_107:
        if (M2C_FIELD(arg0, s16 *, 0x36) >= 4) {
            if (M2C_FIELD(&D_80132AE8, s32 *, 0) <= 0x03CFFFFF) {
                M2C_FIELD(&D_80132AE8, s32 *, 0) = 0x03D00000;
            }
            if (M2C_FIELD(&D_80132AE8, s32 *, 4) <= 0x044FFFFF) {
                M2C_FIELD(&D_80132AE8, s32 *, 4) = 0x04500000;
            }
            if (M2C_FIELD(&D_80132AE8, s32 *, 0) > 0x04700000) {
                M2C_FIELD(&D_80132AE8, s32 *, 0) = 0x04700000;
            }
            if (M2C_FIELD(&D_80132AE8, s32 *, 4) > 0x04700000) {
                M2C_FIELD(&D_80132AE8, s32 *, 4) = 0x04700000;
            }
        }
        return;
}
