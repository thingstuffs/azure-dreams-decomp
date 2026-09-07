#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;
typedef struct {
    Vec3s item[3];
} Vec3sTable;

extern Vec3sTable D_80170838;
extern Vec3sTable D_8017084C;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_80083228[5];
extern u8 D_80174AA4[];
extern u8 D_80083498[];
extern u8 D_80174AAC[];
extern u8 D_80170E94[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern void *D_80170860[];
s32 func_8003DE58();
void *func_8003FD64(s32, void *);
M2C_UNK func_8004491C();
s16 func_80066460();
s16 func_8006649C();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
extern M2C_UNK D_800DB618;
extern M2C_UNK D_800DB660;
extern u8 D_80174A8C;
extern u8 D_80174A94;


typedef struct S_801727B4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    u16 unk_A8;
    u16 unk_AA;
    u16 unk_AC;
    u16 unk_AE;
    u16 unk_B0;
} S_801727B4_0;   /* arg0 in func_801727B4 */

typedef struct S_801727B4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801727B4_1;   /* arg1 in func_801727B4 */

typedef struct S_801727B4_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801727B4_2;   /* arg2 in func_801727B4 */

typedef struct S_801727B4_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
} S_801727B4_3;   /* arg3 in func_801727B4 */

typedef struct S_801727B4_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0xC];
    u16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
} S_801727B4_4;   /* temp_s0 in func_801727B4 */

void func_801727B4(void *arg0, S_801727B4_1 *arg1, S_801727B4_2 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    Vec3sTable sp10;
    Vec3sTable sp28;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u32 formula_factor;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 case_left;
    s32 case_right;
    u16 temp_v0_3;
    u16 temp_v0_7;
    u8 temp_v1;
    u8 state_v;
    void *temp_a2;
    S_801727B4_4 *temp_s0;
    void *temp_v0_2;
    void *temp_v0_6;
    void *temp_v1_4;

    sp10 = D_80170838;
    sp28 = D_8017084C;
    temp_v1 = ((S_801727B4_0 *)arg0)->unk_9B;
    if (temp_v1 >= 6U) {
        goto block_50;
    }
    (void)jt_keep; goto *D_80170860[(u32)(temp_v1)];
jt_c0:
    ((S_801727B4_0 *)arg0)->unk_A8 = (u16) arg1->unk_02;
    ((S_801727B4_0 *)arg0)->unk_AA = (u16) arg1->unk_06;
    if (!(arg2->unk_14 & 0x8000)) {
        goto block_5;
    }
    ((S_801727B4_0 *)arg0)->unk_9B = 5U;
    arg2->unk_14 = (u16) (arg2->unk_14 | 0x6000);
    func_8009C12C(arg3, arg2, ((S_801727B4_3 *)arg3)->unk_2A, 1);
    goto block_50;
block_5:
    temp_v0 = ((u16) ((S_801727B4_3 *)arg3)->unk_2A >> 9) & 7;
    temp_a0 = temp_v0 + 4;
    var_v1 = temp_a0;
    if (temp_a0 >= 0) {
        goto block_7;
    }
    var_v1 = temp_v0 + 0xB;
block_7:
    temp_v1_2 = temp_a0 - (var_v1 & 0x18);
    arg1->unk_0C = (s32) ((s16) D_8006CCD8[temp_v1_2] * 0x30000);
    arg1->unk_10 = (s32) ((s16) D_8006CCE8[temp_v1_2] * 0x30000);
    arg2->unk_2C = &D_80174A8C;
    func_80047784(arg2, (&D_80174A8C)[((s32) (*D_80083228 + ((S_801727B4_3 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    goto increment_state_load;
jt_c1:
    if (!(arg2->unk_14 & 0xE000)) {
        goto block_50;
    }
    arg2->unk_2C = &D_80174A94;
    func_80047784(arg2, (&D_80174A94)[((s32) (*D_80083228 + ((S_801727B4_3 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_801727B4_0 *)arg0)->unk_90 = 0;
    ((S_801727B4_0 *)arg0)->unk_98 = (u16) (((S_801727B4_0 *)arg0)->unk_98 | 8);
    arg1->unk_14 = 0xFFF40000;
    goto increment_state_load;
jt_c2:
    temp_v1_3 = arg1->unk_14 + 0x20000;
    arg1->unk_14 = temp_v1_3;
    ((S_801727B4_0 *)arg0)->unk_90 = (s32) (((S_801727B4_0 *)arg0)->unk_90 + temp_v1_3);
    if (!(arg2->unk_14 & 0xE000)) {
        goto block_50;
    }
    arg1->unk_0C = (s32) ((s32) (0 - arg1->unk_0C) >> 1);
    arg1->unk_10 = (s32) ((s32) (0 - arg1->unk_10) >> 1);
    arg2->unk_2C = D_80174AA4;
    func_80047784(arg2, D_80174AA4[((s32) (*D_80083228 + ((S_801727B4_3 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_801727B4_0 *)arg0)->unk_96 = 7;
    ((S_801727B4_0 *)arg0)->unk_9B = (u8) (((S_801727B4_0 *)arg0)->unk_9B + 1);
    goto block_50;
jt_c3:
    if (arg2->unk_04 >= 3) {
        goto block_20;
    }
    if (func_8003DE58(arg2->unk_08, arg2, arg0 + 0xAC, 0) != 0) {
        goto block_18;
    }
    ((S_801727B4_0 *)arg0)->unk_B0 = 0U;
    ((S_801727B4_0 *)arg0)->unk_AE = 0U;
    ((S_801727B4_0 *)arg0)->unk_AC = 0U;
block_18:
    ((S_801727B4_0 *)arg0)->unk_AC = (u16) (((S_801727B4_0 *)arg0)->unk_AC + arg1->unk_02);
    ((S_801727B4_0 *)arg0)->unk_AE = (u16) (((S_801727B4_0 *)arg0)->unk_AE + arg1->unk_06);
    ((S_801727B4_0 *)arg0)->unk_B0 = (u16) (((S_801727B4_0 *)arg0)->unk_B0 + arg1->unk_0A);
    goto block_24;
block_20:
    temp_v0_2 = func_8003FD64(1, D_80083498);
    if (temp_v0_2 == NULL) {
        goto block_24;
    }
    (*(M2C_UNK **)((u8 *)temp_v0_2 + 0x10)) = &D_800DB618;
    func_8004491C(temp_v0_2, &D_800DB660);
    temp_s0 = temp_v0_2 + 0x20;
    temp_s0->unk_10 = (u16) ((S_801727B4_0 *)arg0)->unk_AC;
    temp_s0->unk_12 = (u16) ((S_801727B4_0 *)arg0)->unk_AE;
    temp_s0->unk_14 = (u16) ((S_801727B4_0 *)arg0)->unk_B0;
    temp_v0 = func_8003DE58(arg2->unk_08, arg2, arg0 + 0xAC, 0);
    if (temp_v0 == 0) {
        ((S_801727B4_0 *)arg0)->unk_B0 = 0U;
        ((S_801727B4_0 *)arg0)->unk_AE = 0U;
        ((S_801727B4_0 *)arg0)->unk_AC = 0U;
    }
    {
    s32 color_a;
    s32 color_b;
    s32 color_c;
    s32 effect_a0;
    s32 effect_a1;
    s32 effect_a2;

    color_a = 0x200020;
    color_b = 0xC0C0C0;
    effect_a0 = 0;
    effect_a1 = 1;
    effect_a2 = 0x2C0;
    temp_v0_3 = ((S_801727B4_0 *)arg0)->unk_AC + arg1->unk_02;
    ((S_801727B4_0 *)arg0)->unk_AC = temp_v0_3;
    temp_s0->unk_08 = temp_v0_3;
    temp_v0_3 = ((S_801727B4_0 *)arg0)->unk_AE + arg1->unk_06;
    ((S_801727B4_0 *)arg0)->unk_AE = temp_v0_3;
    temp_s0->unk_0A = temp_v0_3;
    temp_v0_3 = ((S_801727B4_0 *)arg0)->unk_B0 + arg1->unk_0A;
    ((S_801727B4_0 *)arg0)->unk_B0 = temp_v0_3;
    temp_s0->unk_0C = temp_v0_3;
    temp_s0->unk_2C = (u16) ((S_801727B4_3 *)arg3)->unk_2A;
    temp_s0->unk_2E = 0x10;
    temp_s0->unk_30 = 0x10;
    temp_s0->unk_36 = 0x10;
    temp_s0->unk_04 = color_a;
    temp_s0->unk_18 = color_b;
    formula_factor = 6 - arg2->unk_04;
    color_c = 0x141414;
    temp_s0->unk_1C = (s32) ((formula_factor * 0x30303) + color_c);
    (*(Vec3s *)((u8 *)temp_v0_2 + 0x40)) = sp10.item[arg2->unk_04 - 3];
    (*(Vec3s *)((u8 *)temp_v0_2 + 0x46)) = sp28.item[arg2->unk_04 - 3];
    temp_s0->unk_32 = func_80066460(effect_a0, effect_a1, effect_a2, 0x100);
    temp_s0->unk_34 = func_8006649C(0, 0x1F8);
    }
block_24:
    temp_v0_7 = ((S_801727B4_0 *)arg0)->unk_96 - 1;
    ((S_801727B4_0 *)arg0)->unk_96 = temp_v0_7;
    if ((temp_v0_7 << 0x10) == 0) {
        goto block_26;
    }
    if (!(arg2->unk_14 & 0x8000)) {
        goto block_27;
    }
block_26:
    func_8009C12C(arg3, arg2, ((S_801727B4_3 *)arg3)->unk_2A, 1);
    func_800A56E0(0x808);
block_27:
    if (!(arg2->unk_14 & 0xE000)) {
        goto block_50;
    }
    arg2->unk_2C = D_80174AAC;
    func_80047784(arg2, D_80174AAC[((s32) (*D_80083228 + ((S_801727B4_3 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    ((S_801727B4_0 *)arg0)->unk_98 = (u16) (((S_801727B4_0 *)arg0)->unk_98 & 0xFFF7);
    ((S_801727B4_0 *)arg0)->unk_9B = (u8) (((S_801727B4_0 *)arg0)->unk_9B + 1);
    goto block_50;
jt_c4:
    if (!(arg2->unk_14 & 0xE000)) {
        goto block_50;
    }
    arg2->unk_2C = D_80174AAC;
    func_80047784(arg2, D_80174AAC[((s32) (*D_80083228 + ((S_801727B4_3 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    if (!(arg2->unk_14 & 0x8000)) {
        goto block_33;
    }
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
block_33:
increment_state_load:
    state_v = ((S_801727B4_0 *)arg0)->unk_9B;
increment_state:
    ((S_801727B4_0 *)arg0)->unk_9B = (u8) (state_v + 1);
    goto block_50;
jt_c5:
    case_left = (s16) arg1->unk_02;
    case_right = (s16) ((S_801727B4_0 *)arg0)->unk_A8;
    case_left = case_left - case_right;
    if (case_left >= 0) {
        goto block_37;
    }
    case_left = 0 - case_left;
block_37:
    if (case_left >= 0x41) {
        goto block_41;
    }
    case_left = (s16) arg1->unk_06;
    case_right = (s16) ((S_801727B4_0 *)arg0)->unk_AA;
    case_left = case_left - case_right;
    if (case_left >= 0) {
        goto block_40;
    }
    case_left = 0 - case_left;
block_40:
    if (case_left < 0x41) {
        goto block_42;
    }
block_41:
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
block_42:
    if ((s16) arg1->unk_02 != (s16) ((S_801727B4_0 *)arg0)->unk_A8) {
        goto block_50;
    }
    if ((s16) arg1->unk_06 != (s16) ((S_801727B4_0 *)arg0)->unk_AA) {
        goto block_50;
    }
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_801727B4_0 *)arg0)->unk_8C = D_80170E94;
    *D_8008346C = 0;
    func_800A4ACC(arg3);
    if (((S_801727B4_3 *)arg3)->unk_6D == 0) {
        ((S_801727B4_3 *)arg3)->unk_46 = (u16) (((S_801727B4_3 *)arg3)->unk_46 & 0x7FFF);
    } else {
        *D_800E3DE8 = arg3 - 0x20;
    }
block_47:
    temp_a0_2 = ((S_801727B4_3 *)arg3)->unk_60;
    if (temp_a0_2 == 0) {
        goto block_50;
    }
    if (((S_801727B4_3 *)arg3)->unk_14 & 0x20000) {
        goto block_50;
    }
    func_800C8EFC(temp_a0_2, 0x10);
block_50:
    return;
}
