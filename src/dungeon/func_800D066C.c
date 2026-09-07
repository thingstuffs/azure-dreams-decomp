#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D5DCC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800D5DCC_0;   /* temp_v0 in func_800D5DCC */


typedef struct S_800D5DCC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800D5DCC_2;   /* temp_a0 in func_800D5DCC */

typedef struct S_800D5DCC_3 {
    s16 unk_00;
    s16 unk_02;
} S_800D5DCC_3;   /* temp_s0 in func_800D5DCC */

typedef struct S_800D5DCC_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800D5DCC_4;   /* temp_a0_2 in func_800D5DCC */

typedef struct S_800D5DCC_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800D5DCC_5;   /* temp_a1 in func_800D5DCC */

typedef struct S_800D5DCC_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D5DCC_6;   /* temp_a2 in func_800D5DCC */

typedef struct S_800D5DCC_7 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_800D5DCC_7;   /* temp_s0_2 in func_800D5DCC */

typedef struct S_800D5DCC_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D5DCC_8;   /* ((S_800D5DCC_0 *)temp_v0)->unk_08 in func_800D5DCC */

typedef struct S_800D5DCC_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D5DCC_9;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_800D5DCC */

typedef struct S_800D5DCC_10 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800D5DCC_10;   /* ((S_800D5DCC_0 *)temp_v0)->unk_0C in func_800D5DCC */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 rand();

extern u8 D_800D5AC0[];
extern u8 D_800D5CA0[];
extern s16 D_800E2468[];

void func_800D5DCC(Rec_D_800E3D7C *arg0, s16 arg1, s32 arg2)
{
    S_800D5DCC_2 *temp_a0;
    S_800D5DCC_4 *temp_a0_2;
    S_800D5DCC_5 *temp_a1;
    S_800D5DCC_6 *temp_a2;
    S_800D5DCC_3 *temp_s0;
    S_800D5DCC_7 *temp_s0_2;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        ((S_800D5DCC_0 *)temp_v0)->unk_10 = D_800D5CA0;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)temp_v0)->unk_08))->unk_02 =
            ((S_800D5DCC_9 *)(arg0->unk_08.at00_pv.v))->unk_02;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)temp_v0)->unk_08))->unk_06 =
            ((S_800D5DCC_9 *)(arg0->unk_08.at00_pv.v))->unk_06;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)temp_v0)->unk_08))->unk_0A =
            ((S_800D5DCC_9 *)(arg0->unk_08.at00_pv.v))->unk_0A - 0x14;
        temp_s0 = ((arg1 >> 7) & 0x1C) + (u8 *)D_800E2468;
        temp_a0 = ((S_800D5DCC_0 *)temp_v0)->unk_08;
        temp_a0->unk_02 += temp_s0->unk_00 * 0x10;
        temp_a0_2 = ((S_800D5DCC_0 *)temp_v0)->unk_08;
        temp_a0_2->unk_06 += temp_s0->unk_02 * 0x10;
        ((S_800D5DCC_10 *)(((S_800D5DCC_0 *)temp_v0)->unk_0C))->unk_06 = 6;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)temp_v0)->unk_08))->unk_0C =
            ((rand(temp_a0_2) & 0x7FFF) - 0x4000) << 6;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)temp_v0)->unk_08))->unk_10 =
            ((rand() & 0x7FFF) - 0x4000) << 6;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)temp_v0)->unk_08))->unk_14 =
            ((rand() & 0x7FFF) - 0x4000) << 5;
        temp_a1 = ((S_800D5DCC_0 *)temp_v0)->unk_08;
        temp_a1->unk_0C += temp_s0->unk_00 * 0x160000;
        temp_s0_2 = (u8 *)temp_v0 + 0x20;
        temp_a2 = ((S_800D5DCC_0 *)temp_v0)->unk_08;
        temp_a2->unk_10 += temp_s0->unk_02 * 0x160000;
        temp_s0_2->unk_14 = arg1;
        temp_s0_2->unk_32 = 7;
        temp_s0_2->unk_34 = 7;
        func_8004491C(temp_v0, D_800D5AC0, temp_a2);
        ((S_800D5DCC_0 *)temp_v0)->unk_20 = arg2;
        temp_s0_2->unk_08 = arg2;
    }
}
