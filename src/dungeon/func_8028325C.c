#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083460.h"

typedef struct S_8001625C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
} S_8001625C_0;   /* state in func_8001625C */


typedef struct S_8001625C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8001625C_2;   /* temp_v0 in func_8001625C */

typedef struct S_8001625C_3 {
    s8 unk_00;
} S_8001625C_3;   /* var_s0 in func_8001625C; pointer addresses record offset 0x30B2 */


M2C_UNK func_80041284();                   /* extern */
s32 func_80048D00();                                /* extern */
M2C_UNK bzero();          /* extern */
extern s32 D_80012D60;
extern s32 D_80080A80;
extern M2C_UNK *D_80080A90;
extern M2C_UNK D_80080AE0;
extern M2C_UNK D_80080AE8;
extern M2C_UNK D_80080E18;
extern M2C_UNK D_80080E20;
extern M2C_UNK D_80080E30;
extern M2C_UNK D_80080EE8;
extern s16 D_80081468[3];
extern u8 D_80082E6B;
extern M2C_UNK D_80083460;
extern s16 D_800DCE68;
extern M2C_UNK D_800DCF4E;
extern s8 D_800DCF4F;
extern s8 D_800DCF58;
extern s8 D_800DCF5B;
extern s32 D_800E296C;
extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;
extern s16 D_800E3CCC;
extern s16 D_800E3CCE;
extern s32 D_800E3D70;
extern s8 D_800E3E40;
extern M2C_UNK D_8014A000;

void func_8001625C(void) {
    M2C_UNK *state;
    M2C_UNK *var_s0;
    s16 *temp_v1;
    s32 *temp_v0;

    bzero(&D_800E3548, 0x100);
    bzero(&D_800E36C8, 0x300);
    state = &D_80083460;
    ((S_8001625C_0 *)state)->unk_08 = 0;
    ((S_8001625C_0 *)state)->unk_0A = 0;
    ((S_8001625C_0 *)state)->unk_14 = 0;
    ((S_8001625C_0 *)state)->unk_0C = 0;
    ((S_8001625C_0 *)state)->unk_10 = 0;
    ((Rec_D_80083460 *)(&D_80083460))->unk_00 = 0x100;
    ((S_8001625C_0 *)state)->unk_02 = 0;
    ((S_8001625C_0 *)state)->unk_1C = 0;
    ((S_8001625C_0 *)state)->unk_04 = 0;
    D_800DCE68 = 0;
    D_800E3E40 = 0;
    D_800E296C = 0;
    D_800E3CCC = 0;
    D_800E3CCE = 0;
    D_800DCF4F = 0;
    D_80080A90 = &D_8014A000;
    D_800E3D70 = 0;
    temp_v0 = &D_800E3D70;
    ((S_8001625C_2 *)temp_v0)->unk_04 = 0;
    ((S_8001625C_2 *)temp_v0)->unk_08 = 0;
    D_800DCF58 = 1;
    D_800DCF5B = 0;
    if (D_80082E6B != 5) {
        temp_v1 = D_80081468;
        if (temp_v1[2] >= 0x64) {
            temp_v1[2] = 0x63;
        }
        var_s0 = (M2C_UNK *)0x800E0000;
        if ((u32) D_80012D60 < (u32) temp_v1[2]) {
            D_80012D60 = (s32) temp_v1[2];
            goto block_5;
        }
    } else {
block_5:
        var_s0 = (M2C_UNK *)0x800E0000;
    }
    if (((S_8001625C_3 *)((u8 *)var_s0 - 0x30B2))->unk_00 == 0) {
        func_80041284(&D_80080AE0);
        func_80041284(&D_80080AE8);
        func_80041284(&D_80080E18);
        func_80041284(&D_80080E20);
        func_80041284(&D_80080EE8);
        func_80041284(&D_80080E30);
        D_80080A80 = func_80048D00();
        ((S_8001625C_3 *)((u8 *)var_s0 - 0x30B2))->unk_00 = 1;
    }
}

/* MECHANISM: Named D_80083460 and D_80081468 bases reproduce the retail held-address forms.
   D_800E3D70 and D_80012D60 use their symbol addresses without duplicated byte displacements.
   Holding the 0x800E0000 page in s0 removes one addiu and closes the branch-displacement cascade. */
