#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009D8A4();                            /* extern */
M2C_UNK func_800A56E0(M2C_UNK, s32 *);              /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
s32 func_800D5F80(void *, void *, void *);          /* extern */
extern M2C_UNK D_800E2468;
extern s32 D_800E296C;

void func_80162C64(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a0_4;
    s32 temp_a0_2;
    s32 temp_s1;
    s32 temp_v0_12;
    s32 temp_v0_2;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    u16 temp_a0;
    u16 temp_s1_2;
    u16 temp_v0;
    u16 temp_v0_10;
    u16 temp_v0_11;
    u16 temp_v0_14;
    u16 temp_v0_16;
    u16 temp_v0_17;
    u16 temp_v0_18;
    u16 temp_v0_19;
    u16 temp_v0_20;
    u16 temp_v0_3;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_9;
    u16 temp_v1_6;
    u8 temp_v0_15;
    u8 temp_v0_4;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_7;
    u8 var_v0;
    void *temp_a0_3;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a2;
    void *temp_a2_2;
    void *temp_a2_3;
    void *temp_a2_4;
    void *temp_v0_13;
    void *var_a0;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    temp_a0 = M2C_FIELD(arg3, u16 *, 0x2A);
    temp_s1 = (temp_a0 >> 9) & 7;
    if (M2C_FIELD(arg0, u8 *, 0xB3) != 0) {
        goto block_37;
    }
    temp_v1 = M2C_FIELD(arg0, u8 *, 0xB1);
    if (temp_v1 == 0) {
        goto block_4;
    }
    if (temp_v1 == 1) {
        goto block_25;
    }
    goto block_36;
block_4:
    temp_v1_2 = M2C_FIELD(arg0, u8 *, 0xB2);
    if (temp_v1_2 == 1) {
        goto block_20;
    }
    if ((s32) temp_v1_2 >= 2) {
        goto block_8;
    }
    if (temp_v1_2 == 0) {
        goto block_10;
    }
    goto block_36;
block_8:
    temp_v0 = temp_a0 + 0x200;
    if (temp_v1_2 == 2) {
        goto block_22;
    }
    goto block_36;
block_10:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        goto block_29;
    }
    temp_v0_2 = temp_a0 & 0x3FF;
    if ((u8) M2C_FIELD(arg0, u8 *, 0xB4) < 7U) {
        goto block_14;
    }
    if (temp_v0_2 != 0) {
        goto block_19;
    }
    M2C_FIELD(arg0, u8 *, 0xB1) = 1U;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    goto block_36;
block_14:
    if (temp_v0_2 != 0) {
        goto block_19;
    }
    if ((func_800D5F80(arg1, arg3) << 0x10) == 0) {
        goto block_18;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x1EU;
    temp_a0_2 = M2C_FIELD(arg0, s32 *, 0xAC);
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB3) = (u8) (M2C_FIELD(arg0, u8 *, 0xB3) + 1);
    if (temp_a0_2 == 0) {
        goto block_36;
    }
    temp_a2 = temp_a0_2 + 0x20;
    M2C_FIELD(temp_a2, u16 *, 0x62) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_a2, s16 *, 0x68) = 0;
    M2C_FIELD(temp_a2, s16 *, 0x66) = 0;
    M2C_FIELD(temp_a2, u16 *, 0x64) = (u16) M2C_FIELD(arg1, u16 *, 6);
    goto block_36;
block_18:
block_19:
    M2C_FIELD(arg0, u8 *, 0xB2) = 2U;
    goto block_36;
block_20:
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_3 - 1);
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_36;
    }
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    goto block_36;
block_22:
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_v0;
    if ((s16) temp_v0 < 0x1000) {
        goto block_24;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = 0U;
block_24:
    M2C_FIELD(arg0, u8 *, 0xB2) = 1U;
    M2C_FIELD(arg0, u16 *, 0x96) = 1U;
    M2C_FIELD(arg0, u8 *, 0xB4) = (u8) (M2C_FIELD(arg0, u8 *, 0xB4) + 1);
    goto block_36;
block_25:
    temp_v0_4 = M2C_FIELD(arg0, u8 *, 0xB2);
    if (temp_v0_4 == 0) {
        goto block_28;
    }
    if (temp_v0_4 == temp_v1) {
        goto block_33;
    }
    goto block_36;
block_28:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_30;
    }
block_29:
    M2C_FIELD(arg0, u8 *, 0xB3) = 2U;
    goto block_36;
block_30:
    if ((func_800D5F80(arg1, arg3) << 0x10) == 0) {
        goto block_32;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x1EU;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB3) = (u8) (M2C_FIELD(arg0, u8 *, 0xB3) + 1);
    goto block_36;
block_32:
    M2C_FIELD(arg0, u16 *, 0x96) = 3U;
    M2C_FIELD(arg0, u8 *, 0xB2) = (u8) (M2C_FIELD(arg0, u8 *, 0xB2) + 1);
block_33:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_5 - 1);
    if ((temp_v0_5 << 0x10) > 0) {
        goto block_35;
    }
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
block_35:
    temp_a0_3 = (temp_s1 * 4) + &D_800E2468;
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + (M2C_FIELD(temp_a0_3, s16 *, 0) * 0x10));
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + (M2C_FIELD(temp_a0_3, s16 *, 2) * 0x10));
block_36:
block_37:
    if (M2C_FIELD(arg0, u8 *, 0xB3) != 1) {
        goto block_100;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_40;
    }
    M2C_FIELD(arg0, u8 *, 0xB3) = 2U;
    goto block_99;
block_40:
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0xA8);
    M2C_FIELD(arg0, u16 *, 0xA8) = (u16) (temp_v0_6 + 1);
    if ((s16) temp_v0_6 >= 0x12C) {
        goto block_97;
    }
    temp_v0_7 = M2C_FIELD(arg0, s32 *, 0xAC);
    if (temp_v0_7 == 0) {
        goto block_53;
    }
    temp_a2_2 = temp_v0_7 + 0x20;
    if (M2C_FIELD(temp_a2_2, s16 *, 0x66) != 0) {
        goto block_44;
    }
    if (M2C_FIELD(temp_a2_2, s16 *, 0x68) == 0) {
        goto block_46;
    }
block_44:
    if (M2C_FIELD(temp_a2_2, s16 *, 0x62) != (s16) M2C_FIELD(arg1, u16 *, 2)) {
        goto block_46;
    }
    if (M2C_FIELD(temp_a2_2, s16 *, 0x64) == (s16) M2C_FIELD(arg1, u16 *, 6)) {
        goto block_98;
    }
block_46:
    temp_v0_8 = M2C_FIELD(arg0, s32 *, 0xAC);
    if (temp_v0_8 == 0) {
        goto block_53;
    }
    temp_a2_3 = temp_v0_8 + 0x20;
    temp_a0_4 = M2C_FIELD(temp_a2_3, s16 *, 0x66);
    var_a1 = 2;
    if (temp_a0_4 != 0) {
        goto block_49;
    }
    if (M2C_FIELD(temp_a2_3, s16 *, 0x68) == 0) {
        goto block_53;
    }
block_49:
    var_a0 = temp_v0_8 + 0x28;
loop_50:
    if (temp_a0_4 != M2C_FIELD(var_a0, s16 *, 0x62)) {
        goto block_52;
    }
    if (M2C_FIELD(temp_a2_3, s16 *, 0x68) == M2C_FIELD(var_a0, s16 *, 0x64)) {
        goto block_98;
    }
block_52:
    var_a1 += 1;
    var_a0 += 4;
    if (var_a1 < 6) {
        goto loop_50;
    }
block_53:
    temp_v1_3 = M2C_FIELD(arg0, u8 *, 0xB1);
    if (temp_v1_3 == 1) {
        goto block_64;
    }
    if ((s32) temp_v1_3 >= 2) {
        goto block_57;
    }
    if (temp_v1_3 == 0) {
        goto block_61;
    }
    goto block_99;
block_57:
    if (temp_v1_3 == 2) {
        goto block_73;
    }
    if (temp_v1_3 == 3) {
        goto block_87;
    }
    goto block_99;
block_60:
block_61:
    if ((func_800D5F80(arg1, arg3) << 0x10) != 0) {
        goto block_63;
    }
    M2C_FIELD(arg0, u8 *, 0xB1) = 2U;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    goto block_73;
block_63:
    M2C_FIELD(arg0, u8 *, 0xB1) = 1U;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
block_64:
    temp_v1_4 = M2C_FIELD(arg0, u8 *, 0xB2);
    if (temp_v1_4 == 0) {
        goto block_67;
    }
    if (temp_v1_4 == 1) {
        goto block_69;
    }
    goto block_99;
block_67:
    temp_v0_9 = M2C_FIELD(arg3, u16 *, 0x2A) + 0x200;
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_v0_9;
    if ((s16) temp_v0_9 < 0x1000) {
        goto block_92;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = 0U;
    goto block_92;
block_69:
    temp_v0_10 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_10 - 1);
    if ((temp_v0_10 << 0x10) > 0) {
        goto block_99;
    }
    if (!(M2C_FIELD(arg3, u16 *, 0x2A) & 0x3FF)) {
        goto block_72;
    }
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    goto block_67;
block_72:
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    goto block_60;
block_73:
    temp_v1_5 = M2C_FIELD(arg0, u8 *, 0xB2);
    if (temp_v1_5 == 0) {
        goto block_76;
    }
    if (temp_v1_5 == 1) {
        goto block_77;
    }
    goto block_99;
block_76:
    M2C_FIELD(arg0, u8 *, 0xB2) = 1U;
    M2C_FIELD(arg0, u16 *, 0x96) = 3U;
block_77:
    temp_a0_5 = (temp_s1 * 4) + &D_800E2468;
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + (M2C_FIELD(temp_a0_5, s16 *, 0) * 0x10));
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + (M2C_FIELD(temp_a0_5, s16 *, 2) * 0x10));
    temp_v0_11 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_11 - 1);
    if ((temp_v0_11 << 0x10) > 0) {
        goto block_99;
    }
    temp_v0_12 = M2C_FIELD(arg0, s32 *, 0xAC);
    temp_a2_4 = temp_v0_12 + 0x20;
    if (temp_v0_12 == 0) {
        goto block_82;
    }
    var_a1_2 = 5;
    var_a0_2 = 5 * 4;
loop_80:
    var_a1_2 -= 1;
    temp_v0_13 = temp_a2_4 + (var_a1_2 * 4);
    temp_a0_6 = temp_a2_4 + var_a0_2;
    M2C_FIELD(temp_a0_6, u16 *, 0x62) = (u16) M2C_FIELD(temp_v0_13, u16 *, 0x62);
    M2C_FIELD(temp_a0_6, u16 *, 0x64) = (u16) M2C_FIELD(temp_v0_13, u16 *, 0x64);
    var_a0_2 = var_a1_2 * 4;
    if (var_a1_2 >= 2) {
        goto loop_80;
    }
    M2C_FIELD(temp_a2_4, u16 *, 0x66) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_a2_4, u16 *, 0x68) = (u16) M2C_FIELD(arg1, u16 *, 6);
block_82:
    temp_s1_2 = M2C_FIELD(arg3, u16 *, 0x2A);
    temp_v0_14 = temp_s1_2 - 0x400;
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_v0_14;
    if (!(temp_v0_14 & 0x8000)) {
        goto block_84;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (temp_s1_2 + 0xC00);
block_84:
    if ((func_800D5F80(arg1, arg3, temp_a2_4) << 0x10) == 0) {
        goto block_86;
    }
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_s1_2;
    goto block_99;
block_86:
    M2C_FIELD(arg0, u8 *, 0xB1) = 3U;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_s1_2;
    goto block_99;
block_87:
    temp_v0_15 = M2C_FIELD(arg0, u8 *, 0xB2);
    if (temp_v0_15 == 0) {
        goto block_90;
    }
    if (temp_v0_15 == 1) {
        goto block_93;
    }
    goto block_99;
block_90:
    temp_v1_6 = M2C_FIELD(arg3, u16 *, 0x2A);
    temp_v0_16 = temp_v1_6 - 0x200;
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_v0_16;
    if (!(temp_v0_16 & 0x8000)) {
        goto block_92;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (temp_v1_6 + 0xE00);
block_92:
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0xB2) = (u8) (M2C_FIELD(arg0, u8 *, 0xB2) + 1);
    goto block_99;
block_93:
    temp_v0_17 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_17 - 1);
    if ((temp_v0_17 << 0x10) > 0) {
        goto block_99;
    }
    if (!(M2C_FIELD(arg3, u16 *, 0x2A) & 0x3FF)) {
        goto block_96;
    }
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    goto block_90;
block_96:
    M2C_FIELD(arg0, u8 *, 0xB1) = 2U;
    M2C_FIELD(arg0, u8 *, 0xB2) = 0U;
    goto block_73;
block_97:
block_98:
    M2C_FIELD(arg0, u8 *, 0xB3) = 3U;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    goto block_102;
block_99:
block_100:
    if (M2C_FIELD(arg0, u8 *, 0xB3) != 2) {
        goto block_102;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) & 0xFC00);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
    M2C_FIELD(arg0, s16 *, 0x92) = 0;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA2) = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F, &D_800E296C);
block_102:
    if (M2C_FIELD(arg0, u8 *, 0xB3) != 3) {
        goto block_114;
    }
    temp_v1_7 = M2C_FIELD(arg0, u8 *, 0xB1);
    if (temp_v1_7 >= 5U) {
        goto block_114;
    }
    switch (temp_v1_7);                             /* jump table: jtbl_8015E888 */
case 0:
    M2C_FIELD(arg0, u16 *, 0x96) = 0xAU;
    M2C_FIELD(arg0, u8 *, 0xB1) = (u8) (M2C_FIELD(arg0, u8 *, 0xB1) + 1);
case 1:
    temp_v0_18 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_18 - 1);
    if ((temp_v0_18 << 0x10) > 0) {
        goto block_114;
    }
    var_v0 = M2C_FIELD(arg0, u8 *, 0xB1) + 1;
    goto block_111;
case 2:
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
    goto block_110;
case 3:
    temp_v0_19 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_19 - 1);
    if ((temp_v0_19 << 0x10) > 0) {
        goto block_114;
    }
block_110:
    M2C_FIELD(arg0, u16 *, 0x96) = 0x14U;
    var_v0 = M2C_FIELD(arg0, u8 *, 0xB1) + 1;
block_111:
    M2C_FIELD(arg0, u8 *, 0xB1) = var_v0;
    goto block_114;
case 4:
    temp_v0_20 = M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_20 - 1);
    if ((temp_v0_20 << 0x10) > 0) {
        goto block_114;
    }
    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) & 0xFC00);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
    M2C_FIELD(arg0, s16 *, 0x92) = 0;
    M2C_FIELD(arg0, u8 *, 0xB1) = 0U;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA2) = 0;
    func_8009D8A4();
    D_800E296C |= 0x800000;
    func_800A56E0(0x80F, &D_800E296C);
block_114:
    M2C_FIELD(arg3, s16 *, 0x88) = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x20));
    return;
}
