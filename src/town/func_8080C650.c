/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
extern int abs(int);

typedef struct S_8080C650_0_pre {
    u16 unk_00;
} S_8080C650_0_pre;   /* the 0x2 bytes before arg0 in func_8080C650, addressed as arg0[-1] */

typedef struct S_8080C650_0 {
    u8 pad_00[0x15];
    s8 unk_15;
    u8 pad_16[0x52];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    u16 unk_6C;
    u8 pad_6E[0x3A];
    s32 unk_A8;
    void * unk_AC;
} S_8080C650_0;   /* arg0 in func_8080C650 */

typedef struct S_8080C650_1 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xA];
    u16 unk_2A;
    s16 unk_2C;
    u16 unk_2E;
    u8 pad_30[0x4];
    s16 unk_34;
    s16 unk_36;
} S_8080C650_1;   /* var_s0 in func_8080C650 */

typedef struct S_8080C650_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8080C650_2;   /* arg1 in func_8080C650 */

typedef struct S_8080C650_3 {
    u8 pad_00[0xC];
    union { s32 s32; u8 u8; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8080C650_3;   /* arg2 in func_8080C650 */

typedef struct S_8080C650_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
    void * unk_24;
} S_8080C650_4;   /* temp_v0_3 in func_8080C650 */


s32 func_80034A1C();                /* extern */
void *func_800374FC();            /* extern */
M2C_UNK func_8003BC18();           /* extern */
M2C_UNK func_8003EA54();                      /* extern */
M2C_UNK func_80050BD8();                     /* extern */
M2C_UNK func_80050BFC();                     /* extern */
M2C_UNK func_80058F88();                     /* extern */
s32 func_8006A3A4();                             /* extern */
s32 func_8006A470();                             /* extern */
M2C_UNK func_8023FB18();                      /* extern */
M2C_UNK func_80245C10();             /* extern */
s16 func_8025E01C();                          /* extern */
extern s16 D_800133A0[5];
extern s16 D_800133A0_store[5] __asm__("D_800133A0");
extern u8 D_8003C558[3];
extern s32 D_80084D5C;
extern M2C_UNK D_8012F130[5];
extern u8 D_801328C8[3];
extern s32 D_801328E8[3];
extern s32 D_80132AE8[3];
extern s32 D_80132AEC[3];
extern s32 D_80132AF0[3];
extern s16 D_80132AF2[5];
extern u8 D_802430A8[12];
extern u8 D_80243200[12];
extern u8 D_802434B0[12];
extern u8 D_802892EC[12];
extern u8 D_80289334[12];
extern u8 D_8028937C[12];
extern u8 D_802893C4[12];
extern u8 D_8028940C[12];
extern u8 D_802894AC[12];
extern u8 D_80289454[12];
extern u8 D_8028950C[12];
extern u8 D_8028954C[12];
extern s32 D_8029070C[3];
extern u8 D_80529080[12];
extern s16 D_80530658[];
void func_8080C650(void *in0, void *arg1, void *in2) {
    s16 *var_v1;
    s16 raw_s1;
    s32 temp_v0_4;
    s16 temp_v1;
    s32 var_a0;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_v0_6;
    s32 temp_v0_6_2;
    s32 temp_v1_4;
    s32 delta;
    s32 loop_index;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_v0_2;
    s32 tmpx;
    s32 state4_v0;
    s32 state4_a1;
    s32 high_v0;
    register s32 abs_v1;
    s32 state6_v0;
    s32 state6_v1;
    s32 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_7;
    u16 temp_state108;
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0_3;
    void *var_s0;
    void *var_s0_2;
    void *arg2 = in2;
    s32 *global_s7;
    s32 *global_s5;

    var_s2 = 0;
    var_s0 = NULL;
    raw_s1 = func_8025E01C(arg1);
    global_s7 = D_8012F130;
    global_s5 = D_801328E8;
    temp_v0_3 = (void *)raw_s1;
    if (((S_8080C650_0 *)in0)->unk_68.s < 0xFF) {
        var_s0 = ((S_8080C650_0 *)in0)->unk_AC;
        if (((S_8080C650_1 *)var_s0)->unk_36 == 0xFF) {
            ((S_8080C650_0 *)in0)->unk_68.s = 0xFF;
        }
        func_80245C10(arg1);
    } else {
        func_80245C10(arg1);
    }
    if (((S_8080C650_2 *)arg1)->unk_08.at02.v >= ((s32)temp_v0_3)) {
        ((S_8080C650_2 *)arg1)->unk_08.at02.v = (s32)temp_v0_3;
        func_8003EA54(arg2);
    } else {
        func_8003EA54(arg2);
    }
    temp_v1 = ((S_8080C650_0 *)in0)->unk_68.s;
    switch (temp_v1) {
    case 0:
        ((S_8080C650_2 *)arg1)->unk_00 = 0x03A00000;
        ((S_8080C650_2 *)arg1)->unk_04 = 0x01E00000;
        ((S_8080C650_2 *)arg1)->unk_08.at02.v = func_8025E01C(arg1);
        ((S_8080C650_0 *)in0)->unk_6C = 0x40U;
        ((S_8080C650_0 *)in0)->unk_15 = 0;
        ((S_8080C650_0 *)in0)->unk_68.s = 1;
    case 1:
        if (((S_8080C650_3 *)arg2)->unk_14 & 0x6000) {
            ((S_8080C650_2 *)arg1)->unk_10 = 0x80000;
            var_s2 = (s32)D_802892EC;
        }
        if (((S_8080C650_0 *)in0)->unk_A8 & 1) {
            temp_v0 = ((S_8080C650_0 *)in0)->unk_6C - 1;
            ((S_8080C650_0 *)in0)->unk_6C = temp_v0;
            if ((s16) temp_v0 >= 0) {
                ((S_8080C650_2 *)arg1)->unk_00 = (s32) ((func_8006A3A4((s16) temp_v0 << 7) << 7) + 0x03A00000);
            }
        }
        if (((S_8080C650_2 *)arg1)->unk_04 > 0x0477FFFF) {
            ((S_8080C650_3 *)arg2)->unk_14 = (u16) (((S_8080C650_3 *)arg2)->unk_14 | 1);
            ((S_8080C650_2 *)arg1)->unk_0C = 0x80000;
            var_s2 = (s32)D_80289334;
            ((S_8080C650_0 *)in0)->unk_68.s = 2;
        }
        if (var_s2 != 0) {
            func_80034A1C(arg2, var_s2, 0);
        }
        return;
    case 2:
        if (((S_8080C650_3 *)arg2)->unk_14 & 0x6000) {
            var_s2 = (s32)D_802893C4;
        }
        if (((S_8080C650_2 *)arg1)->unk_04 > 0x048FFFFF) {
            tmpx = 3;
            var_s2 = (s32)D_8028937C;
            ((S_8080C650_2 *)arg1)->unk_10 = 0;
            ((S_8080C650_0 *)in0)->unk_68.s = tmpx;
        }
        break;
    case 3:
        if (((S_8080C650_3 *)arg2)->unk_14 & 0x6000) {
            var_s2 = (s32)D_802893C4;
        }
        if (((S_8080C650_2 *)arg1)->unk_00 > 0x03DFFFFF) {
            ((S_8080C650_2 *)arg1)->unk_14 = -0x100000;
            var_s2 = (s32)D_80289454;
            ((S_8080C650_0 *)in0)->unk_68.s = 4;
        }
        break;
    case 4:
        temp_a0 = ((S_8080C650_2 *)arg1)->unk_00;
        state4_a1 = 0x48000;
        state4_v0 = ((S_8080C650_2 *)arg1)->unk_14 + state4_a1;
        ((S_8080C650_2 *)arg1)->unk_14 = state4_v0;
        if (temp_a0 > 0x041FFFFF) {
            ((S_8080C650_2 *)arg1)->unk_14 = 0;
            ((S_8080C650_2 *)arg1)->unk_0C = 0;
            ((S_8080C650_0 *)in0)->unk_15 = 1;
            ((S_8080C650_0 *)in0)->unk_68.s = 5;
        }
        break;
    case 5:
        if (global_s5[0] == (s32)D_802430A8) {
            ((S_8080C650_0 *)in0)->unk_6C = 7U;
            global_s5[0] = (s32)D_80243200;
            ((S_8080C650_0 *)in0)->unk_15 = 0;
            ((S_8080C650_0 *)in0)->unk_68.s = 6;
        }
        break;
    case 6:
        ((S_8080C650_2 *)arg1)->unk_0C = (s32) ((s32) (D_80132AE8[0] - ((S_8080C650_2 *)arg1)->unk_00) >> 1);
        ((S_8080C650_2 *)arg1)->unk_10 = (s32) ((s32) (D_80132AEC[0] - ((S_8080C650_2 *)arg1)->unk_04) >> 1);
        state6_v0 = D_80132AF0[0] + D_8029070C[0];
        state6_v1 = ((S_8080C650_2 *)arg1)->unk_08.at00.v + 0x80000;
        state6_v0 -= state6_v1;
        ((S_8080C650_2 *)arg1)->unk_14 = state6_v0 >> 1;
        func_80245C10(arg1);
        global_s5[0] = (s32)D_80243200;
        temp_v0_2 = ((S_8080C650_0 *)in0)->unk_6C - 1;
        ((S_8080C650_0 *)in0)->unk_6C = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            global_s5[0] = (s32)D_80243200;
            ((S_8080C650_2 *)arg1)->unk_14 = 0;
            ((S_8080C650_2 *)arg1)->unk_10 = 0;
            ((S_8080C650_2 *)arg1)->unk_0C = 0;
            ((S_8080C650_0 *)in0)->unk_68.s = 7;
        }
        break;
    case 7:
    case 8:
    case 9:
        ((S_8080C650_2 *)arg1)->unk_00 = (s32) D_80132AE8[0];
        ((S_8080C650_2 *)arg1)->unk_04 = (s32) D_80132AEC[0];
        ((S_8080C650_2 *)arg1)->unk_08.at00.v = (s32) (D_80132AF0[0] + D_8029070C[0] + 0xFFF80000);
        global_s7 += 4;
        if (*global_s7 & 0x20) {
            if (D_80132AF2[0] == 0) {
                if (((S_8080C650_0 *)in0)->unk_68.s == 9) {
                    tmpx = 0x100000;
                    var_s2 = (s32)D_8028950C;
                    ((S_8080C650_1 *)var_s0)->unk_00 = tmpx;
                } else {
                    global_s5[0] = (s32)D_802434B0;
                    ((S_8080C650_2 *)arg1)->unk_14 = 0x100000;
                }
            } else {
                global_s5[0] = (s32)D_80243200;
            }
            if (((S_8080C650_0 *)in0)->unk_68.s == 9) {
                func_80058F88(0x700);
            }
            ((S_8080C650_1 *)var_s0)->unk_2A = (u16)(((S_8080C650_1 *)var_s0)->unk_2A & ~4);
            temp_state108 = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (temp_state108 + 1);
        }
        break;
    case 10:
        temp_lo = (s32) (((s32) ((S_8080C650_1 *)var_s0)->unk_00
            >> 0xC) * func_8006A3A4(((S_8080C650_1 *)var_s0)->unk_2C));
        ((S_8080C650_2 *)arg1)->unk_0C = temp_lo;
        temp_lo = ((s32) (0 - ((S_8080C650_1 *)var_s0)->unk_00)
            >> 0xC) * func_8006A470(((S_8080C650_1 *)var_s0)->unk_2C);
        ((S_8080C650_2 *)arg1)->unk_10 = temp_lo;
        if (temp_lo > -0x40000) {
            ((S_8080C650_2 *)arg1)->unk_10 = -0x40000;
        }
        ((S_8080C650_1 *)var_s0)->unk_2C = (s16) ((u16) ((S_8080C650_1 *)var_s0)->unk_2C
            - ((s32) (((S_8080C650_1 *)var_s0)->unk_2E << 0x10) >> 0x14));
        if (((S_8080C650_2 *)arg1)->unk_08.at00.v > 0) {
            temp_v1_2 = ((S_8080C650_1 *)var_s0)->unk_2A;
            if (!(temp_v1_2 & 4)) {
                ((S_8080C650_1 *)var_s0)->unk_2A = (u16) (temp_v1_2 | 4);
                func_80058F88(0x701);
            }
            temp_a0_2 = ((S_8080C650_2 *)arg1)->unk_00;
            ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0x200000;
            if (temp_a0_2 <= 0x041FFFFF) {
                if (temp_a0_2 > 0x03BFFFFF) {
                    var_v0_2 = 0x03B80000;
                    ((S_8080C650_2 *)arg1)->unk_00 = var_v0_2;
                } else if (temp_a0_2 <= 0x03800000) {
                    ((S_8080C650_2 *)arg1)->unk_00 = 0x03880000;
                }
            } else if (temp_a0_2 > 0x04BFFFFF) {
                var_v0_2 = 0x04B80000;
                ((S_8080C650_2 *)arg1)->unk_00 = var_v0_2;
            } else if (temp_a0_2 <= 0x04800000) {
                var_v0_2 = 0x04880000;
                ((S_8080C650_2 *)arg1)->unk_00 = var_v0_2;
            }
            ((S_8080C650_1 *)var_s0)->unk_2C = (s16) ((s32) (0 - ((S_8080C650_1 *)var_s0)->unk_2C) >> 1);
        }
        if (((S_8080C650_2 *)arg1)->unk_04 <= 0x01E00000) {
            func_80058F88(0x1700);
            func_80058F88(0x1701);
            if (D_80530658[((S_8080C650_1 *)var_s0)->unk_34] == 8) {
                loop_index = 1;
                global_s5 = (s32 *)0x1000;
                ((S_8080C650_0 *)in0)->unk_A8 = (s32) (((S_8080C650_0 *)in0)->unk_A8 | 1);
                {
                    do {
                        temp_v0_3 = func_800374FC(0x136, D_801328C8);
                        if (temp_v0_3 != NULL) {
                            var_s0_2 = ((S_8080C650_4 *)temp_v0_3)->unk_0C;
                            func_8003BC18(temp_v0_3, D_8003C558);
                            ((S_8080C650_1 *)var_s0_2)->unk_0C = 0x808080;
                            ((S_8080C650_1 *)var_s0_2)->unk_1E = (s16)(s32)global_s5;
                            ((S_8080C650_1 *)var_s0_2)->unk_1C = (s16)(s32)global_s5;
                            ((S_8080C650_4 *)temp_v0_3)->unk_22 = 0x78;
                            ((S_8080C650_4 *)temp_v0_3)->unk_24 = arg1;
                            ((S_8080C650_4 *)temp_v0_3)->unk_10 = (s32)D_80529080;
                            func_80034A1C(var_s0_2, D_8028954C, (s16)(loop_index * 4));
                        }
                    } while (--loop_index >= 0);
                }
            } else {
                ((S_8080C650_0 *)in0)->unk_A8 = (s32) (((S_8080C650_0 *)in0)->unk_A8 & ~1);
            }
            var_s2 = (s32)D_802894AC;
            ((S_8080C650_2 *)arg1)->unk_14 = 0;
            ((S_8080C650_2 *)arg1)->unk_10 = 0;
            ((S_8080C650_2 *)arg1)->unk_0C = 0;
            ((S_8080C650_0 *)in0)->unk_6C = 0x14U;
            ((S_8080C650_0 *)in0)->unk_68.s = 0xB;
        }
        break;
    case 11:
        temp_v1_3 = ((S_8080C650_3 *)arg2)->unk_14;
        if ((temp_v1_3 & 0x6000) && ((s16) ((S_8080C650_0 *)in0)->unk_6C > 0)) {
            var_s2 = (s32)D_802892EC;
            ((S_8080C650_3 *)arg2)->unk_14 = (u16) (temp_v1_3 | 0x800);
        }
        temp_v1_4 = ((S_8080C650_2 *)arg1)->unk_00;
        temp_v0_6 = 0x03A00000;
        if (temp_v1_4 > temp_v0_6) {
            temp_v0_6 = ((S_8080C650_3 *)arg2)->unk_14 & 0xFFFE;
        } else {
            temp_v0_6 = ((S_8080C650_3 *)arg2)->unk_14 | 1;
        }
        ((S_8080C650_3 *)arg2)->unk_14 = (u16)temp_v0_6;
        temp_v0_6_2 = ((S_8080C650_2 *)arg1)->unk_04;
        ((S_8080C650_2 *)arg1)->unk_04 = (s32) (((s32) (0x01E00000 - temp_v0_6_2) >> 1) + temp_v0_6_2);
        temp_v0_7 = ((S_8080C650_0 *)in0)->unk_6C - 1;
        ((S_8080C650_0 *)in0)->unk_6C = temp_v0_7;
        if ((temp_v0_7 << 0x10) == 0) {
            ((S_8080C650_3 *)arg2)->unk_14 = (u16) (((S_8080C650_3 *)arg2)->unk_14 & 0xF7FF);
            temp_v1_4 = ((S_8080C650_2 *)arg1)->unk_00;
            if (temp_v1_4 > 0x03A80000) {
                ((S_8080C650_2 *)arg1)->unk_0C = -0x80000;
            } else if (temp_v1_4 <= 0x0397FFFF) {
                ((S_8080C650_2 *)arg1)->unk_0C = 0x80000;
            } else {
                var_s2 = (s32)D_8028937C;
                ((S_8080C650_2 *)arg1)->unk_0C = 0;
                ((S_8080C650_2 *)arg1)->unk_00 = 0x03A00000;
            }
        }
        if ((u32) (((S_8080C650_2 *)arg1)->unk_00 + 0xFC440000) <= 0xC80000U) {
            ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0;
        } else {
            ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0x200000;
        }
        abs_v1 = 0xFC600000;
        delta = ((S_8080C650_2 *)arg1)->unk_00 + abs_v1;
        if ((abs(delta)) <= 0x80000) {
            if (((s32) (s16) ((S_8080C650_0 *)in0)->unk_6C) < 0) {
                ((S_8080C650_1 *)var_s0)->unk_2A = (u16) (((S_8080C650_1 *)var_s0)->unk_2A | 2);
                ((S_8080C650_2 *)arg1)->unk_14 = 0;
                ((S_8080C650_2 *)arg1)->unk_10 = 0;
                ((S_8080C650_2 *)arg1)->unk_0C = 0;
                ((S_8080C650_0 *)in0)->unk_68.s = 0;
                break;
            }
        }
        break;
    case 0xFF:
        var_a0 = 0;
        loop_index = 7;
        var_v1 = &D_80530658[7];
        do {
            temp_v0_4 = *var_v1;
            var_v1 -= 1;
            loop_index -= 1;
            var_a0 += temp_v0_4;
        } while (loop_index >= 0);
        if ((D_800133A0[0] < var_a0) || (var_a0 == 0x40)) {
            D_800133A0_store[0] = var_a0;
            func_80050BFC(0x5DA);
        } else {
            func_80050BD8(0x5DA);
        }
        var_s2 = (s32)D_802892EC;
        ((S_8080C650_2 *)arg1)->unk_10 = 0x80000;
        ((S_8080C650_0 *)in0)->unk_6C = 0x1EU;
        ((S_8080C650_0 *)in0)->unk_68.s = (s16) ((u16) ((S_8080C650_0 *)in0)->unk_68.s + 1);
    case 0x100:
    case 0x102:
        temp_v0_5 = ((S_8080C650_0 *)in0)->unk_6C - 1;
        ((S_8080C650_0 *)in0)->unk_6C = temp_v0_5;
        if ((temp_v0_5 << 0x10) <= 0) {
            ((S_8080C650_2 *)arg1)->unk_10 = 0;
            ((S_8080C650_2 *)arg1)->unk_14 = -0x100000;
            temp_state108 = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (temp_state108 + 1);
        }
        break;
    case 0x101:
    case 0x103:
        high_v0 = ((S_8080C650_2 *)arg1)->unk_14 + 0x20000;
        ((S_8080C650_2 *)arg1)->unk_14 = high_v0;
        if (((S_8080C650_2 *)arg1)->unk_08.at00.v > 0x1FFFFF) {
            ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0x200000;
            ((S_8080C650_2 *)arg1)->unk_14 = 0;
            temp_state108 = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (temp_state108 + 1);
        }
        break;
    case 0x104:
        var_s2 = (s32)D_80289334;
        raw_s1 = temp_v1 + 1;
        ((S_8080C650_0 *)in0)->unk_68.s = raw_s1;
        break;
    case 0x105:
        var_s2 = (s32)D_8028937C;
        raw_s1 = temp_v1 + 1;
        ((S_8080C650_0 *)in0)->unk_68.s = raw_s1;
        break;
    case 0x106:
        var_s2 = (s32)D_802893C4;
        raw_s1 = temp_v1 + 1;
        ((S_8080C650_0 *)in0)->unk_68.s = raw_s1;
        break;
    case 0x107:
        var_a0 = 0xC0C0C0;
        ((S_8080C650_2 *)arg1)->unk_10 = -0x80000;
        temp_v1_3 = ((S_8080C650_3 *)arg2)->unk_14;
        ((S_8080C650_3 *)arg2)->unk_10 = 0x60;
        ((S_8080C650_3 *)arg2)->unk_0C.s32 = var_a0;
        temp_v1_3 |= 0xC;
        ((S_8080C650_3 *)arg2)->unk_14 = temp_v1_3;
        temp_v0_6 = (u16) ((S_8080C650_0 *)in0)->unk_68.u;
        var_s2 = (s32)D_8028940C;
        temp_v0_6 += 1;
        ((S_8080C650_0 *)in0)->unk_68.s = (s16) temp_v0_6;
        break;
    case 0x108:
        ((S_8080C650_3 *)arg2)->unk_0C.s32 = (s32) (((S_8080C650_3 *)arg2)->unk_0C.s32 + 0xFFF7F7F8);
        if (((S_8080C650_3 *)arg2)->unk_0C.u8 < 0x11U) {
            temp_state108 = ((S_8080C650_0 *)in0)->unk_68.u;
            ((S_8080C650_0 *)in0)->unk_68.s = (s16) (temp_state108 + 1);
        }
        break;
    case 0x109:
        func_8023FB18(in0);
        (*(u16 *)((u8 *)in0 + -2)) = (u16) (((S_8080C650_0_pre *)in0)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
        return;
    }
    if (var_s2 != 0) {
        func_80034A1C(arg2, var_s2, 0);
    }
}
