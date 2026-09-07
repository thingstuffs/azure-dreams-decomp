#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801749A8_8 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801749A8_8;   /* temp_s0 in func_801749A8 */


typedef struct S_801749A8_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749A8_10;   /* ((S_801749A8_8 *)temp_s0)->unk_08 in func_801749A8 */

typedef struct S_801749A8_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801749A8_11;   /* ((Rec_D_80082E80 *)arg3)->unk_60.as_pv in func_801749A8 */


typedef struct S_801749A8_0_pre {
    u16 unk_00;
} S_801749A8_0_pre;   /* the 0x2 bytes before arg0 in func_801749A8, addressed as arg0[-1] */

typedef struct S_801749A8_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    s16 unk_A8;
} S_801749A8_0;   /* arg0 in func_801749A8 */


typedef struct S_801749A8_2 {
    u8 pad_00[0xC];
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    union { M2C_UNK * s; s32 u; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_801749A8_2;   /* temp_s0 in func_801749A8 */

typedef struct S_801749A8_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_801749A8_3;   /* temp_a1 in func_801749A8 */



typedef struct S_801749A8_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801749A8_6_pre;   /* the 0x14 bytes before temp_v1_3 in func_801749A8, addressed as temp_v1_3[-1] */

typedef struct S_801749A8_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801749A8_6;   /* temp_v1_3 in func_801749A8 */

typedef struct S_801749A8_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_801749A8_7;   /* temp_s0_2 in func_801749A8 */


extern s16 D_80083228[5];
extern s32 D_8006CD58[];
extern s32 D_8003E140[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern u8 D_80045340[];
extern u8 D_8014A000[];
extern s16 D_80174F48[];
extern s32 D_800814A0[3];
extern s32 D_80083460[3];
extern void *D_80170870[];
M2C_UNK func_8003E4FC();
M2C_UNK func_8003F540();
void *func_8003FC64();
M2C_UNK func_80041588();
M2C_UNK func_8004491C();
M2C_UNK func_800445E0();
s32 func_8003DB94();
s32 func_80047738();
s32 rand();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
void *func_800A504C();
M2C_UNK func_800A56E0();
s32 func_800ADC4C();
M2C_UNK func_800C77D0();
M2C_UNK func_801745E0();
s32 func_800498A0(void *, ...);
extern u8 *D_800DCEEC[];
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8017487C;
extern M2C_UNK D_80174FAC;
extern M2C_UNK D_80174FB4;
extern u8 D_80174FCC[];
extern u8 D_80174FCD[];
extern s32 D_80174FD0[];

void func_801749A8(void *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    M2C_UNK *temp_a1;
    s16 temp_a0;
    s32 temp_v0_2;
    s16 var_v1;
    u16 temp_v0;
    s16 temp_v0_3;
    u16 temp_v1_2;
    u8 temp_v1;
    u8 var_v0;
    S_801749A8_2 *temp_s0;
    S_801749A8_7 *temp_s0_2;
    void *temp_v1_3;
    u16 *temp_83460;

    temp_s0 = &D_80083160;
    temp_v1 = ((S_801749A8_0 *)arg0)->unk_9B;
    var_v0 = temp_v1 < 9U;
    if (var_v0 == 0) {
        goto block_32;
    }
    (void)jt_keep; goto *D_80170870[(u32)(temp_v1)];
jt_c0:
    ((S_801749A8_0 *)arg0)->unk_9B = (u8)(((S_801749A8_0 *)arg0)->unk_9B + 1);
    return;
jt_c1:
    func_80041588(&D_80174FAC, &D_80174FCC, 0);
    ((S_801749A8_0 *)arg0)->unk_A8 = 0;
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
    ((Rec_D_80082E80 *)arg3)->unk_8A = (u16) ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v;
jt_c2:
    temp_a0 = ((s32) (*D_80083228 + (s16) ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v + 0x100) >> 9) & 7;
    if (D_80174FCC[0] == 0) {
        goto block_7;
    }
    if (temp_a0 == 2) {
        goto block_10;
    }
block_7:
    if (temp_a0 == 2) {
        return;
    }
    temp_v0 = ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v + 0x200;
    ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v = temp_v0;
    return;
block_10:
    func_80041588(&D_80174FAC, &D_80174FCC, 1);
    func_8003F540(0, *D_8006CD58, 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), NULL);
    D_80174FCD[0] = 0;
    func_8003E4FC(0xFF, (s32) D_8003E140, &D_80174FCD);
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    ((S_801749A8_0 *)arg0)->unk_96 = 0x10U;
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
jt_c3:
    temp_v1_2 = ((S_801749A8_0 *)arg0)->unk_96;
    temp_v0 = temp_v1_2 - 1;
    ((S_801749A8_0 *)arg0)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_15;
    }
    var_v0 = D_80174FCD[0];
    ((S_801749A8_0 *)arg0)->unk_96 = temp_v1_2;
    if (var_v0 == 0) {
        return;
    }
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
    func_800A56E0(0x300);
    return;
block_15:
    temp_a1 = D_800DCEEC[func_800498A0(arg3)];
    temp_s0->unk_A8 = (u8) (temp_s0->unk_A8 + ((s32) (((S_801749A8_3 *)temp_a1)->unk_00 - temp_s0->unk_A8) / (s16) ((S_801749A8_0 *)arg0)->unk_96));
    temp_s0->unk_A9 = (u8) (temp_s0->unk_A9 + ((s32) (((S_801749A8_3 *)temp_a1)->unk_01 - temp_s0->unk_A9) / (s16) ((S_801749A8_0 *)arg0)->unk_96));
    temp_s0->unk_AA = (u8) (temp_s0->unk_AA + ((s32) (((S_801749A8_3 *)temp_a1)->unk_02 - temp_s0->unk_AA) / (s16) ((S_801749A8_0 *)arg0)->unk_96));
    return;
jt_c4:
    temp_s0 = func_8003FC64(0x12);
    if (temp_s0 == 0) {
        goto block_32;
    }
    temp_s0->unk_10.s = &D_8017487C;
    func_8004491C(temp_s0, D_80045340);
    ((S_801749A8_0 *)arg0)->unk_A4 = temp_s0;
    ((S_801749A8_10 *)(((S_801749A8_8 *)temp_s0)->unk_08))->unk_00 = (s32) arg1->unk_00.at00_s32.v;
    ((S_801749A8_10 *)(((S_801749A8_8 *)temp_s0)->unk_08))->unk_04 = (s32) arg1->unk_04.at00_s32.v;
    ((S_801749A8_10 *)(((S_801749A8_8 *)temp_s0)->unk_08))->unk_08 = (s32) arg1->unk_08.at00_s32.v;
    temp_s0 = temp_s0->unk_0C.s;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    temp_s0->unk_0C.u = 0x808080;
    temp_v0_2 = func_800498A0(arg3) - 1;
    var_v1 = temp_v0_2;
    if ((temp_v0_2 << 0x10) >= 0) {
        goto block_20;
    }
    var_v1 = rand() % 3;
block_20:
    func_8003DB94(temp_s0, &D_8014A000[*(((s32) (var_v1 << 0x10) >> 0x10) + &D_80174FB4)], 0);
    arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v | 0x80);
    ((S_801749A8_0 *)arg0)->unk_96 = 0U;
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
    func_801745E0(arg0, arg1, arg2);
    return;
jt_c5:
    temp_s0 = ((S_801749A8_0 *)arg0)->unk_A4;
    temp_s0 = temp_s0->unk_0C.s;
    if (!(temp_s0->unk_14 & 0xE000)) {
        goto block_24;
    }
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
jt_c6:
block_24:
    if (((S_801749A8_0 *)arg0)->unk_9B != 6) {
        return;
    }
    temp_v0_2 = func_800ADC4C(arg1, D_80174FD0[0], D_80174F48[0], &D_800DCF5C);
    if (temp_v0_2 == 0) {
        goto block_32;
    }
    ((S_801749A8_0 *)arg0)->unk_96 = 0x10U;
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
    func_800A18E8(((Rec_D_80082E80 *)arg3)->unk_12.at01_u8.v, 3);
    func_8009A3D0(arg2->unk_24, arg2->unk_25, 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    temp_s0->unk_10.u = temp_s0->unk_10.u | 0x80000000;
    return;
jt_c7:
    temp_v0_2 = func_800A504C(arg2, arg3);
    ((Rec_D_80082E80 *)arg3)->unk_60.as_pv = (void *) temp_v0_2;
    if (temp_v0_2 == 0) {
        goto block_32;
    }
    ((S_801749A8_0 *)arg0)->unk_96 = 0x10U;
    ((S_801749A8_0 *)arg0)->unk_9B = (u8) (((S_801749A8_0 *)arg0)->unk_9B + 1);
    ((S_801749A8_11 *)(((Rec_D_80082E80 *)arg3)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)arg3)->unk_28.at02_u16.v;
    temp_v1_3 = ((Rec_D_80082E80 *)arg3)->unk_60.as_pv;
    temp_s0_2 = ((S_801749A8_6_pre *)temp_v1_3)[-1].unk_00;
    func_80047738(temp_s0_2, *(temp_s0_2->unk_2C + (((s32) (*D_80083228 + (s16) ((S_801749A8_6 *)temp_v1_3)->unk_2A + 0x100) >> 9) & 7)), temp_s0_2->unk_04);
    temp_s0_2->unk_14 = (u16) (temp_s0_2->unk_14 & 0xFFFE);
jt_c8:
    temp_v0_3 = ((S_801749A8_0 *)arg0)->unk_96 - 1;
    ((S_801749A8_0 *)arg0)->unk_96 = temp_v0_3;
    if (temp_v0_3 > 0) {
        goto block_32;
    }
    ((S_801749A8_11 *)(((Rec_D_80082E80 *)arg3)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)arg3)->unk_8A;
    ((S_801749A8_0_pre *)arg0)[-1].unk_00 = (u16) (((S_801749A8_0_pre *)arg0)[-1].unk_00 | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
    temp_83460 = (u16 *)&D_80083460;
    temp_83460[5] = (u16)(temp_83460[5] - 1);
    ((Rec_D_80082E80 *)arg3)->unk_6D = 0;
block_32:
    return;
}
