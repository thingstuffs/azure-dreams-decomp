#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173C5C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xA];
    s16 unk_AE;
} S_80173C5C_0;   /* arg0 in func_80173C5C */




typedef struct S_80173C5C_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173C5C_4;   /* temp_counter in func_80173C5C */


extern s16 D_80083228[5];
extern u8 D_80173FD0[];
extern u8 D_80173FB8[];
extern s32 D_80083460[3];
extern s32 D_80170F68;
extern void *D_80170878[];
M2C_UNK func_800A2B04();
M2C_UNK func_800A48F0();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A6D30();
extern u8 D_80173FD8;
extern M2C_UNK D_80173FE0;

void func_80173C5C(S_80173C5C_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u8 *temp_a1;
    u16 *temp_counter;
    s32 temp_v1_3;
    u16 temp_v1_2;
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_state;
    s32 temp_a0;

    temp_v1 = arg0->unk_9B;
    arg0->unk_96.s = (u16) (arg0->unk_96.s - 1);
    if (temp_v1 >= 8U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_80170878[(u32)(temp_v1)];
jt_c0:
jt_c4:
    func_800A56E0(0x51C);
    temp_v1_2 = arg2->unk_14.at00_u16.v;
    if (!(temp_v1_2 & 0x8000)) {
        goto block_5;
    }
    arg0->unk_9B = 7;
    goto block_20;
block_5:
    if (!(temp_v1_2 & 0xE000)) {
        goto block_20;
    }
    arg2->unk_2C.as_pu8 = &D_80173FD8;
    func_80047784(arg2, (&D_80173FD8)[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    arg0->unk_98 = (u16) (arg0->unk_98 | 8);
    arg1->unk_14.as_s32 = 0xFFF00000;
    arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 & 0xF7FFFFFF);
    arg0->unk_A0 = 0;
    temp_state = arg0->unk_9B;
    temp_v1 = 10;
    arg0->unk_96.s = temp_v1;
    goto block_e60;
jt_c1:
jt_c5:
    temp_v0 = arg0->unk_90;
    temp_v1_3 = arg0->unk_A0;
    temp_a0 = arg0->unk_96.u;
    arg0->unk_90 = temp_v0 - temp_v1_3;
    if (temp_a0 == 0) {
        goto block_10;
    }
    temp_v0 = temp_v1_3;
    temp_v1_3 = arg1->unk_14.as_s32;
    arg0->unk_A0 = (s32) (temp_v0 + temp_v1_3);
    arg1->unk_14.as_s32 = (s32) (arg1->unk_14.as_s32 + 0x30000);
block_10:
    temp_v0 = arg0->unk_90;
    temp_v1_3 = arg0->unk_A0;
    temp_a0 = arg0->unk_96.u;
    arg0->unk_90 = temp_v0 + temp_v1_3;
    if (temp_a0 > 0) {
        goto block_20;
    }
    arg0->unk_90 = 0;
    arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF7);
    arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 | 0x8000000);
    goto block_e5c;
jt_c2:
jt_c6:
    arg0->unk_98 = (u16) (arg0->unk_98 & 0xFFF7);
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
    arg2->unk_2C.as_pu8 = &D_80173FE0;
    func_80047784(arg2, ((u8 *) ((u32) ((((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32) &D_80173FE0)))[0], 0);
    goto block_e5c;
jt_c3:
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto block_20;
    }
    arg2->unk_2C.as_pu8 = D_80173FD0;
    func_80047784(arg2, D_80173FD0[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    block_e5c:
    temp_state = arg0->unk_9B;
    block_e60:
    arg0->unk_9B = (u8) (temp_state + 1);
    goto block_20;
jt_c7:
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto block_20;
    }
    arg2->unk_2C.as_pu8 = D_80173FB8;
    func_80047784(arg2, D_80173FB8[((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    temp_counter = (u16 *) D_80083460;
    ((S_80173C5C_4 *)temp_counter)->unk_0A = (u16) (((S_80173C5C_4 *)temp_counter)->unk_0A - 1);
    func_800A4ACC(arg3);
    arg3->unk_6D.as_s8 = 0;
    arg3->unk_44.at02_u16.v = (u16) (arg3->unk_44.at02_u16.v & 0x7FFF);
    arg0->unk_8C = &D_80170F68;
    arg0->unk_98 = (u16) (arg0->unk_98 | 0x8000);
    arg0->unk_AE = (s16) ((func_800A6D30() & 7) + 8);
    func_800A48F0(arg3, 0x1A, (s8) arg0->unk_AE);
block_20:
    return;
}
