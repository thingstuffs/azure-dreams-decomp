#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A0.h"

typedef struct S_8195281C_0_pre {
    u16 unk_00;
} S_8195281C_0_pre;   /* the 0x2 bytes before arg0 in func_8195281C, addressed as arg0[-1] */

typedef struct S_8195281C_0 {
    s32 unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x8];
    union { u16 u; s16 s; } unk_14;   /* accessed as both */
    u16 unk_16;
    s16 unk_18;
} S_8195281C_0;   /* arg0 in func_8195281C */

typedef struct S_8195281C_1 {
    union { s32 i; void * p; } unk_00;   /* accessed as both */
} S_8195281C_1;   /* D_800814A8 in func_8195281C */

typedef struct S_8195281C_2 {
    u8 pad_00[0xA6];
    u16 unk_A6;
    u8 unk_A8;
} S_8195281C_2;   /* temp_v1_7 in func_8195281C */

typedef struct S_8195281C_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7D];
    u8 unk_A9;
} S_8195281C_3;   /* temp_v1_3 in func_8195281C */

typedef struct S_8195281C_4 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8195281C_4;   /* temp_v1_5 in func_8195281C */

typedef struct S_8195281C_5_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8195281C_5_pre;   /* the 0x14 bytes before temp_a0 in func_8195281C, addressed as temp_a0[-1] */

typedef struct S_8195281C_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8195281C_5;   /* temp_a0 in func_8195281C */

typedef struct S_8195281C_6 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_8195281C_6;   /* var_a1 in func_8195281C */

typedef struct S_8195281C_7 {
    u8 pad_00[0x60];
    void * unk_60;
} S_8195281C_7;   /* D_800E3D7C[0] in func_8195281C */

typedef struct S_8195281C_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8195281C_8;   /* temp_v1_2 in func_8195281C */


typedef struct S_8195281C_10 {
    u8 pad_00[0x60];
    void * unk_60;
    u8 pad_64[0x90];
    M2C_UNK * unk_F4;
} S_8195281C_10;   /* ((S_8195281C_1 *)D_800814A8)->unk_00.i in func_8195281C */


extern u8 D_800DF334[];
extern int D_800814A8[4];
extern u16 D_80082E94;
extern u8 *D_800E3D7C[];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
M2C_UNK func_80024330() __attribute__((noreturn));
M2C_UNK func_80024908();
M2C_UNK func_800A56E0();
M2C_UNK func_800B835C();
M2C_UNK func_800B8C20();
extern u8 D_80024980;
extern M2C_UNK D_80024998;
extern s16 D_800249A4;
extern s16 D_800249A6;

void func_8195281C(void *arg0, void *arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 sp10[2];
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_v1;
    void *temp_a0;
    S_8195281C_6 *var_a1;
    u8 *temp_v1_2;
    S_8195281C_3 *temp_v1_3;
    u16 temp_v0_3;
    u16 temp_v1_4;
    S_8195281C_4 *temp_v1_5;
    u16 temp_v1_6;
    S_8195281C_2 *temp_v1_7;
    void **temp_a0_base;

    var_a1 = arg1;
    temp_v1 = ((S_8195281C_0 *)arg0)->unk_0A.s;
    ((S_8195281C_0 *)arg0)->unk_16 = (u16) (((S_8195281C_0 *)arg0)->unk_16 + 1);
    if ((u32) temp_v1 >= 5U) {
        goto block_27;
    }
    (void)jt_keep; goto *D_80024008[(s32) temp_v1];
jt_c0:
    sp10[0] = 0x01000340;
    sp10[1] = 0x200020;
    func_800B835C(D_800DF334, sp10, 1, 0);
    sp10[0] = 0x01000360;
    func_800B835C(&D_80024980, sp10, 1, 0);
    ((S_8195281C_10 *)(((S_8195281C_1 *)D_800814A8)->unk_00.i))->unk_F4 = &D_80024998;
    func_800B8C20(((S_8195281C_0 *)arg0)->unk_00 - 0x20, ((S_8195281C_0 *)arg0)->unk_04, 0, 0);
    ((S_8195281C_0 *)arg0)->unk_0A.s = (s16) ((u16) ((S_8195281C_0 *)arg0)->unk_0A.s + 1);
jt_c1:
    temp_a0_base = (void **) D_800814A8;
    if (!(*((S_8195281C_0 *)arg0)->unk_04 & 0x80)) {
        goto block_27;
    }
    temp_v1_7 = *temp_a0_base;
    ((S_8195281C_0 *)arg0)->unk_18 = 0x12;
    temp_v1_7->unk_A6 = (u16) (temp_v1_7->unk_A6 - 1);
    temp_v1_7->unk_A8 = (u8) ((S_8195281C_0 *)arg0)->unk_08;
    temp_v1_3 = *temp_a0_base;
    temp_v1_3->unk_A9 = (u8) ((S_8195281C_0 *)arg0)->unk_09;
    temp_v1_3 = *temp_a0_base;
    D_800249A4 = 0;
    temp_v0_3 = ((S_8195281C_0 *)arg0)->unk_0A.u;
    temp_v1_4 = temp_v1_3->unk_2A;
    ((S_8195281C_0 *)arg0)->unk_0A.u = temp_v0_3 + 1;
    ((S_8195281C_0 *)arg0)->unk_14.u = temp_v1_4;
    func_80024330();
    return;
jt_c2:
    if (((S_8195281C_0 *)arg0)->unk_18 != 8) {
        goto block_8;
    }
    func_800A56E0(0x300);
block_8:
    temp_v0 = (u16) ((S_8195281C_0 *)arg0)->unk_18 - 1;
    ((S_8195281C_0 *)arg0)->unk_18 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_28;
    }
    temp_v1_5 = ((S_8195281C_1 *)D_800814A8)->unk_00.p;
    ((S_8195281C_0 *)arg0)->unk_18 = 0x20;
    func_80024908(arg0 - 0x20, ((S_8195281C_0 *)arg0)->unk_14.s, ((S_8195281C_0 *)arg0)->unk_09, temp_v1_5->unk_60);
    ((S_8195281C_0 *)arg0)->unk_0A.s = (u16) ((S_8195281C_0 *)arg0)->unk_0A.s + 1;
    func_80024330();
    return;
jt_c3:
    temp_a0 = ((S_8195281C_10 *)(((S_8195281C_1 *)D_800814A8)->unk_00.i))->unk_60;
    if (temp_a0 == NULL) {
        goto block_18;
    }
    var_a1 = ((S_8195281C_5_pre *)temp_a0)[-1].unk_00;
    ((S_8195281C_5 *)temp_a0)->unk_1C = (s32) (((S_8195281C_5 *)temp_a0)->unk_1C | 0x10000000);
    var_a1->unk_0C.at00.v = (u8) (var_a1->unk_0C.at00.v - 4);
    var_a1->unk_0C.at01.v = (u8) (var_a1->unk_0C.at01.v - 4);
    var_a1->unk_0C.at02.v = (u8) (var_a1->unk_0C.at02.v - 4);
    if ((u8) var_a1->unk_0C.at00.v >= 0x20U) {
        goto block_14;
    }
    var_a1->unk_0C.at00.v = 0x20U;
block_14:
    if ((u8) var_a1->unk_0C.at01.v >= 0x20U) {
        goto block_16;
    }
    var_a1->unk_0C.at01.v = 0x20U;
block_16:
    if ((u8) var_a1->unk_0C.at02.v >= 0x20U) {
        goto block_18;
    }
    var_a1->unk_0C.at02.v = 0x20U;
block_18:
    if (D_80082E94 & 0x8000) {
        goto block_21;
    }
    temp_v0_2 = (u16) ((S_8195281C_0 *)arg0)->unk_18 - 1;
    ((S_8195281C_0 *)arg0)->unk_18 = temp_v0_2;
    if ((temp_v0_2 << 0x10) >= 0) {
        goto block_28;
    }
block_21:
    temp_a0 = ((S_8195281C_7 *)(D_800E3D7C[0]))->unk_60;
    if (temp_a0 == NULL) {
        goto block_23;
    }
    var_a1 = ((S_8195281C_5_pre *)temp_a0)[-1].unk_00;
    var_a1->unk_0C.at00u.v = 0x808080;
block_23:
    temp_v1_6 = ((S_8195281C_0 *)arg0)->unk_0A.u;
    D_800249A4 = 1;
    ((S_8195281C_0 *)arg0)->unk_0A.u = temp_v1_6 + 1;
    func_80024330();
    return;
jt_c4:
    if (D_800249A6 != 0) {
        goto block_28;
    }
    temp_v1_2 = (u8 *) D_80083460;
    ((S_8195281C_8 *)temp_v1_2)->unk_0C = 0;
    ((S_8195281C_8 *)temp_v1_2)->unk_0A = (u16) (((S_8195281C_8 *)temp_v1_2)->unk_0A - 1);
    ((S_8195281C_0_pre *)arg0)[-1].unk_00 = (u16) (((S_8195281C_0_pre *)arg0)[-1].unk_00 | 0x8000);
    ((Rec_D_800814A0 *)D_800814A0)->unk_00 = (s32) (((Rec_D_800814A0 *)D_800814A0)->unk_00 | 0x8000);
block_27:
block_28:
    D_800249A6 = 0;
    return;
}
