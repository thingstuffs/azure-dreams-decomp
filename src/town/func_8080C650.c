/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

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
s32 func_8052776C() __attribute__((noreturn));
s32 func_805278B0() __attribute__((noreturn));
s32 func_80527920() __attribute__((noreturn));
s32 func_80527A3C() __attribute__((noreturn));
s32 func_80527AD0() __attribute__((noreturn));
s32 func_80527AF8() __attribute__((noreturn));
s32 func_80527BB8() __attribute__((noreturn));
s32 func_80527C60() __attribute__((noreturn));
s32 func_80527CCC() __attribute__((noreturn));
s32 func_80527CD8() __attribute__((noreturn));
s32 func_80527D18() __attribute__((noreturn));
s32 func_80527D2C() __attribute__((noreturn));
extern s16 D_800133A0[5];
extern s16 D_800133A0_store[5] __asm__("D_800133A0");
extern M2C_UNK D_8003C558[3];
extern volatile s32 D_80084D5C;
extern volatile s32 D_80084D5C_store __asm__("D_80084D5C");
extern M2C_UNK D_8012F130[5];
extern M2C_UNK D_801328C8[3];
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
extern s16 D_80530666;
void func_8080C650(void *in0, void *in1, void *in2) {
    s16 *var_v1;
    register s32 temp_s1 ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 raw_s1;
    s32 temp_v0_4;
    s16 temp_v1;
    register s32 var_a0 ASM_REG("$4");   /* MATCH pin: retail basic-block layout depends on it */
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    register s32 temp_lo ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 temp_v0_6 ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 temp_v1_4;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_v0_2;
    s32 tmpx;
    s32 state4_v0;
    s32 state4_a1;
    s32 high_v0;
    register s32 abs_v0 ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 abs_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 state6_v0;
    s32 state6_v1;
    register s32 state10_sin_v0 ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_7;
    u16 temp_state108;
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0_3;
    register void *var_s0 ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
    void *arg0 = in0;
    register void *arg1 ASM_REG("$19") = in1;   /* MATCH pin: keeps a constant in a register as retail does */
    void *arg2 = in2;
    s32 *global_s7;
    s32 *global_s5;

    var_s2 = 0;
    var_s0 = NULL;
    ASM_KEEP_NV(arg1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP_NV(arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    raw_s1 = func_8025E01C(arg1);
    global_s7 = D_8012F130;
    ASM_KEEP_NV(global_s7);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    global_s5 = D_801328E8;
    temp_s1 = raw_s1;
    if (((S_8080C650_0 *)arg0)->unk_68.s < 0xFF) {
        var_s0 = ((S_8080C650_0 *)arg0)->unk_AC;
        if (((S_8080C650_1 *)var_s0)->unk_36 == 0xFF) {
            ((S_8080C650_0 *)arg0)->unk_68.s = 0xFF;
        }
    }
    func_80245C10(arg1);
    if (((S_8080C650_2 *)arg1)->unk_08.at02.v >= temp_s1) {
        ((S_8080C650_2 *)arg1)->unk_08.at02.v = temp_s1;
    }
    func_8003EA54(arg2);
    temp_v1 = ((S_8080C650_0 *)arg0)->unk_68.s;
    if (temp_v1 == 0xB) {
        goto block_state11;
    }
    {
        if (temp_v1 < 0xC) {
            if (temp_v1 != 4) {
                if (temp_v1 < 5) {
                    if (temp_v1 != 1) {
                        if (temp_v1 < 2) {
                            if (temp_v1 != 0) {
                                return func_80527D18();
                            }
                            goto block_state0;
                        }
                        if (temp_v1 != 2) {
                            if (temp_v1 != 3) {
                                return func_80527D18();
                            }
                            goto block_state3;
                        }
                        goto block_state2;
                    }
                    goto block_state1;
                }
                if (temp_v1 < 0xA) {
                    if (temp_v1 < 7) {
                        if (temp_v1 != 5) {
                            if (temp_v1 != 6) {
                                return func_80527D18();
                            }
                            goto block_state6;
                        }
                        goto block_state5;
                    }
                    goto block_state7;
                }
                goto block_state10;
            }
            goto block_state4;
        }
        if (temp_v1 >= 0xC) {
            if (temp_v1 != 0x104) {
                if (temp_v1 < 0x105) {
                    if (temp_v1 != 0x101) {
                        if (temp_v1 < 0x102) {
                            if (temp_v1 != 0xFF) {
                                if (temp_v1 != 0x100) {
                                    return func_80527D18();
                                }
                                goto block_140;
                            }
                            goto block_highff;
                        }
                        if (temp_v1 != 0x102) {
                            if (temp_v1 != 0x103) {
                                return func_80527D18();
                            }
                            goto block_144;
                        }
                        goto block_140;
                    }
                    goto block_144;
                }
                if (temp_v1 != 0x107) {
                    if (temp_v1 < 0x108) {
                        if (temp_v1 != 0x105) {
                            if (temp_v1 != 0x106) {
                                return func_80527D18();
                            }
                            goto block_high106;
                        }
                        goto block_high105;
                    }
                    if (temp_v1 != 0x108) {
                        if (temp_v1 != 0x109) {
                            return func_80527D18();
                        }
                        goto block_high109;
                    }
                    goto block_high108;
                }
                goto block_high107;
            }
            goto block_high104;
        }
block_state0:
                ((S_8080C650_2 *)arg1)->unk_00 = 0x03A00000;
                ((S_8080C650_2 *)arg1)->unk_04 = 0x01E00000;
                ((S_8080C650_2 *)arg1)->unk_08.at02.v = func_8025E01C(arg1);
                ((S_8080C650_0 *)arg0)->unk_6C = 0x40U;
                ((S_8080C650_0 *)arg0)->unk_15 = 0;
                ((S_8080C650_0 *)arg0)->unk_68.s = 1;
block_state1:
                if (((S_8080C650_3 *)arg2)->unk_14 & 0x6000) {
                    ((S_8080C650_2 *)arg1)->unk_10 = 0x80000;
                    var_s2 = (s32)D_802892EC;
                }
                if (((S_8080C650_0 *)arg0)->unk_A8 & 1) {
                    temp_v0 = ((S_8080C650_0 *)arg0)->unk_6C - 1;
                    ((S_8080C650_0 *)arg0)->unk_6C = temp_v0;
                    if ((s16) temp_v0 >= 0) {
                        ((S_8080C650_2 *)arg1)->unk_00 = (s32) ((func_8006A3A4((s16) temp_v0 << 7) << 7) + 0x03A00000);
                    }
                }
                if (((S_8080C650_2 *)arg1)->unk_04 > 0x0477FFFF) {
                    ((S_8080C650_3 *)arg2)->unk_14 = (u16) (((S_8080C650_3 *)arg2)->unk_14 | 1);
                    ((S_8080C650_2 *)arg1)->unk_0C = 0x80000;
                    var_s2 = (s32)D_80289334;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    ((S_8080C650_0 *)arg0)->unk_68.s = 2;
                    return func_80527D18();
                }
                goto block_160;
block_state2:
                if (((S_8080C650_3 *)arg2)->unk_14 & 0x6000) {
                    var_s2 = (s32)D_802893C4;
                }
                if (((S_8080C650_2 *)arg1)->unk_04 > 0x048FFFFF) {
                    tmpx = 3;
                    var_s2 = (s32)D_8028937C;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    ((S_8080C650_2 *)arg1)->unk_10 = 0;
                    ((S_8080C650_0 *)arg0)->unk_68.s = tmpx;
                    return func_80527D18();
                }
                goto block_160;
block_state3:
                if (((S_8080C650_3 *)arg2)->unk_14 & 0x6000) {
                    var_s2 = (s32)D_802893C4;
                }
                if (((S_8080C650_2 *)arg1)->unk_00 > 0x03DFFFFF) {
                    ((S_8080C650_2 *)arg1)->unk_14 = -0x100000;
                    var_s2 = (s32)D_80289454;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    ((S_8080C650_0 *)arg0)->unk_68.s = 4;
                    return func_80527D18();
                }
                goto block_160;
block_state4:
                temp_a0 = ((S_8080C650_2 *)arg1)->unk_00;
                state4_a1 = 0x48000;
                state4_v0 = ((S_8080C650_2 *)arg1)->unk_14 + state4_a1;
                ((S_8080C650_2 *)arg1)->unk_14 = state4_v0;
                if (temp_a0 > 0x041FFFFF) {
                    ((S_8080C650_2 *)arg1)->unk_14 = 0;
                    ((S_8080C650_2 *)arg1)->unk_0C = 0;
                    ((S_8080C650_0 *)arg0)->unk_15 = 1;
                    ((S_8080C650_0 *)arg0)->unk_68.s = 5;
                    return func_80527D18();
                }
                goto block_160;
block_state5:
                if (global_s5[0] == (s32)D_802430A8) {
                    ((S_8080C650_0 *)arg0)->unk_6C = 7U;
                    global_s5[0] = (s32)D_80243200;
                    ((S_8080C650_0 *)arg0)->unk_15 = 0;
                    ((S_8080C650_0 *)arg0)->unk_68.s = 6;
                    return func_80527D18();
                }
                goto block_160;
block_state6:
                ((S_8080C650_2 *)arg1)->unk_0C = (s32) ((s32) (D_80132AE8[0] - ((S_8080C650_2 *)arg1)->unk_00) >> 1);
                ((S_8080C650_2 *)arg1)->unk_10 = (s32) ((s32) (D_80132AEC[0] - ((S_8080C650_2 *)arg1)->unk_04) >> 1);
                state6_v0 = D_80132AF0[0] + D_8029070C[0];
                state6_v1 = ((S_8080C650_2 *)arg1)->unk_08.at00.v + 0x80000;
                state6_v0 -= state6_v1;
                ((S_8080C650_2 *)arg1)->unk_14 = state6_v0 >> 1;
                func_80245C10(arg1);
                global_s5[0] = (s32)D_80243200;
                temp_v0_2 = ((S_8080C650_0 *)arg0)->unk_6C - 1;
                ((S_8080C650_0 *)arg0)->unk_6C = temp_v0_2;
                if ((temp_v0_2 << 0x10) <= 0) {
                    global_s5[0] = (s32)D_80243200;
                    ((S_8080C650_2 *)arg1)->unk_14 = 0;
                    ((S_8080C650_2 *)arg1)->unk_10 = 0;
                    ((S_8080C650_2 *)arg1)->unk_0C = 0;
                    ((S_8080C650_0 *)arg0)->unk_68.s = 7;
                    return func_80527D18();
                }
                goto block_160;
block_state7:
                    ((S_8080C650_2 *)arg1)->unk_00 = (s32) D_80132AE8[0];
                    ((S_8080C650_2 *)arg1)->unk_04 = (s32) D_80132AEC[0];
                    ((S_8080C650_2 *)arg1)->unk_08.at00.v = (s32) (D_80132AF0[0] + D_8029070C[0] + 0xFFF80000);
                    if (global_s7[4] & 0x20) {
                        if (D_80132AF2[0] == 0) {
                            if (((S_8080C650_0 *)arg0)->unk_68.s == 9) {
                                tmpx = 0x100000;
                                var_s2 = (s32)D_8028950C;
                                ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                                ((S_8080C650_1 *)var_s0)->unk_00 = tmpx;
                                return func_8052776C();
                            }
                            global_s5[0] = (s32)D_802434B0;
                            ((S_8080C650_2 *)arg1)->unk_14 = 0x100000;
                            return func_8052776C();
                        }
                        global_s5[0] = (s32)D_80243200;
                        if (((S_8080C650_0 *)arg0)->unk_68.s == 9) {
                            func_80058F88(0x700);
                        }
                        ((S_8080C650_1 *)var_s0)->unk_2A = (u16)(((S_8080C650_1 *)var_s0)->unk_2A & ~4);
                        return func_80527CCC();
                    }
                    goto block_160;
block_state10:
                state10_sin_v0 = (s32) (((s32) ((S_8080C650_1 *)var_s0)->unk_00 >> 0xC) * func_8006A3A4(((S_8080C650_1 *)var_s0)->unk_2C));
                ((S_8080C650_2 *)arg1)->unk_0C = state10_sin_v0;
                temp_lo = ((s32) (0 - ((S_8080C650_1 *)var_s0)->unk_00) >> 0xC) * func_8006A470(((S_8080C650_1 *)var_s0)->unk_2C);
                ((S_8080C650_2 *)arg1)->unk_10 = temp_lo;
                if (temp_lo > -0x40000) {
                    ((S_8080C650_2 *)arg1)->unk_10 = -0x40000;
                }
                ((S_8080C650_1 *)var_s0)->unk_2C = (s16) ((u16) ((S_8080C650_1 *)var_s0)->unk_2C - ((s32) (((S_8080C650_1 *)var_s0)->unk_2E << 0x10) >> 0x14));
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
                            goto block_98;
                        }
                        if (temp_a0_2 > 0x03800000) {
                            goto block_99;
                        }
                        ((S_8080C650_2 *)arg1)->unk_00 = 0x03880000;
                        return func_805278B0(temp_a0_2);
                    }
                    if (temp_a0_2 > 0x04BFFFFF) {
                        var_v0_2 = 0x04B80000;
                        goto block_98;
                    }
                    if (temp_a0_2 > 0x04800000) {
                        goto block_99;
                    }
                    var_v0_2 = 0x04880000;
block_98:
                    ((S_8080C650_2 *)arg1)->unk_00 = var_v0_2;
block_99:
                    ((S_8080C650_1 *)var_s0)->unk_2C = (s16) ((s32) (0 - ((S_8080C650_1 *)var_s0)->unk_2C) >> 1);
                    goto block_100;
                }
block_100:
                if (((S_8080C650_2 *)arg1)->unk_04 <= 0x01E00000) {
                    func_80058F88(0x1700);
                    func_80058F88(0x1701);
                    if (D_80530658[((S_8080C650_1 *)var_s0)->unk_34] == 8) {
                        var_s2 = 1;
                        global_s5 = (s32 *)0x1000;
                        ((S_8080C650_0 *)arg0)->unk_A8 = (s32) (((S_8080C650_0 *)arg0)->unk_A8 | 1);
                        {
                            ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                            temp_v0_3 = func_800374FC(0x136, D_801328C8);
                            if (temp_v0_3 != NULL) {
                                var_s0 = ((S_8080C650_4 *)temp_v0_3)->unk_0C;
                                func_8003BC18(temp_v0_3, D_8003C558);
                                ((S_8080C650_1 *)var_s0)->unk_0C = 0x808080;
                                ((S_8080C650_1 *)var_s0)->unk_1E = (s16)(s32)global_s5;
                                ((S_8080C650_1 *)var_s0)->unk_1C = (s16)(s32)global_s5;
                                ((S_8080C650_4 *)temp_v0_3)->unk_22 = 0x78;
                                ((S_8080C650_4 *)temp_v0_3)->unk_24 = arg1;
                                ((S_8080C650_4 *)temp_v0_3)->unk_10 = (s32)D_80529080;
                                func_80034A1C(var_s0, D_8028954C, (s16)(var_s2 * 4));
                            }
                            var_s2 -= 1;
                            if (var_s2 >= 0) {
                                return func_80527920();
                            }
                            goto block_after;
                        }
                    }
                    ((S_8080C650_0 *)arg0)->unk_A8 = (s32) (((S_8080C650_0 *)arg0)->unk_A8 & ~1);
block_after:
                    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    var_s2 = (s32)D_802894AC;
                    ((S_8080C650_2 *)arg1)->unk_14 = 0;
                    ((S_8080C650_2 *)arg1)->unk_10 = 0;
                    ((S_8080C650_2 *)arg1)->unk_0C = 0;
                    ((S_8080C650_0 *)arg0)->unk_6C = 0x14U;
                    ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    ((S_8080C650_0 *)arg0)->unk_68.s = 0xB;
                    return func_80527D18();
                }
                goto block_160;
block_state11:
        temp_v1_3 = ((S_8080C650_3 *)arg2)->unk_14;
        if ((temp_v1_3 & 0x6000) && ((s16) ((S_8080C650_0 *)arg0)->unk_6C > 0)) {
            var_s2 = (s32)D_802892EC;
            ((S_8080C650_3 *)arg2)->unk_14 = (u16) (temp_v1_3 | 0x800);
        }
        temp_v1_4 = ((S_8080C650_2 *)arg1)->unk_00;
        temp_v0_6 = 0x03A00000;
        if (temp_v1_4 > temp_v0_6) {
            temp_v0_6 = ((S_8080C650_3 *)arg2)->unk_14 & 0xFFFE;
            ASM_TAILSLOT_PIN_TIED(temp_v0_6);   /* MATCH pin: retail delay-slot fill depends on it */
            return func_80527A3C();
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((S_8080C650_3 *)arg2)->unk_14 = (u16) (((S_8080C650_3 *)arg2)->unk_14 | 1);
        temp_v0_6 = ((S_8080C650_2 *)arg1)->unk_04;
        ((S_8080C650_2 *)arg1)->unk_04 = (s32) (((s32) (0x01E00000 - temp_v0_6) >> 1) + temp_v0_6);
        temp_v0_7 = ((S_8080C650_0 *)arg0)->unk_6C - 1;
        ((S_8080C650_0 *)arg0)->unk_6C = temp_v0_7;
        if ((temp_v0_7 << 0x10) == 0) {
            ((S_8080C650_3 *)arg2)->unk_14 = (u16) (((S_8080C650_3 *)arg2)->unk_14 & 0xF7FF);
            temp_v1_4 = ((S_8080C650_2 *)arg1)->unk_00;
            if (temp_v1_4 > 0x03A80000) {
                ((S_8080C650_2 *)arg1)->unk_0C = -0x80000;
                return func_80527AD0();
            }
            ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            if (temp_v1_4 <= 0x0397FFFF) {
                ((S_8080C650_2 *)arg1)->unk_0C = 0x80000;
                return func_80527AD0();
            }
            var_s2 = (s32)D_8028937C;
            ((S_8080C650_2 *)arg1)->unk_0C = 0;
            ((S_8080C650_2 *)arg1)->unk_00 = 0x03A00000;
            goto block_124;
        }
block_124:
        if ((u32) (((S_8080C650_2 *)arg1)->unk_00 + 0xFC440000) <= 0xC80000U) {
            ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0;
            return func_80527AF8();
        }
        ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0x200000;
        ASM_KEEP_NV(arg1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        abs_v1 = 0xFC600000;
        abs_v0 = ((S_8080C650_2 *)arg1)->unk_00 + abs_v1;
        if (abs_v0 < 0) {
            abs_v0 = 0 - abs_v0;
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        if (abs_v0 <= 0x80000) {
            abs_v0 = (s32) (s16) ((S_8080C650_0 *)arg0)->unk_6C;
            if (abs_v0 < 0) {
                ((S_8080C650_1 *)var_s0)->unk_2A = (u16) (((S_8080C650_1 *)var_s0)->unk_2A | 2);
                ((S_8080C650_2 *)arg1)->unk_14 = 0;
                ((S_8080C650_2 *)arg1)->unk_10 = 0;
                ((S_8080C650_2 *)arg1)->unk_0C = 0;
                ((S_8080C650_0 *)arg0)->unk_68.s = 0;
                return func_80527D18();
            }
        }
        goto block_160;
block_highff:
        var_a0 = 0;
        var_s2 = 7;
        var_v1 = &D_80530658[7];
        do {
            temp_v0_4 = *var_v1;
            var_v1 -= 1;
            var_s2 -= 1;
            var_a0 += temp_v0_4;
        } while (var_s2 >= 0);
        if ((D_800133A0[0] < var_a0) || (var_a0 == 0x40)) {
            D_800133A0_store[0] = var_a0;
            func_80050BFC(0x5DA);
            return func_80527BB8();
        }
        func_80050BD8(0x5DA);
        var_s2 = (s32)D_802892EC;
        ((S_8080C650_2 *)arg1)->unk_10 = 0x80000;
        ((S_8080C650_0 *)arg0)->unk_6C = 0x1EU;
        ((S_8080C650_0 *)arg0)->unk_68.s = (s16) ((u16) ((S_8080C650_0 *)arg0)->unk_68.s + 1);
block_140:
        temp_v0_5 = ((S_8080C650_0 *)arg0)->unk_6C - 1;
        ((S_8080C650_0 *)arg0)->unk_6C = temp_v0_5;
        if ((temp_v0_5 << 0x10) <= 0) {
            ((S_8080C650_2 *)arg1)->unk_10 = 0;
            ((S_8080C650_2 *)arg1)->unk_14 = -0x100000;
            return func_80527CCC();
        }
        goto block_160;
block_144:
        high_v0 = ((S_8080C650_2 *)arg1)->unk_14 + 0x20000;
        ((S_8080C650_2 *)arg1)->unk_14 = high_v0;
        if (((S_8080C650_2 *)arg1)->unk_08.at00.v > 0x1FFFFF) {
            ((S_8080C650_2 *)arg1)->unk_08.at00.v = 0x200000;
            ((S_8080C650_2 *)arg1)->unk_14 = 0;
            return func_80527CCC();
        }
        goto block_160;
block_high104:
        var_s2 = (s32)D_80289334;
        raw_s1 = temp_v1 + 1;
        ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_TAILSLOT_PIN_TIED(raw_s1);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_80527C60();
block_high105:
        var_s2 = (s32)D_8028937C;
        raw_s1 = temp_v1 + 1;
        ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_TAILSLOT_PIN_TIED(raw_s1);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_80527C60();
block_high106:
        var_s2 = (s32)D_802893C4;
        raw_s1 = temp_v1 + 1;
        ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ((S_8080C650_0 *)arg0)->unk_68.s = raw_s1;
        return func_80527D18();
block_high107:
        var_a0 = 0xC0C0C0;
        ((S_8080C650_2 *)arg1)->unk_10 = -0x80000;
        temp_v1_3 = ((S_8080C650_3 *)arg2)->unk_14;
        ((S_8080C650_3 *)arg2)->unk_10 = 0x60;
        ((S_8080C650_3 *)arg2)->unk_0C.s32 = var_a0;
        temp_v1_3 |= 0xC;
        ((S_8080C650_3 *)arg2)->unk_14 = temp_v1_3;
        temp_v0_6 = (u16) ((S_8080C650_0 *)arg0)->unk_68.u;
        ASM_KEEP(temp_v0_6);   /* MATCH pin: retail schedule: same instructions, different order without it */
        var_s2 = (s32)D_8028940C;
        ASM_KEEP(var_s2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_v0_6 += 1;
        ASM_TAILSLOT_PIN_TIED(temp_v0_6);   /* MATCH pin: retail delay-slot fill depends on it */
        return func_80527CD8(var_a0);
block_high108:
        ((S_8080C650_3 *)arg2)->unk_0C.s32 = (s32) (((S_8080C650_3 *)arg2)->unk_0C.s32 + 0xFFF7F7F8);
        if (((S_8080C650_3 *)arg2)->unk_0C.u8 < 0x11U) {
            temp_state108 = ((S_8080C650_0 *)arg0)->unk_68.u;
            ((S_8080C650_0 *)arg0)->unk_68.s = (s16) (temp_state108 + 1);
            return func_80527D18();
        }
        goto block_160;
block_high109:
        func_8023FB18(arg0);
        (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_8080C650_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_80084D5C_store = D_80084D5C | 0x8000;
        return func_80527D2C();
    }
block_160:
    if (var_s2 != 0) {
        func_80034A1C(arg2, var_s2, 0);
    }
}
