#include "common.h"
#include "m2c_compat.h"

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
M2C_UNK func_80243A38();                      
typedef struct S_80527D5C_0_pre {
    u16 unk_00;
} S_80527D5C_0_pre;   /* the 0x2 bytes before arg0 in func_80527D5C, addressed as arg0[-1] */

typedef struct S_80527D5C_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x20];
    u16 unk_28;
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    union { u16 u; s16 s; } unk_2C;   /* accessed as both */
    union { u16 u; s16 s; } unk_2E;   /* accessed as both */
    u16 unk_30;
    u16 unk_32;
    s16 unk_34;
    union { s16 s; u16 u; } unk_36;   /* accessed as both */
} S_80527D5C_0;   /* arg0 in func_80527D5C */

typedef struct S_80527D5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x7C];
    s16 unk_88;
} S_80527D5C_1;   /* temp_a0 in func_80527D5C */

typedef struct S_80527D5C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80527D5C_2;   /* &D_80132AE8 in func_80527D5C */

typedef struct S_80527D5C_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
} S_80527D5C_3;   /* &D_801328E8 in func_80527D5C */

typedef struct S_80527D5C_4 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_80527D5C_4;   /* temp_s4 in func_80527D5C */

typedef struct S_80527D5C_5 {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
} S_80527D5C_5;   /* second in func_80527D5C */

typedef struct S_80527D5C_6 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s32 unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    u16 unk_1C;
} S_80527D5C_6;   /* first in func_80527D5C */

typedef struct S_80527D5C_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80527D5C_7;   /* state8_item_addr in func_80527D5C */

typedef struct S_80527D5C_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x1C];
    u16 unk_28;
} S_80527D5C_8;   /* temp_a1 in func_80527D5C */

typedef struct S_80527D5C_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80527D5C_9;   /* (void *) var_a0 in func_80527D5C */

typedef struct S_80527D5C_10 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80527D5C_10;   /* temp_s2 in func_80527D5C */

typedef struct S_80527D5C_11 {
    u16 unk_00;
} S_80527D5C_11;   /* temp_v1_2 in func_80527D5C */

/* extern */

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

    temp_a0 = ((S_80527D5C_0 *)arg0)->unk_04;
    temp_v1 = ((S_80527D5C_0 *)arg0)->unk_36.s;
    temp_s2 = ((S_80527D5C_1 *)temp_a0)->unk_08;
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
    state0_v0 = ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at02.v;
    ((S_80527D5C_0 *)arg0)->unk_30 = state0_v0;
    state0_v1 = ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at02.v;
    ((S_80527D5C_0 *)arg0)->unk_28 = 4U;
    ((S_80527D5C_0 *)arg0)->unk_36.s = 1;
    ((S_80527D5C_0 *)arg0)->unk_32 = state0_v1;
    ((S_80527D5C_2 *)(&D_80132AE8))->unk_14 = 0xFFE00000;
    ((S_80527D5C_2 *)(&D_80132AE8))->unk_10 = -0x200000;
    ((S_80527D5C_2 *)(&D_80132AE8))->unk_0C = -0x200000;
    (*(s32 *)((u8 *)temp_s3 + (0))) = (s32) &func_802483B8;
    ((S_80527D5C_3 *)(&D_801328E8))->unk_04 = (s32) &func_80529134;
block_state1:
    (*(u16 *)((u8 *)temp_s3 + (0x10))) = (u16) (((*(u16 *)((u8 *)temp_s3 + (0x10))) + 0x200) & 0xFFF);
    temp_v0 = ((S_80527D5C_0 *)arg0)->unk_28 - 1;
    ((S_80527D5C_0 *)arg0)->unk_28 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_80527D5C_0 *)arg0)->unk_28 = 0x10U;
        ((S_80527D5C_0 *)arg0)->unk_36.s = 2;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_0C = (s32) ((0x420 - (s16) ((S_80527D5C_0 *)arg0)->unk_30) << 0x10) / (s16) ((S_80527D5C_0 *)arg0)->unk_28;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_10 = (s32) ((0x460 - (s16) ((S_80527D5C_0 *)arg0)->unk_32) << 0x10) / (s16) ((S_80527D5C_0 *)arg0)->unk_28;
        ((S_80527D5C_2 *)(&D_80132AE8))->unk_14 = 0xFFF40000;
        goto block_107;
    }
    goto block_107;
block_state2:
                state2_base = (u16 *)((s8 *)&D_80132AE8 + 2);
                ((S_80527D5C_3 *)(&D_801328E8))->unk_10.s = ((u16) ((S_80527D5C_3 *)(&D_801328E8))->unk_10.s + 0x200) & 0xFFF;
                if ((s16) *state2_base < 0x420) {
                    *state2_base = 0x420;
                }
                temp_v0_2 = ((S_80527D5C_0 *)arg0)->unk_28 - 1;
                ((S_80527D5C_0 *)arg0)->unk_28 = temp_v0_2;
                if ((temp_v0_2 << 0x10) <= 0) {
                    ((S_80527D5C_2 *)(&D_80132AE8))->unk_10 = 0;
                    ((S_80527D5C_2 *)(&D_80132AE8))->unk_0C = 0;
                    ((S_80527D5C_0 *)arg0)->unk_36.s = 3;
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
                    (*(u16 *)((u8 *)temp_s3 + (0x10))) =
                        (u16) (((*(u16 *)((u8 *)temp_s3 + (0x10))) + 0x200) & 0xFFF);
                    var_s0 = (s16) func_8025E01C(temp_s2);
                    if (((S_80527D5C_2 *)(&D_80132AE8))->unk_0A < var_s0) {
                        goto block_107;
                    }
                    if ((*(s16 *)((u8 *)temp_s3 + (0x10))) != 0x800) {
                        goto block_107;
                    }
                    ((S_80527D5C_0 *)arg0)->unk_36.s = 4;
                    func_80526D34(arg0);
                    func_80244660(temp_s3, temp_s2, D_80095AA0);
                    goto block_107;
                }
block_state4:
                if (((S_80527D5C_1 *)temp_a0)->unk_88 == 7) {
                    ((S_80527D5C_0 *)arg0)->unk_36.s = 5;
                    goto block_107;
                }
                goto block_107;
block_state5:
                    state5_angle = ((S_80527D5C_3 *)(&D_801328E8))->unk_10.s;
                    if (state5_angle >= 0x801) {
                        ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u =
                            ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u - 0x200;
                    } else if (state5_angle < 0x800) {
                        ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u =
                            ((S_80527D5C_3 *)(&D_801328E8))->unk_10.u + 0x200;
                    }
                    if ((func_80052374(state5_angle) == 0) && (((S_80527D5C_4 *)temp_s4)->unk_68 == 8)) {
                        (*(u16 *)((u8 *)temp_s3 + (0x10))) = 0x800U;
                        ((M2C_UNK (*)(void))func_80244588)();
                        func_802445FC((s32) &func_80290318);
                        ((S_80527D5C_0 *)arg0)->unk_30 = (u16) ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at02.v;
                        state5_v1 = (u16) ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at02.v;
                        ((S_80527D5C_0 *)arg0)->unk_2C.u = 0U;
                        ((S_80527D5C_0 *)arg0)->unk_2A.u = (u16) (((S_80527D5C_0 *)arg0)->unk_2A.u & 0x7FFF);
                        ((S_80527D5C_0 *)arg0)->unk_36.s = 6;
                        ((S_80527D5C_0 *)arg0)->unk_32 = state5_v1;
                        goto block_107;
                    }
                    goto block_107;

block_state6:
        if ((s16) ((S_80527D5C_0 *)arg0)->unk_2A.u & 0x8000) {
            ((S_80527D5C_0 *)arg0)->unk_2C.u -= 0x20;
        } else {
            ((S_80527D5C_0 *)arg0)->unk_2C.u += 0x20;
        }
        var_v0_5 = ((S_80527D5C_0 *)arg0)->unk_2C.s;
        if (var_v0_5 < 0) {
            var_v0_5 = 0 - var_v0_5;
        }
        if (var_v0_5 >= 0x200) {
            tail_dead = ((S_80527D5C_0 *)arg0)->unk_2A.s;
            toggle_saved = tail_dead;
            tail_dead &= 0x8000;
            if (tail_dead) {
                tail_dead = toggle_saved & 0x7FFF;
            } else {
                tail_dead = toggle_saved | 0x8000;
            }
            ((S_80527D5C_0 *)arg0)->unk_2A.u = tail_dead;
        }
        ((S_80527D5C_5 *)second)->unk_0C = 0;
        ((S_80527D5C_5 *)second)->unk_04 = 0;
        ((S_80527D5C_5 *)second)->unk_00 = ((S_80527D5C_0 *)arg0)->unk_30;
        ((S_80527D5C_5 *)second)->unk_02 = ((S_80527D5C_0 *)arg0)->unk_32;
        temp_a0_3 = func_8006A3A4((s16) ((S_80527D5C_0 *)arg0)->unk_2C.u) / 24;
        ((S_80527D5C_5 *)second)->unk_08 = ((S_80527D5C_0 *)arg0)->unk_30 + temp_a0_3;
        temp_ret = func_8006A470((s16) ((S_80527D5C_0 *)arg0)->unk_2C.u);
        temp_a0_3 = temp_ret / 24;
        ((S_80527D5C_5 *)second)->unk_14 = 0x202020;
        ((S_80527D5C_5 *)second)->unk_10 = 0x202020;
        ((S_80527D5C_5 *)second)->unk_0A = ((S_80527D5C_0 *)arg0)->unk_32 - temp_a0_3;
        if (((S_80527D5C_4 *)temp_s4)->unk_68 == 9) {
            func_80244588();
            func_802445FC((s32) &func_80290318);
            func_80526E4C((s32) &func_80528950, second, second + 0x10, arg0);
            ((S_80527D5C_0 *)arg0)->unk_28 = 0x200U;
            ((S_80527D5C_0 *)arg0)->unk_2E.u = 0U;
            ((S_80527D5C_0 *)arg0)->unk_36.s = 7;
            ((S_80527D5C_0 *)arg0)->unk_2A.u &= 0x7FFF;
            goto block_107;
        }
        func_80526E4C((s32) &func_80528910, second, second + 0x10, arg0);
        goto block_107;
block_state7:
                if ((s16) ((S_80527D5C_0 *)arg0)->unk_2A.u & 0x8000) {
                    ((S_80527D5C_0 *)arg0)->unk_2E.u -= 4;
                } else {
                    ((S_80527D5C_0 *)arg0)->unk_2E.u += 4;
                }
                var_v0_3 = ((S_80527D5C_0 *)arg0)->unk_2E.s;
                if (var_v0_3 < 0) {
                    var_v0_3 = 0 - var_v0_3;
                }
                if (var_v0_3 >= 0x100) {
                    tail_dead = ((S_80527D5C_0 *)arg0)->unk_2A.s;
                    toggle_saved = tail_dead;
                    tail_dead &= 0x8000;
                    if (tail_dead) {
                        tail_dead = toggle_saved & 0x7FFF;
                    } else {
                        tail_dead = toggle_saved | 0x8000;
                    }
                    ((S_80527D5C_0 *)arg0)->unk_2A.u = tail_dead;
                }
                ((S_80527D5C_0 *)arg0)->unk_28 = (u16) ((((S_80527D5C_0 *)arg0)->unk_28 + ((S_80527D5C_0 *)arg0)->unk_2E.u + 0x1000) & 0xFFF);
                func_80528998(arg0);
                if (((S_80527D5C_4 *)temp_s4)->unk_68 == 0xA) {
                    func_802441A4();
                    record_color = 0x808080;
                    (*(s32 *)((u8 *)temp_s3 + (0))) = (s32) &func_80243A38;
                    record_offset = ((S_80527D5C_0 *)arg0)->unk_34;
                    ((S_80527D5C_6 *)first)->unk_16 = 0xB6;
                    ((S_80527D5C_6 *)first)->unk_18 = 3;
                    ((S_80527D5C_6 *)first)->unk_10 = record_color;
                    ((S_80527D5C_6 *)first)->unk_1A = 0x7C80;
                    ((S_80527D5C_6 *)first)->unk_14 = (record_offset * 0x10) + 0x64;
                    ((S_80527D5C_6 *)first)->unk_1C &= 0xFFFE;
                    record_index0 = ((S_80527D5C_0 *)arg0)->unk_34 * 2;
                    record_index0 += (s32) D_805306C8;
                    ((S_80527D5C_6 *)first)->unk_04 = record_index0;
                    record_index1 = ((S_80527D5C_0 *)arg0)->unk_34 * 2;
                    ((S_80527D5C_6 *)first)->unk_00 = 0;
                    ((S_80527D5C_6 *)first)->unk_0C = arg0;
                    record_index1 += (s32) D_80530658;
                    ((S_80527D5C_6 *)first)->unk_08 = record_index1;
                    func_80526BFC((s32) &func_80526B18, first);
                    ((S_80527D5C_0 *)arg0)->unk_36.s = 8;
                    goto block_107;
                }
                goto block_107;
block_state8:
                    temp_s3 = D_80530658;
                    for (var_s0 = 7; var_s0 >= 0; var_s0--) {
                        state8_item_addr = (var_s0 << 2) + (s32) arg0;
                        temp_a1 = ((S_80527D5C_7 *)state8_item_addr)->unk_08;
                        temp_a2 = ((S_80527D5C_8 *)temp_a1)->unk_28;
                        {
                            var_a0 = (s32) ((S_80527D5C_8 *)temp_a1)->unk_08;
                            if (!(temp_a2 & 3)) {
                                s32 delta0;
                                s32 state8_v0;

                                state8_v0 = ((S_80527D5C_9 *)((void *) var_a0))->unk_02;
                                var_v1 = ((S_80527D5C_10 *)temp_s2)->unk_02;
                                state8_v0 -= var_v1;
                                var_v1 = ((S_80527D5C_9 *)((void *) var_a0))->unk_06;
                                var_a0 = ((S_80527D5C_10 *)temp_s2)->unk_06;
                                delta0 = __builtin_abs(state8_v0);
                                var_v1 -= var_a0;
                                if (var_v1 < 0) {
                                    var_v1 = -var_v1;
                                }
                                if ((delta0 + var_v1) < 0x20) {
                                    ((S_80527D5C_8 *)temp_a1)->unk_28 = (u16) (temp_a2 | 1);
                                    temp_v1_2 = ((S_80527D5C_0 *)arg0)->unk_34 * 2;
                                    temp_v1_2 += (s32) temp_s3;
                                    ((S_80527D5C_11 *)temp_v1_2)->unk_00 = (u16) (((S_80527D5C_11 *)temp_v1_2)->unk_00 + 1);
                                    var_a0 = 0x703;
                                    if ((*(s16 *)((u8 *)temp_s3 + ((((S_80527D5C_0 *)arg0)->unk_34 * 2)))) < 7) {
                                        var_a0 = 0x702;
                                    }
                                    func_80058F88(var_a0, temp_a1, temp_a2);
                                }
                            }
                        }
                    }
                    if (((S_80527D5C_4 *)temp_s4)->unk_68 == 0xB) {
                        ((S_80527D5C_0 *)arg0)->unk_28 = 0x1EU;
                        ((S_80527D5C_0 *)arg0)->unk_36.s = 9;
                        goto block_107;
                    }
                    goto block_107;

block_state9:
            temp_v0_6 = ((S_80527D5C_0 *)arg0)->unk_28 - 1;
            ((S_80527D5C_0 *)arg0)->unk_28 = temp_v0_6;
            if ((temp_v0_6 << 0x10) <= 0) {
                ((S_80527D5C_0 *)arg0)->unk_36.s = 0xA;
                goto block_107;
            }
            goto block_107;
block_state10:
                    temp_v1_3 = ((S_80527D5C_0 *)arg0)->unk_2A.u;
                    if (temp_v1_3 & 2) {
                        ((S_80527D5C_0 *)arg0)->unk_2A.u = (u16) (temp_v1_3 & 0xFFFD);
                        func_802441A4();
                        temp_v0_4 = (u16) ((S_80527D5C_0 *)arg0)->unk_34 + 1;
                        ((S_80527D5C_0 *)arg0)->unk_34 = temp_v0_4;
                        if (temp_v0_4 == 8) {
                            ((S_80527D5C_0 *)arg0)->unk_28 = 0x1EU;
                            ((S_80527D5C_0 *)arg0)->unk_36.s = 0xFF;
                            goto block_107;
                        }
                        func_80526D34(arg0);
                        ((S_80527D5C_0 *)arg0)->unk_36.s = 4;
                        goto block_107;
                    }
                    goto block_107;

block_state255:
                temp_v0_5 = ((S_80527D5C_0 *)arg0)->unk_28 - 1;
                ((S_80527D5C_0 *)arg0)->unk_28 = temp_v0_5;
                if ((temp_v0_5 << 0x10) <= 0) {
                    state255_state = ((S_80527D5C_0 *)arg0)->unk_36.u;
                    state255_flag = ((S_80527D5C_0 *)arg0)->unk_2A.u;
                    state255_state++;
                    state255_flag |= 1;
                    ((S_80527D5C_0 *)arg0)->unk_2A.u = state255_flag;
                    ((S_80527D5C_0 *)arg0)->unk_36.u = state255_state;
                    goto block_107;
                }
                goto block_107;
block_state256:
                (*(u16 *)((u8 *)arg0 + (-2))) = (u16) (((S_80527D5C_0_pre *)arg0)[-1].unk_00 | 0x8000);
                D_80084D5C |= 0x8000;
                goto block_107;
block_107:
        if (((S_80527D5C_0 *)arg0)->unk_36.s >= 4) {
            if (((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v <= 0x03CFFFFF) {
                ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v = 0x03D00000;
            }
            if ((*(s32 *)((u8 *)(&D_80132AE8) + (4))) <= 0x044FFFFF) {
                ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at00.v = 0x04500000;
            }
            if (((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v > 0x04700000) {
                ((S_80527D5C_2 *)(&D_80132AE8))->unk_00.at00.v = 0x04700000;
            }
            if ((*(s32 *)((u8 *)(&D_80132AE8) + (4))) > 0x04700000) {
                ((S_80527D5C_2 *)(&D_80132AE8))->unk_04.at00.v = 0x04700000;
            }
        }
        return;
}
