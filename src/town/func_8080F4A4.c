#include "common.h"

typedef s32 M2C_UNK;
#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

/* RAW m2c DRAFT -- NOT A LANDABLE CANDIDATE.
 * Row func_8080F4A4, disassembled at the RECOVERED true load base
 * delta=0x7FD9AC00 (true vram 0x8052A0A4), not the synthetic
 * 0x80080000 sweep base the window yaml still declares.
 * Adopting this requires the after-wave overlay-base fix; do
 * not copy into work/overlay_wave/candidates/ (that directory is
 * globbed by tools/gen_noreturn_syms.py).
 */
void *func_800374FC(s32, void *);            /* extern */
void func_8003BC18(void *, void *);           /* extern */
s32 func_80052374(s32);                             /* extern */
void func_80058F88(s32);                     /* extern */
s32 func_8006A3A4(s32);                             /* extern */
s32 func_8006A470(s32);                             /* extern */
s32 func_80071494();                                /* extern */
s32 func_80232868(s32, s32, s32);       /* extern */
void func_80232A08(s32);                         /* extern */
void func_802441A4();                   /* extern */
void func_80244588();                            /* extern */
void func_802445FC(s32, ...);    /* extern */
void func_80244660(void *, ...); /* extern */
void func_80529438(void *, ...);           /* extern */
extern u32 D_80012BCC[3];
extern u32 D_80012BC8[4];
extern u8 D_8003C558[16];
extern u8 D_80095AA0[16];
extern u8 D_8012F130[0x14];
extern u8 D_801328C8[16];
extern u8 D_801328E8[0x20];
extern s32 D_80132AE8[6];
extern s32 D_802BC5C8[3];
extern s32 D_80530588[3];
extern u8 D_802483B8[];
extern u8 D_80290268[];
extern u8 D_80290270[];
extern u8 D_80290290[];
extern u8 D_80290298[];
extern u8 D_802902A8[];
extern u8 D_8052B054[];
extern u8 D_8052B1EC[];
extern u8 D_8053012C[];
void func_8052A0A4(void *arg0) {
    u8 local[0x80];
#define sp10 FIELD(local, s16 *, 0)
#define sp12 FIELD(local, s16 *, 2)
#define sp14 FIELD(local, void **, 4)
#define sp2D FIELD(local, s8 *, 0x1D)
#define sp64 FIELD(local, s16 *, 0x54)
#define sp66 FIELD(local, s16 *, 0x56)
#define sp68 FIELD(local, s32 *, 0x58)
#define sp6C FIELD(local, s32 *, 0x5C)
#define sp70 FIELD(local, s32 *, 0x60)
#define sp74 FIELD(local, s32 *, 0x64)
#define sp78 FIELD(local, s32 *, 0x68)
#define sp7C FIELD(local, s32 *, 0x6C)
#define sp80 FIELD(local, s16 *, 0x70)
#define sp82 FIELD(local, s16 *, 0x72)
#define sp84 FIELD(local, s16 *, 0x74)
    M2C_UNK var_a0;
    M2C_UNK var_a0_2;
    s16 temp_a0_2;
    s16 temp_a1;
    s16 temp_s0_2;
    s32 temp_v0;
    s16 temp_v0_13;
    s16 temp_v0_14;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 *var_s4;
    s32 temp_a2;
    s32 temp_call;
    s32 temp_lo;
    s32 temp_s0_3;
    s32 temp_scale;
    s32 temp_v0_12;
    s32 var_s1;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_v0;
    s32 var_v0_3;
    s32 var_v0_4;
    u16 temp_a0;
    u16 temp_flags0;
    s32 temp_v0_10;
    u16 temp_v0_11;
    u16 temp_v0_15;
    u16 temp_v0_16;
    s16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 var_v0_5;
    s16 temp_v0_17;
    s32 temp_b14;
    s32 work_v0;
    s32 work_v1;
    void *temp_a0_3;
    void *global_a0;
    void *global_s0;
    void *temp_s0;
    void *temp_s3;
    void *temp_v0_3;

    global_a0 = &D_8012F130;
    global_s0 = &D_801328E8;
    temp_v1 = FIELD(arg0, s16 *, 0x18);
    temp_s3 = FIELD(arg0, s32 *, 0) + 0x20;
    switch (temp_v1) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        temp_flags0 = FIELD(arg0, u16 *, 0x20);
        D_802BC5C8[0] = 1;
        FIELD(arg0, s16 *, 0x22) = 3;
        FIELD(arg0, u16 *, 0x1E) = 0U;
        FIELD(arg0, s32 *, 0x14) = 0;
        FIELD(arg0, u16 *, 0x20) = (u16) (temp_flags0 & 0xFFFD);
        func_802441A4(global_a0);
        func_80058F88(0x700);
        work_v0 = FIELD(arg0, u16 *, 0x20);
        work_v1 = 1;
        FIELD(arg0, s16 *, 0x18) = work_v1;
        FIELD(arg0, u16 *, 0x20) = (u16) (work_v0 & 0xFFF7);
        sp10 = 0;
        sp14 = arg0;
        sp64 = 2;
        do {
            sp66 = 9;
loop_4:
            sp6C = 0x03E00000;
            sp7C = 0;
            sp78 = 0;
            sp74 = 0;
            temp_a2 = sp64 << 0x16;
            work_v1 = 0x05200000 - temp_a2;
            sp68 = work_v1;
            work_v0 = 0 - (sp66 << 0x13);
            sp70 = work_v0;
            func_80529438(&sp10, &sp68, temp_a2);
            temp_v0_2 = (u16) sp66 - 1;
            sp66 = temp_v0_2;
            if ((s16) temp_v0_2 >= 0) {
                goto loop_4;
            }
            temp_v0 = (u16) sp64 - 1;
            sp64 = temp_v0;
        } while ((s16) temp_v0 >= 0);
        var_s3 = 2;
        temp_scale = 0x1000;
        var_s4 = (s32 *)D_8053012C;
        do {
            temp_v0_3 = func_800374FC(0x112, &D_801328C8);
            if (temp_v0_3 != NULL) {
                temp_s0 = FIELD(temp_v0_3, void **, 0xC);
                FIELD(temp_v0_3, s32 *, 0x10) = (s32 *)D_8052B054;
                func_8003BC18(temp_v0_3, &D_8003C558);
                FIELD(FIELD(temp_v0_3, void **, 8), s32 *, 0) = (s32) ((var_s3 << 0x17) + 0x04600000);
                FIELD(FIELD(temp_v0_3, void **, 8), s32 *, 4) = 0x03600000;
                FIELD(FIELD(temp_v0_3, void **, 8), s32 *, 8) = 0xFE000000;
                FIELD(temp_s0, s16 *, 0x1E) = temp_scale;
                FIELD(temp_s0, s16 *, 0x1C) = temp_scale;
                FIELD(temp_s0, u16 *, 0x14) = (u16) (FIELD(temp_s0, u16 *, 0x14) | 0xC);
                FIELD(temp_s0, s32 *, 8) = (s32) *var_s4;
                FIELD(temp_s0, s8 *, 4) = 0;
                FIELD(temp_s0, s8 *, 5) = 0;
                FIELD(temp_s0, s32 *, 0xC) = 0x808080;
                FIELD(temp_v0_3, void **, 0x24) = arg0;
            }
            var_s3 -= 1;
            var_s4 -= 1;
        } while (var_s3 >= 0);
        break;
    case 1:                                         /* switch 1 */
        if (FIELD(arg0, s16 *, 0x22) != 3) {
            temp_call = func_80232868(0, -0x50, 0x40);
            temp_lo = 6 / (s32) (FIELD(arg0, s16 *, 0x22) + 1);
            D_80530588[0] = temp_call;
            FIELD(arg0, s32 *, 0x10) = temp_lo;
            if (func_80052374(temp_lo) == 0) {
                D_80132AE8[5] = 0;
                D_80132AE8[4] = 0;
                D_80132AE8[3] = 0;
                FIELD(global_s0, u16 *, 0x10) = 0U;
                func_802445FC((s32)D_80290268);
                FIELD(global_s0, s32 *, 0) = (s32)D_802483B8;
                FIELD(global_s0, s32 *, 4) = (s32)D_8052B1EC;
            }
            FIELD(temp_s3, s16 *, 0x70) = 1;
            FIELD(temp_s3, s16 *, 0x72) = 0x10;
            FIELD(temp_s3, s16 *, 0x74) = 0x14;
            FIELD(arg0, u16 *, 0x1A) = 5U;
            FIELD(arg0, s16 *, 0x18) = 2;
        }
        break;
    case 2:                                         /* switch 1 */
        if (FIELD(global_a0, s32 *, 8) & 0x5000) {
            temp_v0_4 = FIELD(arg0, u16 *, 0x1A);
            FIELD(arg0, u16 *, 0x1A) = (u16) (temp_v0_4 - 1);
            if (temp_v0_4 < 0) {
                FIELD(arg0, u16 *, 0x1A) = 0U;
            }
        } else {
            FIELD(arg0, u16 *, 0x1A) = 5U;
        }
        if (((FIELD(global_a0, s32 *, 0x10) & 0x1000) || ((FIELD(global_a0, s32 *, 8) & 0x1000) && ((s16) FIELD(arg0, u16 *, 0x1A) <= 0))) && (FIELD(arg0, s32 *, 0x14) <= 0x1869F) && ((u32) D_80012BCC[0] >= 0x3E8U)) {
            D_80012BC8[1] = D_80012BCC[0] - 0x3E8;
            var_v0 = FIELD(arg0, s32 *, 0x14) + 0x3E8;
            goto block_30;
        }
        if (((FIELD(global_a0, s32 *, 0x10) & 0x4000) || ((FIELD(global_a0, s32 *, 8) & 0x4000) && ((s16) FIELD(arg0, u16 *, 0x1A) <= 0))) && (FIELD(arg0, s32 *, 0x14) >= 0x3E8)) {
            D_80012BC8[1] = D_80012BCC[0] + 0x3E8;
            var_v0 = FIELD(arg0, s32 *, 0x14) - 0x3E8;
block_30:
            FIELD(arg0, s32 *, 0x14) = var_v0;
        }
        FIELD(arg0, u16 *, 0x1E) = (u16) (FIELD(arg0, s32 *, 0x14) / 1000);
        temp_v1 = FIELD(global_a0, s32 *, 0x10);
        if (temp_v1 & 0x20) {
            if (FIELD(arg0, s32 *, 0x14) > 0) {
                FIELD(arg0, s16 *, 0x18) = 3;
                FIELD(arg0, u16 *, 0x1A) = 9U;
                D_80132AE8[5] = -0x240000;
            }
        } else if (temp_v1 & 0x40) {
            if (FIELD(temp_s3, s16 *, 0x70) != 0) {
                FIELD(temp_s3, s16 *, 0x70) = 3;
            }
            FIELD(arg0, s16 *, 0x18) = 0xA;
            func_80244660(global_s0, &D_80132AE8[0], &D_80095AA0);
        }
        break;
    case 3:                                         /* switch 1 */
        FIELD(global_s0, u16 *, 0x10) = (u16) ((FIELD(global_s0, u16 *, 0x10) + 0x200) & 0xFFF);
        temp_v0_5 = FIELD(arg0, u16 *, 0x1A) - 1;
        FIELD(arg0, u16 *, 0x1A) = temp_v0_5;
        if ((temp_v0_5 << 0x10) <= 0) {
            FIELD(arg0, u16 *, 0x1A) = 0xAU;
            D_80132AE8[3] = (s32) (0x03600000 - D_80132AE8[0]) / (s16) FIELD(arg0, u16 *, 0x1A);
            D_80132AE8[4] = (s32) (0x02A00000 - D_80132AE8[1]) / (s16) FIELD(arg0, u16 *, 0x1A);
            FIELD(arg0, s16 *, 0x18) = 0xB;
        }
        break;
    case 11:                                        /* switch 1 */
        FIELD(global_s0, u16 *, 0x10) = (u16) ((FIELD(global_s0, u16 *, 0x10) + 0x200) & 0xFFF);
        temp_v0_6 = FIELD(arg0, u16 *, 0x1A) - 1;
        FIELD(arg0, u16 *, 0x1A) = temp_v0_6;
        if ((temp_v0_6 << 0x10) <= 0) {
            D_80132AE8[0] = 0x03600000;
            D_80132AE8[1] = 0x02A00000;
            D_80132AE8[5] = 0x180000;
            D_80132AE8[4] = 0;
            D_80132AE8[3] = 0;
            FIELD(arg0, s16 *, 0x18) = 0xC;
        }
        break;
    case 12: {                                      /* switch 1 */
        s32 temp_case12_limit;
        s32 *temp_case12_ptr;
        temp_case12_ptr = &D_80132AE8[2];
        temp_case12_limit = (s32)0xFF000000;
        temp_a0 = (FIELD(global_s0, u16 *, 0x10) + 0x200) & 0xFFF;
        FIELD(global_s0, u16 *, 0x10) = temp_a0;
        if ((*temp_case12_ptr >= temp_case12_limit) && (temp_a0 == 0)) {
            *temp_case12_ptr = temp_case12_limit;
            FIELD(arg0, s16 *, 0x18) = 4;
            func_80244660(global_s0, temp_case12_ptr - 2, &D_80095AA0, temp_case12_limit);
            func_80244588();
        }
        break;
    }
    case 4:                                         /* switch 1 */
        if ((FIELD(global_a0, s32 *, 0x10) & 0x20) && (FIELD(temp_s3, s16 *, 0x70) == 2)) {
            func_802445FC((s32)D_80290290);
            D_80132AE8[4] = 0x48000;
            D_80132AE8[5] = -0xC0000;
            FIELD(arg0, u16 *, 0x1C) = 0U;
            FIELD(arg0, s16 *, 0x18) = 5;
        }
        break;
    case 5:                                         /* switch 1 */
        D_80132AE8[1] += D_80132AE8[4];
        D_80132AE8[2] += D_80132AE8[5];
        if (D_80132AE8[5] <= 0x9FFFF) {
            D_80132AE8[5] += 0x20000;
        }
        temp_v0_7 = FIELD(arg0, u16 *, 0x1C);
        FIELD(arg0, u16 *, 0x1C) = (u16) (temp_v0_7 + 1);
        switch ((s16) temp_v0_7) {                  /* switch 2 */
        case 0x0:                                   /* switch 2 */
            goto block_0;
        case 0x15:                                  /* switch 2 */
        case 0x25:                                  /* switch 2 */
        case 0x31:                                  /* switch 2 */
        case 0x3E:                                  /* switch 2 */
            goto block_98;
        case 0x5:                                   /* switch 2 */
            goto block_5;
        case 0x19:                                  /* switch 2 */
        case 0x29:                                  /* switch 2 */
        case 0x35:                                  /* switch 2 */
            goto block_A8;
        case 0x14:                                  /* switch 2 */
            goto block_14;
        case 0x24:                                  /* switch 2 */
            goto block_24;
        case 0x30:                                  /* switch 2 */
            goto block_30_arm;
        case 0x3D:                                  /* switch 2 */
            goto block_3D;
        default:
            goto switch_2_end;
        }
block_0:
        var_a0 = (s32)D_80290298;
        goto block_61;
block_5:
        var_a0 = (s32)D_802902A8;
        goto block_61;
block_14:
        temp_b14 = 0x18000;
        var_a0 = (s32)D_80290268;
        D_80132AE8[5] = -0xC0000;
        D_80132AE8[4] = temp_b14;
        goto block_61;
block_A8:
        var_a0 = (s32)&D_80290298[0x10];
        goto block_61;
block_98:
        var_a0 = (s32)&D_80290290[8];
        goto block_61;
block_24:
        var_a0 = (s32)D_80290268;
        D_80132AE8[5] = -0x80000;
        D_80132AE8[4] = 0x20000;
        goto block_61;
block_30_arm:
        var_v0_3 = -0x40000;
        goto block_60;
block_3D:
        var_v0_3 = -0x38000;
block_60:
        D_80132AE8[5] = var_v0_3;
        var_a0 = (s32)D_80290268;
        goto block_61;
block_61:
        func_802445FC(var_a0);
switch_2_end:
        if (FIELD(temp_s3, s16 *, 0x70) == 3) {
            D_80132AE8[5] = -0x50000;
            D_80132AE8[4] = 0;
            D_80132AE8[2] = -0x400000;
            func_802445FC((s32)D_80290268);
            FIELD(arg0, u16 *, 0x1C) = 0U;
            FIELD(arg0, s16 *, 0x18) = 6;
        }
        break;
    case 6:                                         /* switch 1 */
        D_80132AE8[2] += D_80132AE8[5];
        D_80132AE8[5] += 0x10000;
        temp_v0_8 = FIELD(arg0, u16 *, 0x1C);
        FIELD(arg0, u16 *, 0x1C) = (u16) (temp_v0_8 + 1);
        switch ((s16) temp_v0_8) {                  /* switch 3 */
        case 0:                                     /* switch 3 */
        case 11:                                    /* switch 3 */
        case 19:                                    /* switch 3 */
            goto block_6_98;
        case 5:                                     /* switch 3 */
            goto block_6_A8;
        case 10:                                    /* switch 3 */
            goto block_6_10;
        case 26:                                    /* switch 3 */
            goto block_6_26;
        case 18:                                    /* switch 3 */
            goto block_6_18;
        default:
            goto switch_3_end;
        }
block_6_98:
        var_a0_2 = (s32)D_80290298;
        goto block_73;
block_6_A8:
        var_a0_2 = (s32)D_802902A8;
        goto block_73;
block_6_10:
        var_v0_4 = -0x40000;
        goto block_71;
block_6_18:
        var_v0_4 = -0x30000;
block_71:
        D_80132AE8[5] = var_v0_4;
block_6_26:
        var_a0_2 = (s32)D_80290268;
        goto block_73;
block_73:
        func_802445FC(var_a0_2);
switch_3_end:
        if ((s16) FIELD(arg0, u16 *, 0x1C) == 0x1C) {
            FIELD(temp_s3, s16 *, 0x70) = 4;
            D_80132AE8[5] = 0;
            D_80132AE8[2] = -0x400000;
            func_802445FC((s32)D_80290268);
            FIELD(arg0, u16 *, 0x1C) = 3U;
            FIELD(arg0, s16 *, 0x18) = 7;
        }
        break;
    case 7:                                         /* switch 1 */
        D_80132AE8[0] = (func_8006A3A4(0x1000 - (s16) FIELD(arg0, u16 *, 0x1A)) * 0xA00) + 0x03600000;
        D_80132AE8[1] = (func_8006A470(0x1000 - (s16) FIELD(arg0, u16 *, 0x1A)) * 0xA00) + 0x03600000;
        temp_v0_9 = FIELD(arg0, u16 *, 0x1C) - 1;
        FIELD(arg0, u16 *, 0x1C) = temp_v0_9;
        if ((temp_v0_9 << 0x10) == 0) {
            func_802445FC((s32)D_80290270);
        }
        if (FIELD(temp_s3, s16 *, 0x70) == 0) {
            func_802441A4();
            if (FIELD(arg0, s16 *, 0x22) == FIELD(arg0, s16 *, 0x24)) {
                FIELD(temp_s3, s16 *, 0x70) = 6;
                FIELD(arg0, u16 *, 0x1A) = 0x1EU;
                FIELD(arg0, s16 *, 0x18) = 8;
            } else {
                FIELD(arg0, s32 *, 0x14) = 0;
                FIELD(arg0, s16 *, 0x18) = 0xA;
            }
        }
        break;
    case 8: {                                       /* switch 1 */
        s32 temp_v1_2;
        temp_v0_10 = FIELD(arg0, u16 *, 0x1E) - 2;
        FIELD(arg0, u16 *, 0x1E) = temp_v0_10;
        if ((s16)temp_v0_10 < 0) {
            FIELD(arg0, u16 *, 0x1E) = 0U;
            FIELD(arg0, u16 *, 0x20) = (u16) (FIELD(arg0, u16 *, 0x20) | 8);
        }
        temp_v0_11 = FIELD(arg0, u16 *, 0x1A) - 1;
        FIELD(arg0, u16 *, 0x1A) = temp_v0_11;
        if (((temp_v0_11 << 0x10) <= 0) && (FIELD(arg0, u16 *, 0x20) & 8)) {
            temp_v1_2 = FIELD(arg0, s32 *, 0x14);
            temp_v0_12 = FIELD(arg0, s32 *, 0x10);
            FIELD(arg0, u16 *, 0x1A) = 0xF0U;
            temp_v1_2 *= temp_v0_12;
            var_s3_2 = temp_v1_2 / 1000;
            temp_s0_2 = var_s3_2 % 10;
            temp_a1 = (var_s3_2 / 10) % 10;
            sp80 = temp_s0_2;
            sp82 = temp_a1;
            temp_a0_2 = ((var_s3_2 / 10) / 10) % 10;
            var_s1 = temp_s0_2;
            var_s1 += temp_a1;
            var_s1 += temp_a0_2;
            sp84 = temp_a0_2;
            if (var_s1 < 0xA) {
                if (temp_a0_2 > 0) {
                    var_s1 += 9;
                    sp84 = temp_a0_2 - 1;
                    sp82 = temp_a1 + 0xA;
                } else if (temp_a1 > 0) {
                    var_s1 += 9;
                    sp82 = temp_a1 - 1;
                    sp80 = temp_s0_2 + 0xA;
                }
            }
            var_s3_2 = 0;
            FIELD(arg0, u16 *, 0x20) = (u16) (FIELD(arg0, u16 *, 0x20) & 0xFFF7);
            sp10 = 1;
            sp14 = arg0;
            sp2D = 0;
            sp12 = 8;
            if (var_s1 > 0) {
                do {
                    do {
                        temp_v0_13 = func_80071494() % 3;
                        sp64 = temp_v0_13;
                        temp_a0_3 = (void *) (((s32) (temp_v0_13 << 0x10) >> 0xF) + (s32) local);
                        temp_v0_14 = FIELD(temp_a0_3, s16 *, 0x70);
                    } while (temp_v0_14 <= 0);
                    do { FIELD(temp_a0_3, s16 *, 0x70) = (s16) (temp_v0_14 - 1); } while (0);
                    sp68 = 0x03600000;
                    temp_s0_3 = (s32) (var_s3_2 << 0xC) / var_s1;
                    var_s3_2 += 1;
                    sp6C = 0x03600000;
                    sp70 = 0xFF800000;
                    sp74 = func_8006A3A4(temp_s0_3) * 0x140;
                    sp78 = func_8006A470(temp_s0_3) * 0x140;
                    sp7C = 0xFFF80000;
                    func_80529438(&sp10, &sp68);
                } while (var_s3_2 < var_s1);
            }
            FIELD(arg0, s16 *, 0x18) = 9;
        }
        break;
    }
    case 9:                                         /* switch 1 */
        temp_v0_15 = FIELD(arg0, u16 *, 0x1A) - 1;
        FIELD(arg0, u16 *, 0x1A) = temp_v0_15;
        if ((temp_v0_15 << 0x10) <= 0) {
            func_80232A08(D_80530588[0]);
            FIELD(arg0, s16 *, 0x18) = 0;
            var_v0_5 = FIELD(arg0, u16 *, 0x20) | 2;
            goto block_104;
        }
        break;
    case 10:                                        /* switch 1 */
        if (FIELD(arg0, s32 *, 0x14) != 0) {
            u32 var_v0_6;
            temp_v0_17 = (s16) FIELD(arg0, u16 *, 0x1E);
            var_v0_6 = D_80012BCC[0] + ((temp_v0_17 >= 2) ? 0x7D0 : 0x3E8);
            D_80012BC8[1] = var_v0_6;
        }
        temp_v0_16 = FIELD(arg0, u16 *, 0x1E) - 2;
        FIELD(arg0, u16 *, 0x1E) = temp_v0_16;
        if ((temp_v0_16 << 0x10) <= 0) {
            func_80232A08(D_80530588[0]);
            FIELD(arg0, u16 *, 0x1E) = 0U;
            FIELD(arg0, s16 *, 0x18) = 0;
            var_v0_5 = FIELD(arg0, u16 *, 0x20) | 0xA;
block_104:
            FIELD(arg0, u16 *, 0x20) = var_v0_5;
        }
        break;
    }
    FIELD(arg0, u16 *, 0x20) = (u16) (FIELD(arg0, u16 *, 0x20) & 0xFFFE);
}
