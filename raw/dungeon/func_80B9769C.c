#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    u8 pad_00[0x24];
    u8 x;
    u8 y;
} RefPosition;

typedef struct {
    u8 pad_00[0xC];
    u16 flags;
    u8 pad_0E[6];
} TerrainEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170808[];
void func_80047784();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s16 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
s32 func_800AAB10();
M2C_UNK func_800AAF00();
M2C_UNK func_801713B8() __attribute__((noreturn));
M2C_UNK func_80171410();
M2C_UNK func_80171B58();
s32 func_80171E00();
M2C_UNK func_80171FC4();
M2C_UNK func_801737C4();
s32 func_80173A08();
M2C_UNK func_801747D0();
extern void *D_800814A8;
extern RefPosition D_80082E80;
extern u16 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern TerrainEntry D_800E2970[];
extern u8 D_80174EE0[];
extern M2C_UNK D_80174EF8;
extern M2C_UNK D_80174F00;
extern M2C_UNK D_80174F08;
extern M2C_UNK D_80174F10;

void func_80170E9C(void *in0, M2C_UNK in1, void *in2, void *in3) {
    static void *const jt_keep[] = { &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12 };
    void *arg0 = in0;
    M2C_UNK arg1 = in1;
    void *arg2 = in2;
    M2C_UNK sp18;
    M2C_UNK *var_v0;
    void *case_entity;
    RefPosition *case_ref;
    RefPosition *late_ref;
    s16 case_floor;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v1;
    s8 temp_v0;
    u8 current_mode;
    u16 temp_v0_2;
    register void *arg3 ASM_REG("$18") = in3;
    register u32 mode_14 ASM_REG("$20");

    if (!(D_80083462 & 0x1000)) {
        goto block_3;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xEU;
    func_80171B58(arg0);
    return;
block_3:
    ASM_CLOBBER("$7");
    if (M2C_FIELD(arg3, u8 *, 0x25) != 0) {
        goto block_7;
    }
    func_800AA79C(arg0, arg1, arg2, arg3);
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == &D_80174F00) {
        goto block_63;
    }
    {
        register M2C_UNK *dead_a1 ASM_REG("$5") = &D_80174EF8;
        ASM_TAILSLOT_PIN(dead_a1);
        func_801713B8();
    }
    return;
block_7:
    temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (!(temp_v1 & 0x200)) {
        goto block_14;
    }
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80174F00) {
        goto block_11;
    }
    M2C_FIELD(arg0, u8 *, 0x9A) = 0xDU;
    M2C_FIELD(arg0, s8 *, 0x9B) = 1;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32)(M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
    M2C_FIELD(arg2, s8 *, 0xE) = 0x40;
    M2C_FIELD(arg2, s8 *, 0xD) = 0x40;
    M2C_FIELD(arg2, s8 *, 0xC) = 0x40;
    return;
block_11:
    if (func_800AA924(arg0, arg1, arg2, &D_80174EF8) == 0) {
        goto block_63;
    }
    M2C_FIELD(arg3, s32 *, 0x1C) |= 0x10000000;
    return;
block_14:
    if (D_80083462 & 0x2000) {
        goto block_30;
    }
    if (!(temp_v1 & 0x100)) {
        goto block_18;
    }
    func_800AA258(arg0, arg1, arg2, arg3);
    return;
block_18:
    current_mode = M2C_FIELD(arg0, u8 *, 0x9A);
    ASM_SCHED_BARRIER();
    mode_14 = 0xE;
    if (current_mode == mode_14) {
        goto block_22;
    }
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == D_80174EE0) {
        goto block_21;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_80174EE0;
    func_80047784(arg2, D_80174EE0[((s32)(D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
block_21:
    M2C_FIELD(arg0, u8 *, 0x9A) = mode_14;
block_22:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16)(M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) {
        goto block_24;
    }
    if (func_800AA6B4(arg0, arg1, arg2, &D_80174F10) != 0) {
        goto block_63;
    }
block_24:
    if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
        goto block_27;
    }
    func_800AA888(arg0, arg1, arg2, arg3);
    func_801737C4(arg0, arg1, arg2, arg3);
    return;
block_27:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_30;
    }
    if ((func_800AAB10(arg0, arg1, arg2, arg3) << 0x10) == 0) {
        goto block_30;
    }
    func_801747D0(arg0, arg1, arg2, arg3);
block_30:
    temp_v0 = func_8009FB34(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, s8 *, 0x26) = temp_v0;
    if (M2C_FIELD(arg3, s8 *, 0x6D) <= 0) {
        goto block_52;
    }
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x20) {
        goto block_44;
    }
    if (M2C_FIELD(arg2, u16 *, 0x24) == D_80082EA4) {
        goto block_50;
    }
    if (M2C_FIELD(arg3, u16 *, 0x46) & 0x8000) {
        goto block_38;
    }
    if (!(D_80083462 & 0x2000)) {
        goto block_36;
    }
    if ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
        goto block_63;
    }
block_36:
    if ((func_80173A08(arg0, arg1, arg2, 0) << 0x10) == 0) {
        goto block_63;
    }
    temp_v0_2 = M2C_FIELD(arg3, u16 *, 0x46) | 0x4000;
    M2C_FIELD(arg3, u16 *, 0x46) = temp_v0_2;
    if (!(temp_v0_2 & 0x8000)) {
        goto block_50;
    }
block_38:
    temp_v0_3 = M2C_FIELD(arg3, u16 *, 0x46) & 0x3FFF;
    if ((u32)(temp_v0_3 - 1) >= 0xCU) {
        goto block_49;
    }
    (void)jt_keep;
    goto *D_80170808[(u32)(temp_v0_3 - 1)];
jt_c8:
jt_c9:
    if ((func_80171E00(arg0, arg1, arg2, arg3) << 0x10) != 0) {
        goto block_63;
    }
    func_80171FC4(arg0, arg1, arg2, arg3);
    return;
jt_c5:
jt_c6:
jt_c7:
    case_ref = &D_80082E80;
    case_floor = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), case_ref->x, case_ref->y, &sp18);
    case_entity = D_800814A8;
    M2C_FIELD(arg3, s16 *, 0x2A) = case_floor;
    if (M2C_FIELD(case_entity, u8 *, 0x9A) == 0x11) {
        goto jt_c1;
    }
jt_c12:
block_44:
    func_800A9A0C(arg3);
    return;
jt_c1:
jt_c2:
jt_c3:
    var_v0 = (M2C_UNK *)func_80170E9C;
block_47:
    func_800AAF00(arg0, arg1, arg2, &D_80174F08, var_v0);
    return;
jt_c4:
jt_c10:
jt_c11:
block_49:
block_50:
    func_80171410(arg0, arg1, arg2, arg3);
    return;
block_52:
    temp_a1 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (temp_a1 & 0x2000) {
        goto block_59;
    }
    if (temp_v0 < 0) {
        goto block_55;
    }
    if (D_800E2970[temp_v0].flags & 2) {
        goto block_59;
    }
block_55:
    if (temp_a1 & 0x430) {
        goto block_59;
    }
    late_ref = &D_80082E80;
    if ((func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), late_ref->x, late_ref->y) << 0x10) == 0) {
        goto block_58;
    }
    M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), late_ref->x, late_ref->y, &sp18);
block_58:
block_59:
    if (D_80083462 & 0x2000) {
        goto block_63;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x40) {
        goto block_63;
    }
    if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) == D_80174EE0) {
        goto block_63;
    }
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_80174EE0;
    func_80047784(arg2, D_80174EE0[((s32)(D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
block_63:
    return;
}
