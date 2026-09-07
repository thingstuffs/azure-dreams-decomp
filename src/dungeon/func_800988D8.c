#include "common.h"
#include "m2c_compat.h"

extern void *D_80088CB8[];
void func_8009DF0C();
s32 func_800A2C34();
M2C_UNK func_800A634C();
M2C_UNK func_800A67F4();
extern void func_8009E770(void) __attribute__((noreturn));
extern void func_8009E728(void) __attribute__((noreturn));
extern s16 D_80013630[4];
extern M2C_UNK D_8001363C;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083160;
extern M2C_UNK D_800E296C;
extern void *D_800E3D7C;

void func_8009E038(void *arg0, void *arg1, void *arg2, M2C_UNK *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c16, &&jt_c32, &&jt_c48 };
    s32 var_a1;
    M2C_UNK *var_a3;
    M2C_UNK *var_s3;
    s16 temp_a0;
    s16 temp_a0_3;
    s16 temp_v0_10;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s32 temp_v1;
    register s16 temp_v1_10 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_state_1e;
    s32 temp_a0_4;
    s32 temp_flags;
    s32 temp_flags_cleared;
    s32 temp_state;
    s32 var_a1_2;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v0_11;
    u16 temp_v0_12;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 temp_v1_4;
    u16 temp_v1_5;
    u16 temp_v1_6;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 temp_v1_9;
    u8 temp_v1_2;
    u8 temp_v1_3;
    void *temp_s1;
    M2C_UNK *var_dpage;
    M2C_UNK *var_epage;
    M2C_UNK *var_v0_base;
    s32 var_a2;
    register s32 shared_flags ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 reset_flags ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */

    temp_s1 = arg2;
    var_s3 = &D_80083160;
    if (!(M2C_FIELD(&D_800E296C, s32 *, 0) & 0x2000)) {
        goto block_3;
    }
    if (M2C_FIELD(arg0, s16 *, 0x1A) >= 0x20) {
        goto block_3;
    }
    M2C_FIELD(arg0, s16 *, 0x1A) = 0x20;
block_3:
    temp_flags = M2C_FIELD(&D_800E296C, s32 *, 0);
    if (!(temp_flags & 0x800000)) {
        goto block_7;
    }
    temp_state = M2C_FIELD(arg0, s16 *, 0x1A);
    temp_flags_cleared = temp_flags & ~0x2000;
    (*(s32 *)&D_800E296C) = temp_flags_cleared;
    if (temp_state < 2) {
        goto block_6;
    }
    M2C_FIELD(arg0, s16 *, 0x1A) = 0;
    M2C_FIELD(arg0, s16 *, 0x1C) = 8;
block_6:
    reset_flags = M2C_FIELD(&D_800E296C, s32 *, 0);
    M2C_FIELD(arg0, u16 *, 0x2C) = 0U;
    (*(s32 *)&D_800E296C) = reset_flags & 0xFEFFFFFF;
    goto block_10;
block_7:
    if ((u32) ((u16) M2C_FIELD(arg0, s16 *, 0x1A) - 0x20) >= 0x10U) {
        goto block_10;
    }
    if (M2C_FIELD(&D_800E296C, s32 *, 0) & 0x2000) {
        goto block_10;
    }
    M2C_FIELD(arg0, s16 *, 0x1A) = 0x30;
block_10:
    if (M2C_FIELD(arg0, s16 *, 0x1A) != 0) {
        goto block_12;
    }
    if (!(M2C_FIELD(D_800E3D7C, s32 *, 0x1C) & 0x10)) {
        goto block_13;
    }
block_12:
    reset_flags = M2C_FIELD(&D_800E296C, s32 *, 0);
    M2C_FIELD(arg0, u16 *, 0x2C) = 0U;
    (*(s32 *)&D_800E296C) = reset_flags & 0xFEFFFFFF;
block_13:
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x1A);
    if ((u32) temp_v1 >= 0x31U) {
        goto block_46;
    }
    (void)jt_keep; goto *D_80088CB8[(u32)(temp_v1)];
jt_c0:
    if (M2C_FIELD(&D_800E296C, s32 *, 0) & 0x800000) {
        goto block_20;
    }
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x2C) + 1;
    M2C_FIELD(arg0, u16 *, 0x2C) = temp_v0;
    if ((s16) temp_v0 != 0x1F) {
        goto block_18;
    }
    (*(s32 *)&D_800E296C) = (s32) (M2C_FIELD(&D_800E296C, s32 *, 0) | 0x01000000);
    func_800A634C(0);
    goto block_20;
block_18:
    if ((s16) temp_v0 < 0x20) {
        goto block_20;
    }
    M2C_FIELD(arg0, u16 *, 0x2C) = 0x20U;
block_20:
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x1C);
    if (temp_a0 <= 0) {
        goto block_22;
    }
    temp_v1_2 = M2C_FIELD(temp_s1, u8 *, 0xE);
    temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / temp_a0);
    M2C_FIELD(temp_s1, u8 *, 0xE) = temp_v1_3;
    M2C_FIELD(temp_s1, u8 *, 0xD) = temp_v1_3;
    M2C_FIELD(temp_s1, u8 *, 0xC) = temp_v1_3;
    temp_v1_4 = M2C_FIELD(temp_s1, u16 *, 0x1E);
    temp_a0_2 = M2C_FIELD(temp_s1, u16 *, 0x20);
    temp_v1_5 = temp_v1_4 + ((s32) (0x3000 - temp_v1_4) / (s16) M2C_FIELD(arg0, s16 *, 0x1C));
    M2C_FIELD(temp_s1, u16 *, 0x1E) = temp_v1_5;
    M2C_FIELD(temp_s1, u16 *, 0x1C) = temp_v1_5;
    temp_v0_2 = M2C_FIELD(temp_s1, u16 *, 0x22);
    M2C_FIELD(temp_s1, u16 *, 0x20) = (u16) (temp_a0_2 + ((s32) (0x20 - temp_a0_2) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(temp_s1, u16 *, 0x22) = (u16) (temp_v0_2 + ((s32) (0x20 - temp_v0_2) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) (0xA0 - M2C_FIELD(arg1, s16 *, 2)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (0x78 - M2C_FIELD(arg1, s16 *, 6)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg0, s16 *, 4) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 4) + ((s32) (0 - M2C_FIELD(arg0, s16 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg0, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 6) + ((s32) (0 - M2C_FIELD(arg0, s16 *, 6)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg0, s16 *, 8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 8) + ((s32) (0x140 - M2C_FIELD(arg0, s16 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + ((s32) (0xE0 - M2C_FIELD(arg0, s16 *, 0xA)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
block_22:
    temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x1C) - 1;
    M2C_FIELD(arg0, s16 *, 0x1C) = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_46;
    }
    M2C_FIELD(arg1, s16 *, 2) = 0xA0;
    M2C_FIELD(arg1, s16 *, 6) = 0x78;
    M2C_FIELD(temp_s1, u16 *, 0x1E) = 0x3000U;
    M2C_FIELD(temp_s1, u16 *, 0x1C) = 0x3000U;
    M2C_FIELD(temp_s1, u16 *, 0x20) = 0x20U;
    M2C_FIELD(temp_s1, u16 *, 0x22) = 0x20U;
    M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
    M2C_FIELD(arg0, s16 *, 8) = 0x140;
    M2C_FIELD(arg0, s16 *, 0xA) = 0xE0;
    reset_flags = M2C_FIELD(&D_800E296C, s32 *, 0);
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    if (!(reset_flags & 0x800000)) {
        goto block_25;
    }
    M2C_FIELD(arg0, s16 *, 0x1C) = 0x1E;
    M2C_FIELD(arg0, s16 *, 0x1A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x1A) + 1);
    func_8009E770();
block_25:
    if (M2C_FIELD(var_s3, s32 *, 8) & 0x100) {
        goto block_46;
    }
    M2C_FIELD(arg0, s16 *, 0x1C) = 4;
    M2C_FIELD(arg0, s16 *, 0x1A) = 0x10;
    func_8009E770();
jt_c1:
    temp_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0x1C) - 1;
    M2C_FIELD(arg0, s16 *, 0x1C) = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_46;
    }
    var_a1_2 = 0xFF7FFFFF;
    shared_flags = 8;
    var_epage = (M2C_UNK *)0x800E0000;
    M2C_FIELD(arg0, s16 *, 0x1C) = shared_flags;
    shared_flags = M2C_FIELD(var_epage, s32 *, 0x296C);
    M2C_FIELD(arg0, s16 *, 0x1A) = 0x10;
    goto block_shared_flags;
jt_c16:
    temp_a0_3 = M2C_FIELD(arg0, s16 *, 0x1C);
    if (temp_a0_3 == 0) {
        goto block_32;
    }
    temp_v1_7 = ((s32) (M2C_FIELD(arg0, s16 *, 0x1E) - M2C_FIELD(temp_s1, u16 *, 0x1E)) / temp_a0_3) + M2C_FIELD(temp_s1, u16 *, 0x1E);
    M2C_FIELD(temp_s1, u16 *, 0x1E) = temp_v1_7;
    M2C_FIELD(temp_s1, u16 *, 0x1C) = temp_v1_7;
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) (M2C_FIELD(arg0, s16 *, 0x14) - M2C_FIELD(arg1, s16 *, 2)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (M2C_FIELD(arg0, s16 *, 0x16) - M2C_FIELD(arg1, s16 *, 6)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    var_a3 = &D_80082E80;
    M2C_FIELD(temp_s1, u16 *, 0x20) = (u16) (((s32) (M2C_FIELD(var_a3, u8 *, 0x24) - M2C_FIELD(temp_s1, u16 *, 0x20)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)) + M2C_FIELD(temp_s1, u16 *, 0x20));
    M2C_FIELD(temp_s1, u16 *, 0x22) = (u16) (((s32) (M2C_FIELD(var_a3, u8 *, 0x25) - M2C_FIELD(temp_s1, u16 *, 0x22)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)) + M2C_FIELD(temp_s1, u16 *, 0x22));
    var_a2 = (s32) (M2C_FIELD(arg0, s16 *, 0xC) - M2C_FIELD(arg0, s16 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C);
    M2C_FIELD(arg0, s16 *, 4) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 4) + var_a2);
    var_a1 = (s32) (M2C_FIELD(arg0, s16 *, 0xE) - M2C_FIELD(arg0, s16 *, 6)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C);
    M2C_FIELD(arg0, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 6) + var_a1);
    M2C_FIELD(arg0, s16 *, 8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 8) + ((s32) (M2C_FIELD(arg0, s16 *, 0x10) - M2C_FIELD(arg0, s16 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C)));
    temp_a0_4 = (s32) (M2C_FIELD(arg0, s16 *, 0x12) - M2C_FIELD(arg0, s16 *, 0xA)) / (s16) M2C_FIELD(arg0, s16 *, 0x1C);
    temp_v1_10 = (u16) M2C_FIELD(arg0, s16 *, 0x1C) - 1;
    M2C_FIELD(arg0, s16 *, 0x1C) = temp_v1_10;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + temp_a0_4);
    if ((temp_v1_10 << 0x10) > 0) {
        goto block_33;
    }
    M2C_FIELD(arg1, s16 *, 2) = (s16) (u16) M2C_FIELD(arg0, s16 *, 0x14);
    M2C_FIELD(arg1, s16 *, 6) = (s16) (u16) M2C_FIELD(arg0, s16 *, 0x16);
    temp_v0_5 = (u16) M2C_FIELD(arg0, s16 *, 0x1E);
    M2C_FIELD(temp_s1, u16 *, 0x1E) = temp_v0_5;
    M2C_FIELD(temp_s1, u16 *, 0x1C) = temp_v0_5;
    M2C_FIELD(temp_s1, s16 *, 0x20) = (s16) M2C_FIELD(&D_80082E80, u8 *, 0x24);
    M2C_FIELD(temp_s1, s16 *, 0x22) = (s16) M2C_FIELD(&D_80082E80, u8 *, 0x25);
    temp_v0_6 = (u16) M2C_FIELD(arg0, s16 *, 0xC);
    var_dpage = (M2C_UNK *)0x80010000;
    M2C_FIELD(arg0, s16 *, 4) = (s16) temp_v0_6;
    M2C_FIELD(var_dpage, s16 *, 0x3630) = temp_v0_6;
    temp_v0_7 = (u16) M2C_FIELD(arg0, s16 *, 0xE);
    M2C_FIELD(arg0, s16 *, 6) = (s16) temp_v0_7;
    M2C_FIELD(var_dpage, s16 *, 0x3632) = temp_v0_7;
    temp_v0_8 = (u16) M2C_FIELD(arg0, s16 *, 0x10);
    M2C_FIELD(arg0, s16 *, 8) = (s16) temp_v0_8;
    M2C_FIELD(var_dpage, s16 *, 0x3634) = temp_v0_8;
    temp_v0_9 = (u16) M2C_FIELD(arg0, s16 *, 0x12);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) temp_v0_9;
    M2C_FIELD(var_dpage, s16 *, 0x3636) = temp_v0_9;
    goto block_33;
block_32:
    var_v0_base = &D_80082E80;
    M2C_FIELD(temp_s1, s16 *, 0x20) = (s16) M2C_FIELD(var_v0_base, u8 *, 0x24);
    M2C_FIELD(temp_s1, s16 *, 0x22) = (s16) M2C_FIELD(var_v0_base, u8 *, 0x25);
block_33:
    if (!(M2C_FIELD(var_s3, s32 *, 8) & 0x10)) {
        goto block_39;
    }
    if (!(M2C_FIELD(var_s3, s32 *, 0x10) & 8)) {
        goto block_39;
    }
    temp_state_1e = M2C_FIELD(arg0, s16 *, 0x1E);
    if (temp_state_1e >= 0x5000) {
        goto block_37;
    }
    temp_v0_10 = (u16) M2C_FIELD(arg0, s16 *, 0x1E) + 0x1000;
    M2C_FIELD(arg0, s16 *, 0x1E) = temp_v0_10;
    *(s32 *)0x8001363C = (s32) temp_v0_10;
    goto block_38;
block_37:
    M2C_FIELD(arg0, s16 *, 0x1E) = 0;
    *(s32 *)0x8001363C = 0;
block_38:
    M2C_FIELD(arg0, s16 *, 0x1C) = 4;
block_39:
    if (!(M2C_FIELD(var_s3, s32 *, 8) & 0x100)) {
        goto block_46;
    }
    if ((func_800A2C34(0) << 0x10) != 0) {
        goto block_46;
    }
    func_800A67F4();
    var_a1_2 = 0xFEFFFFFF;
    ASM_KEEP(var_a1_2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_epage = (M2C_UNK *)0x800E0000;
    shared_flags = M2C_FIELD(var_epage, s32 *, 0x296C);
    M2C_FIELD(arg0, u16 *, 0x2C) = 0U;
    M2C_FIELD(arg0, s16 *, 0x1A) = 0;
    M2C_FIELD(arg0, s16 *, 0x1C) = 1;
block_shared_flags:
    M2C_FIELD(var_epage, s32 *, 0x296C) = shared_flags & var_a1_2;
    goto block_46;
jt_c32:
    temp_v0_11 = M2C_FIELD(temp_s1, u16 *, 0x1E);
    temp_v0_12 = temp_v0_11 - (temp_v0_11 >> 2);
    M2C_FIELD(temp_s1, u16 *, 0x1E) = temp_v0_12;
    if ((u32) (temp_v0_12 & 0xFFFF) >= 0x100U) {
        goto block_46;
    }
    M2C_FIELD(temp_s1, u16 *, 0x1E) = 0U;
    goto block_46;
jt_c48:
    M2C_FIELD(arg0, s16 *, 0x1A) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x1C) = 4;
block_46:
    func_8009DF0C(arg0);
    return;
}
