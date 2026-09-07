#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8017558C_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    s16 unk_94;
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 unk_B0;
    u8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    u8 pad_B5[0x1];
    u16 unk_B6;
    u16 unk_B8;
    u16 unk_BA;
} S_8017558C_0;   /* arg0 in func_8017558C */




typedef struct S_8017558C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 * unk_0C;
    u8 * unk_10;
} S_8017558C_4;   /* temp_v0_3 in func_8017558C */

typedef struct S_8017558C_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_8017558C_5;   /* temp_v0_4 in func_8017558C */

typedef struct S_8017558C_6 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8017558C_6;   /* temp_a0 in func_8017558C */

typedef struct S_8017558C_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017558C_7;   /* temp_v1_2 in func_8017558C */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800E296C[3];
extern u8 D_800E2438[];
extern s16 D_80083228[5];
extern u8 D_80170A84[];
extern s32 D_80045C34[3];
extern u8 D_800E2440[];
extern u8 D_800E2448[];
extern u8 D_800E23E0[];
extern u8 D_800E2488[];
extern u8 D_80171A80[];
extern s32 D_8008346C[];
extern void *D_801708A0[];
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();               /* extern */
M2C_UNK func_8009D8A4();                            /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800BCB04();                   /* extern */
M2C_UNK func_801708B8();      /* extern */
M2C_UNK func_80174C64(); /* extern */

void func_8017558C(void *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    s16 temp_a1;
    s16 temp_v1_4;
    s16 temp_s0;
    s32 *temp_a0;
    u16 temp_v0;
    u16 temp_v0_10;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u8 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_5;
    void *temp_v0_3;
    S_8017558C_5 *temp_v0_4;
    S_8017558C_7 *temp_v1_2;

    s32 temp_flag;

    temp_v1 = ((S_8017558C_0 *)arg0)->unk_9B;
    if (temp_v1 >= 6) {
        goto block_46;
    }
    (void)jt_keep; goto *D_801708A0[(u32)(temp_v1)];
jt_c0:
    if (!(arg2->unk_14.at00_u16.v & 0x8000)) {
        goto block_5;
    }
    {
        register s32 five ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
        func_8009D8A4();
        five = 5;
        ASM_KEEP(five);   /* MATCH pin: retail immediate-load split depends on it */
        temp_flag = D_800E296C[0];
        ((S_8017558C_0 *)arg0)->unk_96 = five;
        D_800E296C[0] = temp_flag | 0x800000;
        ((S_8017558C_0 *)arg0)->unk_9B = five;
    }
    arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v | 0x6000);
    goto block_46;
block_5:
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    temp_a1 = func_800BCB04(arg1->unk_00.at02_u16.v, arg1->unk_04.at02_u16.v, (s16) (arg3->unk_88.as_u16 - 0x20));
    temp_v1_4 = arg3->unk_88.as_u16;
    temp_a1 -= temp_v1_4;
    if (((S_8017558C_0 *)arg0)->unk_92.s >= temp_a1) {
        goto block_7;
    }
    ((S_8017558C_0 *)arg0)->unk_92.u = ((S_8017558C_0 *)arg0)->unk_92.u + 0xC;
    if (temp_a1 >= (s16) ((S_8017558C_0 *)arg0)->unk_92.u) {
        goto block_8;
    }
block_7:
    ((S_8017558C_0 *)arg0)->unk_92.u = (u16) temp_a1;
block_8:
    if (((S_8017558C_0 *)arg0)->unk_92.s != 0) {
        goto block_10;
    }
    arg2->unk_2C.as_pu8 = D_800E2438;
    func_80047784(arg2, D_800E2438[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    func_800A56E0(0x800);
    ((S_8017558C_0 *)arg0)->unk_96 = 2U;
    ((S_8017558C_0 *)arg0)->unk_9B = (u8) (((S_8017558C_0 *)arg0)->unk_9B + 1);
    arg2->unk_06.as_s16 = 6;
    ((S_8017558C_0 *)arg0)->unk_A6 = (u16) arg3->unk_2A.as_s16;
block_10:
    temp_v0_2 = ((S_8017558C_0 *)arg0)->unk_96 + 1;
    ((S_8017558C_0 *)arg0)->unk_96 = temp_v0_2;
    if ((s16) temp_v0_2 != 1) {
        goto block_46;
    }
    temp_v0_3 = func_8003FD64(0x12, arg0 - 0x20);
    if (temp_v0_3 == NULL) {
        goto block_46;
    }
    ((S_8017558C_0 *)arg0)->unk_AC = temp_v0_3;
    ((S_8017558C_4 *)temp_v0_3)->unk_10 = D_80170A84;
    func_8004491C(temp_v0_3, D_80045C34);
    temp_v0_4 = temp_v0_3 + 0x20;
    temp_v0_4->unk_38 = 5;
    temp_v0_4->unk_40 = arg0;
    temp_v0_4->unk_44 = arg1;
    temp_a0 = ((S_8017558C_4 *)temp_v0_3)->unk_0C;
    ((S_8017558C_6 *)temp_a0)->unk_10 = 0x40;
    ((S_8017558C_6 *)temp_a0)->unk_14 = (u16) (((S_8017558C_6 *)temp_a0)->unk_14 | 0xC);
    temp_v1_2 = ((S_8017558C_4 *)temp_v0_3)->unk_08;
    temp_v1_2->unk_02 = (u16) arg1->unk_00.at02_u16.v;
    temp_v1_2->unk_06 = (u16) arg1->unk_04.at02_u16.v;
    temp_v1_2->unk_0A = (u16) arg3->unk_88.as_u16;
    temp_a0 = ((S_8017558C_4 *)temp_v0_3)->unk_0C;
    ((S_8017558C_6 *)temp_a0)->unk_1E = 0xA00;
    ((S_8017558C_6 *)temp_a0)->unk_1C = 0xA00;
    ((S_8017558C_6 *)temp_a0)->unk_0E = 0;
    ((S_8017558C_6 *)temp_a0)->unk_0D = 0;
    ((S_8017558C_6 *)temp_a0)->unk_0C = 0;
    ((S_8017558C_6 *)temp_a0)->unk_08 = D_800E2488;
    goto block_46;
jt_c1:
    temp_v0_5 = ((S_8017558C_0 *)arg0)->unk_96 - 1;
    ((S_8017558C_0 *)arg0)->unk_96 = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        goto block_16;
    }
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto block_46;
    }
block_16:
    arg2->unk_2C.as_pu8 = D_800E2440;
    func_80047784(arg2, D_800E2440[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_8017558C_0 *)arg0)->unk_96 = 3U;
    ((S_8017558C_0 *)arg0)->unk_9B = (u8) (((S_8017558C_0 *)arg0)->unk_9B + 1);
    ((S_8017558C_0 *)arg0)->unk_B6 = (u16) arg1->unk_00.at02_u16.v;
    ((S_8017558C_0 *)arg0)->unk_B8 = (u16) arg1->unk_04.at02_u16.v;
    ((S_8017558C_0 *)arg0)->unk_BA = (u16) arg3->unk_88.as_u16;
    goto block_46;
jt_c2:
    temp_v0_6 = ((S_8017558C_0 *)arg0)->unk_96 - 1;
    ((S_8017558C_0 *)arg0)->unk_96 = temp_v0_6;
    if ((temp_v0_6 << 0x10) > 0) {
        goto block_46;
    }
    temp_v1_5 = ((S_8017558C_0 *)arg0)->unk_9B;
    ((S_8017558C_0 *)arg0)->unk_96 = 0x1EU;
    ((S_8017558C_0 *)arg0)->unk_A8 = 0;
    ((S_8017558C_0 *)arg0)->unk_B1 = 0U;
    ((S_8017558C_0 *)arg0)->unk_B2 = 0;
    ((S_8017558C_0 *)arg0)->unk_B4 = 0;
    ((S_8017558C_0 *)arg0)->unk_B3 = 0;
    temp_v1_5 += 1;
    ((S_8017558C_0 *)arg0)->unk_9B = temp_v1_5;
    goto block_46;
jt_c3:
    func_80174C64(arg0, arg1, arg2, arg3);
    goto block_46;
jt_c4:
    temp_v1_3 = ((S_8017558C_0 *)arg0)->unk_B1;
    if (temp_v1_3 == 1) {
        goto block_36;
    }
    if ((s32) temp_v1_3 >= 2) {
        goto block_28;
    }
    if (temp_v1_3 == 0) {
        goto block_31;
    }
    goto block_46;
block_28:
    if (temp_v1_3 == 2) {
        goto block_39;
    }
    goto block_46;
block_31:
    temp_v0_7 = ((S_8017558C_0 *)arg0)->unk_96 + 1;
    ((S_8017558C_0 *)arg0)->unk_96 = temp_v0_7;
    if ((s16) temp_v0_7 != 1) {
        goto block_33;
    }
    arg1->unk_00.at02_u16.v = (u16) ((S_8017558C_0 *)arg0)->unk_B6;
    arg1->unk_04.at02_u16.v = (u16) ((S_8017558C_0 *)arg0)->unk_B8;
    arg3->unk_88.as_u16 = (u16) ((S_8017558C_0 *)arg0)->unk_BA;
    temp_v0_8 = ((S_8017558C_0 *)arg0)->unk_A6;
    arg3->unk_2A.as_s16 = (s16) temp_v0_8;
    temp_s0 = ((s32) (*D_80083228 + (s16) temp_v0_8 + 0x100) >> 9) & 7;
    func_80047738(arg2, arg2->unk_2C.as_pu8[temp_s0], arg2->unk_04.as_s8);
    ((S_8017558C_0 *)arg0)->unk_94 = temp_s0;
block_33:
    if ((s16) ((S_8017558C_0 *)arg0)->unk_96 < 0x10) {
        goto block_46;
    }
    ((S_8017558C_0 *)arg0)->unk_96 = 0U;
    ((S_8017558C_0 *)arg0)->unk_B1 = (u8) (((S_8017558C_0 *)arg0)->unk_B1 + 1);
    arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v & 0x9F7F);
    goto block_46;
block_36:
    temp_v0_9 = ((S_8017558C_0 *)arg0)->unk_96;
    ((S_8017558C_0 *)arg0)->unk_96 = (u16) (temp_v0_9 + 1);
    if ((s16) temp_v0_9 < 4) {
        goto block_46;
    }
    ((S_8017558C_0 *)arg0)->unk_96 = 0U;
    ((S_8017558C_0 *)arg0)->unk_B1 = (u8) (((S_8017558C_0 *)arg0)->unk_B1 + 1);
    arg2->unk_2C.as_pu8 = D_800E2448;
    func_80047784(arg2, D_800E2448[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v & 0x9F7F);
    func_800A56E0(0x801);
    goto block_46;
block_39:
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto block_46;
    }
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 | 0x40000);
    ((S_8017558C_0 *)arg0)->unk_98 = (u16) (((S_8017558C_0 *)arg0)->unk_98 | 8);
    if (arg2->unk_2C.as_pu8 == D_800E23E0) {
        goto block_46;
    }
    arg2->unk_2C.as_pu8 = D_800E23E0;
    func_80047784(arg2, D_800E23E0[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    ((S_8017558C_0 *)arg0)->unk_96 = 5U;
    ((S_8017558C_0 *)arg0)->unk_9B = (u8) (((S_8017558C_0 *)arg0)->unk_9B + 1);
    if (((S_8017558C_0 *)arg0)->unk_B0 != 0) {
        goto block_46;
    }
    func_801708B8(arg0, arg1, arg2);
    goto block_46;
jt_c5:
    temp_v0_10 = ((S_8017558C_0 *)arg0)->unk_96;
    ((S_8017558C_0 *)arg0)->unk_96 = (u16) (temp_v0_10 - 1);
    if ((temp_v0_10 << 0x10) > 0) {
        goto block_46;
    }
    arg2->unk_06.as_s16 = 0;
    func_800AD594(arg3, 0x1000);
    ((S_8017558C_0 *)arg0)->unk_8C = D_80171A80;
    *D_8008346C = 0;
    arg3->unk_44.at02_u16.v = (u16) (arg3->unk_44.at02_u16.v & 0x7FFF);
block_46:
    return;
}
