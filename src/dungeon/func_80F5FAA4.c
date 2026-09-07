#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801732A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x40];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
    u8 pad_A4[0x6];
    u16 unk_AA;
    u8 pad_AC[0xF];
    s8 unk_BB;
} S_801732A4_0;   /* arg0 in func_801732A4 */


typedef struct S_801732A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x4];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
} S_801732A4_2;   /* arg3 in func_801732A4 */

typedef struct S_801732A4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801732A4_3;   /* var_v0 in func_801732A4 */


typedef struct S_801732A4_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_801732A4_5;   /* temp_base_2 in func_801732A4 */

typedef struct S_801732A4_6 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_801732A4_6;   /* temp_base in func_801732A4 */

typedef struct S_801732A4_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    u8 * unk_2C;
} S_801732A4_7;   /* temp_a0 in func_801732A4 */

typedef struct S_801732A4_8 {
    u8 pad_00[0xBB];
    u8 unk_BB;
} S_801732A4_8;   /* temp_v1_7 in func_801732A4 */

typedef struct Copy24 { u32 words[6]; } Copy24;

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

    temp_v1 = ((S_801732A4_0 *)arg0)->unk_9B;
    if (temp_v1 >= 6U) goto block_58;
    (void)jt_keep; goto *D_80170858[(u32)(temp_v1)];
jt_c0:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) goto block_58;
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_801741DC;
    func_80047784(arg2, D_801741DC[((D_80083228 + ((S_801732A4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    D_80083460[5] = (u16)(D_80083460[5] - 1);
    goto block_55;
jt_c1:
    temp_v1_2 = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    if (temp_v1_2 & 0x8000) goto block_9;
    if (!(temp_v1_2 & 0x6000)) goto block_8;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16)(temp_v1_2 & 0x9FFF);
    temp_v0 = ((S_801732A4_0 *)arg0)->unk_96 + 1;
    ((S_801732A4_0 *)arg0)->unk_96 = temp_v0;
    if (!(temp_v0 & 1)) goto block_9;
    func_800A56E0(0x51B);
block_8:
block_9:
    var_v0 = &D_80083460;
    if (((S_801732A4_3 *)var_v0)->unk_02 & 0x1000) goto block_58;
    if ((func_80042900(arg3, 1) << 0x10) != 0) goto block_16;
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_801741E4;
    func_80047784(arg2, D_801741E4[((D_80083228 + ((S_801732A4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        if (!(((S_801732A4_0 *)arg0)->unk_98 & 0x8000)) goto block_14;
        ((S_801732A4_3 *)var_v0)->unk_0A = (u16)(((S_801732A4_3 *)var_v0)->unk_0A + 1);
        func_80173954();
block_14:
        ((S_801732A4_2 *)arg3)->unk_1C = (s32)(((S_801732A4_2 *)arg3)->unk_1C & ~0x200);
        goto block_56;
    }
    ((S_801732A4_3 *)var_v0)->unk_0A = (u16)(((S_801732A4_3 *)var_v0)->unk_0A + 1);
    func_80173954();
block_16:
    if (((S_801732A4_2 *)arg3)->unk_64 == 0) goto block_22;
    if (func_800AA6B4(arg0, arg1, arg2, 0) == 0) goto block_22;
    ((S_801732A4_0 *)arg0)->unk_98 = (u16)(((S_801732A4_0 *)arg0)->unk_98 | 0x8000);
    if (((S_801732A4_2 *)arg3)->unk_25 != 0) goto block_21;
    if (((S_801732A4_3 *)var_v0)->unk_02 & 0x2008) goto block_58;
    func_800AA79C(arg0, arg1, arg2, arg3);
    return;
block_21:
    ((S_801732A4_0 *)arg0)->unk_AA = (u16)((((S_801732A4_2 *)arg3)->unk_6A + 0x800) & 0xFFF);
    return;
block_22:
    temp_v1_3 = ((S_801732A4_2 *)arg3)->unk_14;
    if (temp_v1_3 & 0x8000) goto block_24;
    ((S_801732A4_2 *)arg3)->unk_14 = (s32)(temp_v1_3 | 0x8000);
    ((S_801732A4_2 *)arg3)->unk_64 = (s16)((u16)((S_801732A4_2 *)arg3)->unk_64 + 1);
    func_800AD4D0(arg3);
block_24:
    if ((func_800A2C34(arg3) << 0x10) != 0) goto block_58;
    temp_v1_4 = ((S_801732A4_2 *)arg3)->unk_1C;
    if (!(temp_v1_4 & 0x100)) goto block_27;
    func_800AA258(arg0, arg1, arg2, arg3);
    return;
block_27:
    if (!(temp_v1_4 & 0x80000)) goto block_29;
    func_800AA888(arg0, arg1, arg2, arg3);
    func_80173CEC(arg0, arg1, arg2, arg3);
    return;
block_29:
    if (((S_801732A4_2 *)arg3)->unk_6D == 0) goto block_58;
    if ((func_800A2C34(arg3) << 0x10) == 0) goto block_32;
    if ((func_8009A180(arg3, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) != 0) goto block_58;
block_32:
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 0x10) == 0) goto block_40;
    temp_base_2 = &D_80082E80;
    temp_v1_5 = ((Rec_D_80082E80 *)arg2)->unk_26.as_s8;
    if (temp_v1_5 != ((S_801732A4_5 *)temp_base_2)->unk_26) goto block_35;
    if (temp_v1_5 >= 0) goto block_36;
block_35:
    if (func_8009FD40(temp_base_2, arg2) >= 2) goto block_38;
block_36:
    if (func_800A6D30() & 7) goto block_38;
    func_80042B68(arg3, 1);
block_38:
    if (!(((S_801732A4_0 *)arg0)->unk_98 & 0x8000)) goto block_40;
    func_80042B68(arg3, 1);
block_40:
    if ((func_80042900(arg3, 1) << 0x10) != 0) goto block_58;
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_801741E4;
    func_80047784(arg2, D_801741E4[((D_80083228 + ((S_801732A4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) goto block_44;
    if (!(((S_801732A4_0 *)arg0)->unk_98 & 0x8000)) goto block_14;
    {
        register u16 effect_count ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        effect_count = D_80083460[5];
        D_80083460[5] = (u16)(effect_count + 1);
    }
    func_80173954();
block_44:
    {
        register u16 effect_count ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        effect_count = D_80083460[5];
        D_80083460[5] = (u16)(effect_count + 1);
    }
    func_80173954();
jt_c2:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) goto block_58;
    (*(u8 **)((u8 *)arg2 + 0x2C)) = D_801741EC;
    func_80047784(arg2, D_801741EC[((D_80083228 + ((S_801732A4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    goto block_55;
jt_c3:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) goto block_58;
    temp_base = &D_80083160;
    ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 = D_801741F4;
    func_80047784(arg2, D_801741F4[((((S_801732A4_6 *)temp_base)->unk_C8 + ((S_801732A4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_801732A4_0 *)arg0)->unk_9B = (u8)(((S_801732A4_0 *)arg0)->unk_9B + 1);
    temp_v0_2 = func_8003FD64(0x112, &D_80083498);
    ((S_801732A4_0 *)arg0)->unk_A0 = temp_v0_2;
    arg0 = temp_v0_2;
    if (arg0 == NULL) goto block_58;
    func_8004491C(arg0, &D_80045340);
    temp_v1_6 = ((S_801732A4_0 *)arg0)->unk_08;
    ((S_801732A4_0 *)arg0)->unk_10 = &D_800D7960;
    *(Copy24 *)temp_v1_6 = *(Copy24 *)arg1;
    ((S_801732A4_0 *)arg0)->unk_BB = 0;
    temp_a0 = ((S_801732A4_0 *)arg0)->unk_0C;
    ((S_801732A4_0 *)arg0)->unk_4A = (u16)((S_801732A4_2 *)arg3)->unk_2A;
    temp_arg2_28 = ((Rec_D_80082E80 *)arg2)->unk_28.at00_s32.v;
    ((S_801732A4_7 *)temp_a0)->unk_1E = 0x1000;
    ((S_801732A4_7 *)temp_a0)->unk_1C = 0x1000;
    ((S_801732A4_7 *)temp_a0)->unk_28 = temp_arg2_28;
    ((S_801732A4_7 *)temp_a0)->unk_14 = (u16)((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    ((S_801732A4_7 *)temp_a0)->unk_12 = (u16)((Rec_D_80082E80 *)arg2)->unk_12.at00_u16.v;
    ((S_801732A4_7 *)temp_a0)->unk_0C = (s32)((Rec_D_80082E80 *)arg2)->unk_0C.at00_s32.v;
    ((S_801732A4_7 *)temp_a0)->unk_2C = D_801741FC;
    func_80047784(temp_a0, D_801741FC[((((S_801732A4_6 *)temp_base)->unk_C8 + ((S_801732A4_2 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    return;
jt_c4:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) goto block_58;
    temp_v1_7 = ((S_801732A4_0 *)arg0)->unk_A0;
    if (temp_v1_7 == NULL) goto block_53;
    ((S_801732A4_8 *)temp_v1_7)->unk_BB = 0xFF;
    ((S_801732A4_0 *)arg0)->unk_A0 = NULL;
block_53:
    D_80083460[5] = (u16)(D_80083460[5] - 1);
    ((S_801732A4_2 *)arg3)->unk_1C = (s32)(((S_801732A4_2 *)arg3)->unk_1C & ~0x200);
    temp_v1_8 = ((S_801732A4_0 *)arg0)->unk_98;
    if (!(temp_v1_8 & 0x8000)) goto block_56;
    ((S_801732A4_0 *)arg0)->unk_98 = (u16)(temp_v1_8 & 0x7FFF);
    ((S_801732A4_2 *)arg3)->unk_2A = (s16)((S_801732A4_0 *)arg0)->unk_AA;
    ((S_801732A4_2 *)arg3)->unk_6D = (s8)((u8)((S_801732A4_2 *)arg3)->unk_6D + 1);
block_55:
    ((S_801732A4_0 *)arg0)->unk_9B = (u8)(((S_801732A4_0 *)arg0)->unk_9B + 1);
    return;
block_56:
    ((S_801732A4_0 *)arg0)->unk_8C = &D_80170E68;
    return;
jt_c5:
    func_80171F94(arg0, arg1, arg2, arg3);
block_58:
    return;
}
