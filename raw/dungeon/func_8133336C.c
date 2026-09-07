#include "common.h"
typedef s32 M2C_UNK;

typedef struct DungeonEntry {
    u8 pad00[0xC];
    u16 flags;
    u8 pad0E[6];
} DungeonEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80164918[];
void func_80047784();
void func_800478B8();
s32 func_80069EF8();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
M2C_UNK func_8016AFC4(void *, void *, void *, void *);
M2C_UNK func_8016B230();
s32 func_8016B954();
M2C_UNK func_8016BAE0();
s32 func_8016BBC0();
void func_8016D4B8();
M2C_UNK func_8016D6F8();
void func_8016DAC0();
s32 func_801732A4();
extern u16 D_80013714;
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern DungeonEntry D_800E2970[];
extern u8 D_801739A0;
extern u8 D_801739A8;
extern u8 D_801739B0;
extern u8 D_801739B8;
extern M2C_UNK D_801739E0;
extern M2C_UNK D_801739E8;
extern M2C_UNK D_801739F0;
extern M2C_UNK D_801739F8;
extern M2C_UNK D_80173A00;
extern M2C_UNK D_80173A08;
extern M2C_UNK D_80173A10;
extern M2C_UNK D_80173A18;
extern u8 D_80173A50;
extern u8 D_80173A58;
extern M2C_UNK D_80173AC0;
extern M2C_UNK D_80173AC8;

void func_8016A36C(void *arg0, void *arg1, void *in2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    register void *arg2 = in2;
    M2C_UNK sp18;
    u8 *temp_s2;
    M2C_UNK *state;
    M2C_UNK *late_state;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    register u8 *var_a1 ASM_REG("$5");
    register unsigned long table_index ASM_REG("$2");
    u8 *late_table;
    u8 *late_current;
    s32 temp_a1;
    s32 temp_v0_3;
    s8 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    u32 clear_mask;
    s32 flag_one;

    state = &D_80083460;
    if (!(M2C_FIELD(state, u16 *, 2) & 0x1000)) {
        goto block_3;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    func_8016AFC4(arg0, arg1, arg2, arg3);
    if (M2C_FIELD(arg0, u8 *, 0xB0) != 1) {
        goto block_150;
    }
    M2C_FIELD(arg0, u8 *, 0xAD) = (u8) (M2C_FIELD(arg0, u8 *, 0xAD) + 1);
    M2C_FIELD(state, u16 *, 0xA) = (u16) (M2C_FIELD(state, u16 *, 0xA) + 1);
    return;
block_3:
    if (M2C_FIELD(arg0, u8 *, 0xB0) != 1) {
        goto block_6;
    }
    if (M2C_FIELD(arg0, u8 *, 0xAD) == 0) {
        goto block_6;
    }
    M2C_FIELD(state, u16 *, 0xA) = (u16) (M2C_FIELD(state, u16 *, 0xA) - M2C_FIELD(arg0, u8 *, 0xAD));
    M2C_FIELD(arg0, u8 *, 0xAD) = 0U;
block_6:
    if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
        goto block_19;
    }
    func_800AA79C(arg0, arg1, arg2, arg3);
    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg2);
    temp_a0 = M2C_FIELD(arg0, u8 *, 0xAC);
    if (temp_a0 == 0xE) {
        goto block_15;
    }
    if ((s32) temp_a0 >= 0xF) {
        goto block_11;
    }
    if (temp_a0 == 0xD) {
        goto block_13;
    }
    return;
block_11:
    if (temp_a0 == 0xF) {
        goto block_17;
    }
    return;
block_13:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == (M2C_UNK *)((u8 *)&D_80173AC0 + 8)) {
        goto block_150;
    }
    var_a1 = (M2C_UNK *)((u8 *)&D_80173A58 + 0x68);
    goto block_130;
block_15:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == (M2C_UNK *)((u8 *)&D_80173A58 + 0x70)) {
        goto block_150;
    }
    var_a1 = &D_80173AC0;
    goto block_130;
block_17:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80173AC8) {
        goto block_150;
    }
    var_a1 = (M2C_UNK *)((u8 *)&D_80173A00 + 0xC0);
    goto block_130;
block_19:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x200)) {
        goto block_36;
    }
    temp_a0_2 = M2C_FIELD(arg0, u8 *, 0xAC);
    if (temp_a0_2 == 0xE) {
        goto block_28;
    }
    if ((s32) temp_a0_2 >= 0xF) {
        goto block_24;
    }
    if (temp_a0_2 == 0xD) {
        goto block_26;
    }
    goto block_37;
block_24:
    if (temp_a0_2 == 0xF) {
        goto block_30;
    }
    goto block_37;
block_26:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80173AC8) {
        goto block_33;
    }
    clear_mask = 0xFFFB0000U;
    flag_one = 1;
    M2C_FIELD(arg0, u8 *, 0x9A) = temp_a0_2;
    goto block_32;
block_28:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80173AC8) {
        goto block_31;
    }
    goto block_35;
block_30:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80173AC8) {
        goto block_34;
    }
block_31:
    clear_mask = 0xFFFB0000U;
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
    flag_one = 1;
block_32:
    M2C_FIELD(arg0, s8 *, 0x9B) = (s8)flag_one;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & (clear_mask | 0xFFFFU));
    return;
block_33:
block_34:
block_35:
    if (func_800AA924(arg0, arg1, arg2, &D_80173AC0) != 0) {
        goto block_150;
    }
block_36:
block_37:
    if (D_80083462 & 0x2000) {
        goto block_77;
    }
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x100)) {
        goto block_40;
    }
    func_800AA258(arg0, arg1, arg2, arg3);
    return;
block_40:
    {
        register s32 dispatch_14 ASM_REG("$2") = 0xE;
        temp_v1 = M2C_FIELD(arg0, u8 *, 0x9A);
        if (temp_v1 == dispatch_14) {
            goto block_56;
        }
    }
    temp_v1 = M2C_FIELD(arg0, u8 *, 0xAC);
    if (temp_v1 == 1) {
        goto block_49;
    }
    if ((s32) temp_v1 >= 2) {
        goto block_45;
    }
    if (temp_v1 == 0) {
        goto block_48;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    goto block_55;
block_45:
    if (temp_v1 == 2) {
        goto block_50;
    }
    if (temp_v1 == 3) {
        goto block_51;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    goto block_55;
block_48:
    if (M2C_FIELD(arg2, u8 **, 0x2C) != &D_801739A0) {
        M2C_FIELD(arg2, u8 **, 0x2C) = &D_801739A0;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801739A0), 0);
    }
    goto block_54;
block_49:
    if (M2C_FIELD(arg2, u8 **, 0x2C) != &D_801739A8) {
        M2C_FIELD(arg2, u8 **, 0x2C) = &D_801739A8;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801739A8), 0);
    }
    goto block_54;
block_50:
    if (M2C_FIELD(arg2, u8 **, 0x2C) != &D_801739B0) {
        M2C_FIELD(arg2, u8 **, 0x2C) = &D_801739B0;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801739B0), 0);
    }
    goto block_54;
block_51:
    if (M2C_FIELD(arg2, u8 **, 0x2C) != &D_801739B8) {
        M2C_FIELD(arg2, u8 **, 0x2C) = &D_801739B8;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801739B8), 0);
    }
block_54:
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
block_55:
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA0) = (s16) ((func_80069EF8() & 0x1F) + 0xF);
block_56:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) {
        goto block_69;
    }
    temp_v1_2 = M2C_FIELD(arg0, u8 *, 0xAC);
    if (temp_v1_2 == 1) {
        goto block_65;
    }
    if ((s32) temp_v1_2 >= 2) {
        goto block_61;
    }
    if (temp_v1_2 == 0) {
        goto block_64;
    }
    goto block_69;
block_61:
    if (temp_v1_2 == 2) {
        goto block_66;
    }
    if (temp_v1_2 == 3) {
        goto block_67;
    }
    goto block_69;
block_64:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80173A00) != 0) {
        goto block_150;
    }
    goto block_69;
block_65:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80173A08) != 0) {
        goto block_150;
    }
    goto block_69;
block_66:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80173A10) != 0) {
        goto block_150;
    }
    goto block_69;
block_67:
    if (func_800AA6B4(arg0, arg1, arg2, &D_80173A18) != 0) {
        goto block_150;
    }
block_69:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
        goto block_71;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    func_8016D4B8(arg0, arg1, arg2, arg3);
    return;
block_71:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_77;
    }
    late_state = &D_80083460;
    if (M2C_FIELD(late_state, s32 *, 0xC) != arg3) {
        goto block_150;
    }
    if (M2C_FIELD(late_state, s32 *, 0x10) != 0) {
        goto block_150;
    }
    if ((s16) M2C_FIELD(late_state, u16 *, 0xA) >= 2) {
        goto block_150;
    }
    if (M2C_FIELD(late_state, u16 *, 2) & 8) {
        goto block_150;
    }
    M2C_FIELD(arg3, s32 *, 0x18) = 0;
    M2C_FIELD(late_state, s32 *, 0xC) = 0;
block_77:
    temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
    if (M2C_FIELD(arg3, s8 *, 0x6D) <= 0) {
        goto block_108;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
        goto block_94;
    }
    if (M2C_FIELD(arg2, u16 *, 0x24) == D_80082EA4) {
        goto block_107;
    }
    if (M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) {
        goto block_87;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_83;
    }
    if ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
        goto block_150;
    }
block_83:
    if (!(D_80013714 & 8)) {
        goto block_85;
    }
    func_801732A4(arg0, arg1, arg2);
    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    func_800A9A0C(arg3);
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    return;
block_85:
    if ((func_8016BBC0(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_150;
    }
    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
    M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_107;
    }
block_87:
    temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32) (temp_v0_3 - 1) >= 0xCU) {
        goto block_106;
    }
    (void)jt_keep; goto *D_80164918[(u32)((temp_v0_3) - 1)];
jt_c8:
    if ((func_8016B954(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_150;
    }
    func_8016BAE0(arg0, arg1, arg2, arg3);
    return;
jt_c9:
    func_8016D6F8(arg0, arg1, arg2, arg3);
    return;
jt_c10:
    func_8016DAC0(arg0, arg1, arg2, arg3);
    return;
jt_c5:
jt_c6:
jt_c7:
    {
        u8 *home = (u8 *)&D_80082E80;
        s32 angle = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(home, u8 *, 0x24), M2C_FIELD(home, u8 *, 0x25), &sp18);
        void *owner = D_800814A8;
        M2C_FIELD(arg3, s16 *, 0x2A) = (s16)angle;
        if (M2C_FIELD(owner, u8 *, 0x9A) == 0x11) {
            goto block_95;
        }
    }
jt_c12:
block_94:
    func_800A9A0C(arg3);
    return;
jt_c1:
jt_c2:
jt_c3:
block_95:
    temp_v1_3 = M2C_FIELD(arg0, u8 *, 0xAC);
    if (temp_v1_3 == 1) {
        goto block_103;
    }
    if ((s32) temp_v1_3 >= 2) {
        goto block_99;
    }
    if (temp_v1_3 == 0) {
        goto block_102;
    }
    return;
block_99:
    if (temp_v1_3 == 2) {
        goto block_104;
    }
    if (temp_v1_3 == 3) {
        goto block_105;
    }
    return;
block_102:
    func_800AAF00(arg0, arg1, arg2, &D_801739E0, &func_8016A36C);
    return;
block_103:
    func_800AAF00(arg0, arg1, arg2, &D_801739E8, &func_8016A36C);
    return;
block_104:
    func_800AAF00(arg0, arg1, arg2, &D_801739F0, &func_8016A36C);
    return;
block_105:
    func_800AAF00(arg0, arg1, arg2, &D_801739F8, &func_8016A36C);
    return;
jt_c4:
jt_c11:
block_106:
block_107:
    func_8016B230(arg0, arg1, arg2, arg3);
    return;
block_108:
    temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (temp_a1 & 0x2000) {
        goto block_116;
    }
    if (D_80013714 & 8) {
        goto block_116;
    }
    if (temp_v0 < 0) {
        goto block_112;
    }
    if (D_800E2970[temp_v0].flags & 2) {
        goto block_116;
    }
block_112:
    if (temp_a1 & 0x430) {
        goto block_116;
    }
    {
        u8 *home = (u8 *)&D_80082E80;
        if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(home, u8 *, 0x24), M2C_FIELD(home, u8 *, 0x25)) << 0x10) == 0) {
            goto block_115;
        }
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(home, u8 *, 0x24), M2C_FIELD(home, u8 *, 0x25), &sp18);
    }
block_115:
block_116:
    if (D_80083462 & 0x2000) {
        goto block_150;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x40) {
        goto block_150;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
        goto block_150;
    }
    ASM_SCHED_BARRIER();
    if (D_80013714 & 8) {
        goto block_150;
    }
    temp_v1_4 = M2C_FIELD(arg0, u8 *, 0xAC);
    if (temp_v1_4 == 1) {
        goto block_128;
    }
    if ((s32) temp_v1_4 >= 2) {
        goto block_124;
    }
    if (temp_v1_4 == 0) {
        goto block_127;
    }
    return;
block_124:
    if (temp_v1_4 == 2) {
        goto block_131;
    }
    if (temp_v1_4 == 3) {
        goto block_140;
    }
    return;
block_127:
    late_table = &D_801739A0;
    late_current = M2C_FIELD(arg2, u8 **, 0x2C);
    goto block_129;
block_128:
    late_current = M2C_FIELD(arg2, u8 **, 0x2C);
    ASM_CLOBBER("memory");
    late_table = &D_801739A8;
block_129:
    var_a1 = late_table;
    if (late_current == var_a1) {
        goto block_150;
    }
block_130:
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
    table_index = ((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7;
    table_index += (unsigned long)var_a1;
    func_80047784(arg2, *(u8 *)table_index, 0);
    return;
block_131:
    temp_v1_5 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
    if (temp_v1_5 == &D_801739B0) {
        goto block_135;
    }
    if (temp_v1_5 == &D_80173A50) {
        goto block_134;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801739B0;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801739B0), 0);
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA0) = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
block_134:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_801739B0) {
        goto block_137;
    }
block_135:
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x9E);
    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v0_4 + 1);
    if ((s16) temp_v0_4 < M2C_FIELD(arg0, s16 *, 0xA0)) {
        goto block_137;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173A50;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80173A50), 0);
    func_800478B8(arg2);
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
block_137:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80173A50) {
        goto block_150;
    }
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x9E);
    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v0_5 + 1);
    if ((s16) temp_v0_5 < 0x12) {
        goto block_150;
    }
    var_a1 = &D_801739B0;
    goto block_149;
block_140:
    temp_v1_6 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
    temp_s2 = &D_801739B8;
    if (temp_v1_6 == temp_s2) {
        goto block_144;
    }
    if (temp_v1_6 == &D_80173A58) {
        goto block_143;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = temp_s2;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + temp_s2), 0);
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA0) = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
block_143:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != temp_s2) {
        goto block_146;
    }
block_144:
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x9E);
    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v0_6 + 1);
    if ((s16) temp_v0_6 < M2C_FIELD(arg0, s16 *, 0xA0)) {
        goto block_146;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173A58;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80173A58), 0);
    func_800478B8(arg2);
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
block_146:
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80173A58) {
        goto block_150;
    }
    temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x9E);
    M2C_FIELD(arg0, u16 *, 0x9E) = (u16) (temp_v0_7 + 1);
    if ((s16) temp_v0_7 < 0x12) {
        goto block_150;
    }
    var_a1 = &D_801739B8;
block_149:
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = var_a1;
    table_index = ((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7;
    table_index += (unsigned long)var_a1;
    func_80047784(arg2, *(u8 *)table_index, 0);
    M2C_FIELD(arg0, u16 *, 0x9E) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA0) = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
block_150:
    return;
}
