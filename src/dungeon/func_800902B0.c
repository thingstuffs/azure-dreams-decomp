#include "common.h"
#include "m2c_compat.h"

typedef struct S_80095A10_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80095A10_0;   /* arg0 in func_80095A10 */

typedef struct S_80095A10_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80095A10_1;   /* arg2 in func_80095A10 */

typedef struct S_80095A10_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_80095A10_2;   /* arg3 in func_80095A10 */

typedef struct S_80095A10_3 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_80095A10_3;   /* temp_s1 in func_80095A10 */

typedef struct S_80095A10_4 {
    u8 unk_00;
} S_80095A10_4;   /* &D_800E3E40 in func_80095A10 */

typedef struct S_80095A10_5_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80095A10_5_pre;   /* the 0x18 bytes before temp_v0_3 in func_80095A10, addressed as temp_v0_3[-1] */

typedef struct S_80095A10_5 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
} S_80095A10_5;   /* temp_v0_3 in func_80095A10 */

typedef struct S_80095A10_6 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_80095A10_6;   /* temp_v1 in func_80095A10 */

typedef struct S_80095A10_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80095A10_7;   /* temp_v1_2 in func_80095A10 */

typedef struct S_80095A10_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80095A10_8;   /* arg1 in func_80095A10 */

typedef struct S_80095A10_9 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80095A10_9;   /* temp_v1_4 in func_80095A10 */

typedef struct S_80095A10_10 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80095A10_10;   /* ((S_80095A10_2 *)arg3)->unk_60 in func_80095A10 */


extern void *D_80088AF8[];
s32 func_8003E4FC();
void func_800424E0();
void func_80042560();
M2C_UNK func_80042640();
void func_80042B68();
void func_80043914();
s32 func_80047DB8();
void func_80047DF0();
void func_80048A44();
void func_80095D30() __attribute__((noreturn));
void func_80095D34() __attribute__((noreturn));
M2C_UNK func_80093C70();
M2C_UNK func_80093D8C();
M2C_UNK func_800956B8();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
void *(*func_800A0B94())(M2C_UNK, s8, s8, s16);
s32 func_800A1618();
M2C_UNK func_800A56E0();
extern M2C_UNK D_8003E140;
extern s32 D_80081488;
extern u8 *D_80082EB0;
extern s16 D_80083228;
extern u8 D_80083460[12];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DCFB0[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

void func_80095A10(u8 *incoming0, void *incoming1, void *incoming2, u8 *incoming3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    u8 *arg0 = incoming0;
    void *arg1 = incoming1;
    void *arg2 = incoming2;
    register u8 *arg3 ASM_REG("$19") = incoming3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *var_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    u32 temp_flags;
    u16 temp_v0_4;
    u16 temp_v1_3;
    u8 *temp_s1;
    u32 temp_a0;
    void *temp_v0_3;
    void *temp_v1;
    void *temp_v1_2;
    u8 *temp_v1_4;

    temp_a0 = ((S_80095A10_0 *)arg0)->unk_9B;
    temp_s1 = D_80082EB0;
    if (temp_a0 >= 7U) {
        goto block_22;
    }
    (void)jt_keep; goto *D_80088AF8[(u32)(temp_a0)];
jt_c0:
    if (!(((S_80095A10_1 *)arg2)->unk_14 & 0xE000)) {
        goto block_22;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_800DD138;
    func_80048A44(arg2, *((((s32) (D_80083228 + ((S_80095A10_2 *)arg3)->unk_2A + 0x100) >> 9) & 7) + D_800DD138), 0, 1);
    ((S_80095A10_1 *)arg2)->unk_14 = (u16) (((S_80095A10_1 *)arg2)->unk_14 | 0x200);
    func_80093C70(arg0, arg1, arg2);
    func_80093D8C(arg0, arg1, arg2);
    return func_80095D30();
jt_c1:
    temp_v0 = func_800A1618(((S_80095A10_3 *)temp_s1)->unk_00, 2);
    if (temp_v0 == 0) {
        goto block_18;
    }
    D_80081488 = func_80047DB8(((S_80095A10_3 *)temp_s1)->unk_00);
    func_800A0B94(((S_80095A10_3 *)temp_s1)->unk_00, temp_v0, 0);
    (*(s8 *)&D_800E3E40) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_800E3E40);
    return func_80095D30();
jt_c2:
    if (((S_80095A10_4 *)(&D_800E3E40))->unk_00 == 0) {
        goto block_22;
    }
    func_80047DF0(temp_a0);
    return func_80095D30();
jt_c3:
    temp_v0_2 = func_800A1618(((S_80095A10_3 *)temp_s1)->unk_00, 2);
    if (temp_v0_2 == 0) {
        goto block_22;
    }
    func_80043914(D_80082EB0);
    temp_v0_3 = func_800A0B94(((S_80095A10_3 *)temp_s1)->unk_00, temp_v0_2, 1)(6, ((S_80095A10_2 *)arg3)->unk_72, ((S_80095A10_2 *)arg3)->unk_73, (s16) (((S_80095A10_2 *)arg3)->unk_88 - 0x20));
    if (temp_v0_3 == NULL) {
        goto block_12;
    }
    ((S_80095A10_2 *)arg3)->unk_60 = temp_v0_3;
    D_800E3DF0[((S_80095A10_3 *)temp_s1)->unk_03 & 0x1F] = temp_v0_3;
    temp_v1 = ((S_80095A10_5_pre *)temp_v0_3)[-1].unk_04;
    ((S_80095A10_6 *)temp_v1)->unk_1E = 0x800;
    ((S_80095A10_6 *)temp_v1)->unk_1C = 0x800;
    temp_v1_2 = ((S_80095A10_5_pre *)temp_v0_3)[-1].unk_00;
    ((S_80095A10_7 *)temp_v1_2)->unk_02 = (u16) ((S_80095A10_8 *)arg1)->unk_02;
    ((S_80095A10_7 *)temp_v1_2)->unk_06 = (u16) ((S_80095A10_8 *)arg1)->unk_06;
    ((S_80095A10_7 *)temp_v1_2)->unk_0A = (s16) (((S_80095A10_8 *)arg1)->unk_0A - 0x10);
    func_80042640(temp_v0_3, ((S_80095A10_5 *)temp_v0_3)->unk_13);
    func_800424E0(temp_v0_3, ((S_80095A10_5 *)temp_v0_3)->unk_13, temp_s1);
    temp_flags = ((S_80095A10_5 *)temp_v0_3)->unk_1C;
    temp_flags |= 0x02000000;
    temp_flags |= 0x20000;
    ((S_80095A10_5 *)temp_v0_3)->unk_1C = temp_flags;
    func_80042560(temp_v0_3);
    func_800A56E0(0x704);
    func_80042B68(temp_v0_3, 3);
    func_80042B68(temp_v0_3, 1);
    if (((S_80095A10_5 *)temp_v0_3)->unk_25 != 0) {
        goto block_12;
    }
    ((S_80095A10_5 *)temp_v0_3)->unk_25 = 1U;
block_12:
    temp_a0 = *(volatile u8 *)((u8 *)arg0 + 0x9B);
    {
        register u16 timer ASM_REG("$3") = 0x10U;   /* MATCH pin: retail register colouring depends on it */
        ((S_80095A10_0 *)arg0)->unk_96 = timer;
        return func_80095D34();
    }
jt_c4:
    temp_v0_4 = ((S_80095A10_0 *)arg0)->unk_96 - 1;
    ((S_80095A10_0 *)arg0)->unk_96 = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_22;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_800DD140;
    func_80048A44(arg2, *((((s32) (D_80083228 + ((S_80095A10_2 *)arg3)->unk_2A + 0x100) >> 9) & 7) + D_800DD140), 0, 1);
    goto block_18;
jt_c5:
    temp_v1_3 = ((S_80095A10_1 *)arg2)->unk_14;
    if (!(temp_v1_3 & 0x6000)) {
        goto block_22;
    }
    var_a1 = D_800DCFB0;
    ((S_80095A10_1 *)arg2)->unk_14 = (u16) (temp_v1_3 & 0xFDFF);
block_17:
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = var_a1;
    func_80048A44(arg2, *((((s32) (D_80083228 + ((S_80095A10_2 *)arg3)->unk_2A + 0x100) >> 9) & 7) + var_a1), 0, 1);
block_18:
    ((S_80095A10_0 *)arg0)->unk_9B = (u8) (((S_80095A10_0 *)arg0)->unk_9B + 1);
    return;
jt_c6:
    if (((S_80095A10_10 *)(((S_80095A10_2 *)arg3)->unk_60))->unk_14 & 0x100000) {
        goto block_22;
    }
    func_800956B8(arg0, arg1, arg2, temp_s1);
    ((S_80095A10_0 *)arg0)->unk_8C = &D_8008ACDC;
    func_80099F70(((S_80095A10_2 *)arg3)->unk_5C);
    func_80099F04(((S_80095A10_2 *)arg3)->unk_5C);
    temp_v1_4 = D_80083460;
    ((S_80095A10_9 *)temp_v1_4)->unk_02 = (u16) (((S_80095A10_9 *)temp_v1_4)->unk_02 | 0x812);
block_22:
    return;
}
