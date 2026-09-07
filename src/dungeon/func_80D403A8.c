#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175BA8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 pad_B0[0x1];
    s8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    s8 unk_B5;
} S_80175BA8_0;   /* arg0 in func_80175BA8 */

typedef struct S_80175BA8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175BA8_1;   /* arg1 in func_80175BA8 */

typedef struct S_80175BA8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80175BA8_2;   /* arg3 in func_80175BA8 */

typedef struct S_80175BA8_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0xC];
    u16 unk_14;
} S_80175BA8_3;   /* arg2 in func_80175BA8 */

typedef struct S_80175BA8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80175BA8_4;   /* temp_v0_3 in func_80175BA8 */

typedef struct S_80175BA8_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_80175BA8_5;   /* temp_v0_4 in func_80175BA8 */

typedef struct S_80175BA8_6 {
    u8 pad_00[0x8];
    void * unk_08;
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
} S_80175BA8_6;   /* temp_a0 in func_80175BA8 */

typedef struct S_80175BA8_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175BA8_7;   /* temp_v1_2 in func_80175BA8 */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A56E0();
extern s32 func_800BCB04();

extern u8 D_80045C34[];
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2438[];
extern u8 D_800E2440[];
extern u8 D_800E2488[];
extern u8 D_80170CEC[];
extern u8 D_80171A80[];

void func_80175BA8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_a1;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_5;
    u16 temp_v0_6;
    s32 temp_v1;
    void *temp_a0;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1_2;

    temp_v1 = ((S_80175BA8_0 *)arg0)->unk_9B;
    switch (temp_v1) {
    case 0:
        goto block_0;
    case 1:
        goto block_21;
    case 2:
        goto block_25;
    default:
        goto block_done;
    }

block_0:
    ((S_80175BA8_1 *)arg1)->unk_14 = 0;
    ((S_80175BA8_1 *)arg1)->unk_10 = 0;
    ((S_80175BA8_1 *)arg1)->unk_0C = 0;
    temp_a1 = func_800BCB04(((S_80175BA8_1 *)arg1)->unk_02, ((S_80175BA8_1 *)arg1)->unk_06,
                            (s16)(((S_80175BA8_2 *)arg3)->unk_88 - 0x20))
              - ((S_80175BA8_2 *)arg3)->unk_88;
    if (((S_80175BA8_0 *)arg0)->unk_92.s < temp_a1) {
        temp_v0 = ((S_80175BA8_0 *)arg0)->unk_92.u + 0xC;
        ((S_80175BA8_0 *)arg0)->unk_92.u = temp_v0;
        if (temp_a1 >= (s16)temp_v0) {
            goto block_after_92;
        }
    }
    ((S_80175BA8_0 *)arg0)->unk_92.s = temp_a1;
block_after_92:
    if (((S_80175BA8_3 *)arg2)->unk_14 & 0x8000) {
        ((S_80175BA8_0 *)arg0)->unk_92.u = 0;
    }
    temp_v0_2 = ((S_80175BA8_0 *)arg0)->unk_96 + 1;
    ((S_80175BA8_0 *)arg0)->unk_96 = temp_v0_2;
    if (((s16)temp_v0_2 == 1) || (((S_80175BA8_3 *)arg2)->unk_14 & 0x8000)) {
        ((S_80175BA8_0 *)arg0)->unk_B5 = 1;
        temp_v0_3 = func_8003FD64(0x12, (u8 *)arg0 - 0x20);
        if (temp_v0_3 != NULL) {
            ((S_80175BA8_0 *)arg0)->unk_AC = temp_v0_3;
            ((S_80175BA8_4 *)temp_v0_3)->unk_10 = D_80170CEC;
            func_8004491C(temp_v0_3, D_80045C34);
            temp_v0_4 = (u8 *)temp_v0_3 + 0x20;
            ((S_80175BA8_5 *)temp_v0_4)->unk_38 = 5;
            ((S_80175BA8_5 *)temp_v0_4)->unk_40 = arg0;
            ((S_80175BA8_5 *)temp_v0_4)->unk_44 = arg1;
            temp_a0 = ((S_80175BA8_4 *)temp_v0_3)->unk_0C;
            ((S_80175BA8_6 *)temp_a0)->unk_10 = 0x40;
            ((S_80175BA8_6 *)temp_a0)->unk_14 |= 0xC;
            temp_v1_2 = ((S_80175BA8_4 *)temp_v0_3)->unk_08;
            ((S_80175BA8_7 *)temp_v1_2)->unk_02 = ((S_80175BA8_1 *)arg1)->unk_02;
            ((S_80175BA8_7 *)temp_v1_2)->unk_06 = ((S_80175BA8_1 *)arg1)->unk_06;
            ((S_80175BA8_7 *)temp_v1_2)->unk_0A = ((S_80175BA8_2 *)arg3)->unk_88;
            temp_a0 = ((S_80175BA8_4 *)temp_v0_3)->unk_0C;
            ((S_80175BA8_6 *)temp_a0)->unk_1E = 0xA00;
            ((S_80175BA8_6 *)temp_a0)->unk_1C = 0xA00;
            ((S_80175BA8_6 *)temp_a0)->unk_0E = 0;
            ((S_80175BA8_6 *)temp_a0)->unk_0D = 0;
            ((S_80175BA8_6 *)temp_a0)->unk_0C = 0;
            ((S_80175BA8_6 *)temp_a0)->unk_08 = D_800E2488;
        }
    }
    if (((S_80175BA8_0 *)arg0)->unk_92.s == 0) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_800E2438;
        func_80047784(arg2,
                      D_800E2438[((D_80083228 + ((S_80175BA8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80175BA8_0 *)arg0)->unk_96 = 2;
        ((S_80175BA8_0 *)arg0)->unk_9B++;
        if (!(((S_80175BA8_3 *)arg2)->unk_14 & 0x8000)) {
            func_800A56E0(0x800);
            goto block_20;
        }
        goto block_21;
    }
block_20:
    if (!(((S_80175BA8_3 *)arg2)->unk_14 & 0x8000)) {
        goto block_done;
    }

block_21:
    temp_v0_5 = ((S_80175BA8_0 *)arg0)->unk_96 - 1;
    ((S_80175BA8_0 *)arg0)->unk_96 = temp_v0_5;
    if (((temp_v0_5 << 0x10) <= 0) || (((S_80175BA8_3 *)arg2)->unk_14 & 0xE000)) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_800E2440;
        func_80047784(arg2,
                      D_800E2440[((D_80083228 + ((S_80175BA8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80175BA8_0 *)arg0)->unk_96 = 3;
        ((S_80175BA8_0 *)arg0)->unk_9B++;
    }
    if (((S_80175BA8_3 *)arg2)->unk_14 & 0x8000) {
block_25:
        temp_v0_6 = ((S_80175BA8_0 *)arg0)->unk_96 - 1;
        ((S_80175BA8_0 *)arg0)->unk_96 = temp_v0_6;
        if (((temp_v0_6 << 0x10) <= 0) || (((S_80175BA8_3 *)arg2)->unk_14 & 0x8000)) {
            ((S_80175BA8_0 *)arg0)->unk_96 = 0x1E;
            ((S_80175BA8_0 *)arg0)->unk_A8 = 0;
            ((S_80175BA8_0 *)arg0)->unk_B1 = 0;
            ((S_80175BA8_0 *)arg0)->unk_B2 = 0;
            ((S_80175BA8_0 *)arg0)->unk_B4 = 0;
            ((S_80175BA8_0 *)arg0)->unk_B3 = 0;
            ((S_80175BA8_0 *)arg0)->unk_9B++;
            ((S_80175BA8_0 *)arg0)->unk_98 &= 0xFFF7;
            ((S_80175BA8_3 *)arg2)->unk_06 = 0;
            ((S_80175BA8_0 *)arg0)->unk_8C = D_80171A80;
            D_8008346C = 0;
            (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        }
    }
block_done:
    return;
}
