#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
typedef struct Copy24 { u32 words[6]; } Copy24;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170858[];
void *func_8003FD64();
s32 func_80042900();
void func_80042B68();
s32 func_8004491C();
void func_80047784();
s32 func_8009A180();
s16 func_8009FD40();
s32 func_800A2C34();
M2C_UNK func_800A56E0();
s32 func_800A6D30();
M2C_UNK func_800A9A04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
M2C_UNK func_800AD4D0();
M2C_UNK func_80171F94();
M2C_UNK func_80173CEC();
extern void func_80173954(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern u16 D_80083460[];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800D7960;
extern M2C_UNK D_80170E68;
extern u8 D_801741DC[];
extern u8 D_801741E4[];
extern u8 D_801741EC[];
extern u8 D_801741F4[];
extern u8 D_801741FC[];

void func_801732A4(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    M2C_UNK *var_v0;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_arg2_28;
    s8 temp_v1_5;
    u16 temp_v0;
    u16 temp_v1_2;
    u16 temp_v1_8;
    u8 temp_v1;
    void *temp_a0;
    void *temp_v0_2;
    void *temp_v1_6;
    void *temp_v1_7;
    void *temp_base;
    void *temp_base_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 6U) goto block_58;
    (void)jt_keep; goto *D_80170858[(u32)(temp_v1)];
jt_c0:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) goto block_58;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_801741DC;
    func_80047784(arg2, D_801741DC[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    D_80083460[5] = (u16)(D_80083460[5] - 1);
    goto block_55;
jt_c1:
    temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
    if (temp_v1_2 & 0x8000) goto block_9;
    if (!(temp_v1_2 & 0x6000)) goto block_8;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(temp_v1_2 & 0x9FFF);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if (!(temp_v0 & 1)) goto block_9;
    func_800A56E0(0x51B);
block_8:
block_9:
    var_v0 = &D_80083460;
    if (M2C_FIELD(var_v0, u16 *, 2) & 0x1000) goto block_58;
    if ((func_80042900(arg3, 1) << 0x10) != 0) goto block_16;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_801741E4;
    func_80047784(arg2, D_801741E4[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x8000)) goto block_14;
        M2C_FIELD(var_v0, u16 *, 0xA) = (u16)(M2C_FIELD(var_v0, u16 *, 0xA) + 1);
        func_80173954();
block_14:
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32)(M2C_FIELD(arg3, s32 *, 0x1C) & ~0x200);
        goto block_56;
    }
    M2C_FIELD(var_v0, u16 *, 0xA) = (u16)(M2C_FIELD(var_v0, u16 *, 0xA) + 1);
    func_80173954();
block_16:
    if (M2C_FIELD(arg3, s16 *, 0x64) == 0) goto block_22;
    if (func_800AA6B4(arg0, arg1, arg2, 0) == 0) goto block_22;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16)(M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
    if (M2C_FIELD(arg3, u8 *, 0x25) != 0) goto block_21;
    if (M2C_FIELD(var_v0, u16 *, 2) & 0x2008) goto block_58;
    func_800AA79C(arg0, arg1, arg2, arg3);
    return;
block_21:
    M2C_FIELD(arg0, u16 *, 0xAA) = (u16)((M2C_FIELD(arg3, u16 *, 0x6A) + 0x800) & 0xFFF);
    return;
block_22:
    temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x14);
    if (temp_v1_3 & 0x8000) goto block_24;
    M2C_FIELD(arg3, s32 *, 0x14) = (s32)(temp_v1_3 | 0x8000);
    M2C_FIELD(arg3, s16 *, 0x64) = (s16)((u16)M2C_FIELD(arg3, s16 *, 0x64) + 1);
    func_800AD4D0(arg3);
block_24:
    if ((func_800A2C34(arg3) << 0x10) != 0) goto block_58;
    temp_v1_4 = M2C_FIELD(arg3, s32 *, 0x1C);
    if (!(temp_v1_4 & 0x100)) goto block_27;
    func_800AA258(arg0, arg1, arg2, arg3);
    return;
block_27:
    if (!(temp_v1_4 & 0x80000)) goto block_29;
    func_800AA888(arg0, arg1, arg2, arg3);
    func_80173CEC(arg0, arg1, arg2, arg3);
    return;
block_29:
    if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) goto block_58;
    if ((func_800A2C34(arg3) << 0x10) == 0) goto block_32;
    if ((func_8009A180(arg3, M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) goto block_58;
block_32:
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 0x10) == 0) goto block_40;
    temp_base_2 = &D_80082E80;
    temp_v1_5 = M2C_FIELD(arg2, s8 *, 0x26);
    if (temp_v1_5 != M2C_FIELD(temp_base_2, s8 *, 0x26)) goto block_35;
    if (temp_v1_5 >= 0) goto block_36;
block_35:
    if (func_8009FD40(temp_base_2, arg2) >= 2) goto block_38;
block_36:
    if (func_800A6D30() & 7) goto block_38;
    func_80042B68(arg3, 1);
block_38:
    if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x8000)) goto block_40;
    func_80042B68(arg3, 1);
block_40:
    if ((func_80042900(arg3, 1) << 0x10) != 0) goto block_58;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_801741E4;
    func_80047784(arg2, D_801741E4[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) goto block_44;
    if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x8000)) goto block_14;
    {
        register u16 effect_count ASM_REG("$3");
        effect_count = D_80083460[5];
        D_80083460[5] = (u16)(effect_count + 1);
    }
    func_80173954();
block_44:
    {
        register u16 effect_count ASM_REG("$3");
        effect_count = D_80083460[5];
        D_80083460[5] = (u16)(effect_count + 1);
    }
    func_80173954();
jt_c2:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) goto block_58;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_801741EC;
    func_80047784(arg2, D_801741EC[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    goto block_55;
jt_c3:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) goto block_58;
    temp_base = &D_80083160;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_801741F4;
    func_80047784(arg2, D_801741F4[((M2C_FIELD(temp_base, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8)(M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    temp_v0_2 = func_8003FD64(0x112, &D_80083498);
    M2C_FIELD(arg0, void **, 0xA0) = temp_v0_2;
    arg0 = temp_v0_2;
    if (arg0 == NULL) goto block_58;
    func_8004491C(arg0, &D_80045340);
    temp_v1_6 = M2C_FIELD(arg0, void **, 8);
    M2C_FIELD(arg0, M2C_UNK **, 0x10) = &D_800D7960;
    *(Copy24 *)temp_v1_6 = *(Copy24 *)arg1;
    M2C_FIELD(arg0, s8 *, 0xBB) = 0;
    temp_a0 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(arg0, u16 *, 0x4A) = (u16)M2C_FIELD(arg3, s16 *, 0x2A);
    temp_arg2_28 = M2C_FIELD(arg2, s32 *, 0x28);
    M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_a0, s32 *, 0x28) = temp_arg2_28;
    M2C_FIELD(temp_a0, u16 *, 0x14) = (u16)M2C_FIELD(arg2, u16 *, 0x14);
    M2C_FIELD(temp_a0, u16 *, 0x12) = (u16)M2C_FIELD(arg2, u16 *, 0x12);
    M2C_FIELD(temp_a0, s32 *, 0xC) = (s32)M2C_FIELD(arg2, s32 *, 0xC);
    M2C_FIELD(temp_a0, u8 **, 0x2C) = D_801741FC;
    func_80047784(temp_a0, D_801741FC[((M2C_FIELD(temp_base, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    return;
jt_c4:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) goto block_58;
    temp_v1_7 = M2C_FIELD(arg0, void **, 0xA0);
    if (temp_v1_7 == NULL) goto block_53;
    M2C_FIELD(temp_v1_7, u8 *, 0xBB) = 0xFF;
    M2C_FIELD(arg0, void **, 0xA0) = NULL;
block_53:
    D_80083460[5] = (u16)(D_80083460[5] - 1);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32)(M2C_FIELD(arg3, s32 *, 0x1C) & ~0x200);
    temp_v1_8 = M2C_FIELD(arg0, u16 *, 0x98);
    if (!(temp_v1_8 & 0x8000)) goto block_56;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16)(temp_v1_8 & 0x7FFF);
    M2C_FIELD(arg3, s16 *, 0x2A) = (s16)M2C_FIELD(arg0, u16 *, 0xAA);
    M2C_FIELD(arg3, s8 *, 0x6D) = (s8)((u8)M2C_FIELD(arg3, s8 *, 0x6D) + 1);
block_55:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8)(M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
block_56:
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80170E68;
    return;
jt_c5:
    func_80171F94(arg0, arg1, arg2, arg3);
block_58:
    return;
}
