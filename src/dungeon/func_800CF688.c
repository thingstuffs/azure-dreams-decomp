#include "common.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "records/Rec_func_800D4BD4_arg2.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D4DE8_0_pre {
    u16 unk_00;
} S_800D4DE8_0_pre;   /* the 0x2 bytes before arg0 in func_800D4DE8, addressed as arg0[-1] */



typedef struct S_800D4DE8_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D4DE8_2;   /* temp_a0 in func_800D4DE8 */

typedef struct S_800D4DE8_3 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    s16 unk_20;
} S_800D4DE8_3;   /* temp_v0_3 in func_800D4DE8 */

typedef struct S_800D4DE8_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800D4DE8_4;   /* temp_v0_2 in func_800D4DE8 */

typedef struct S_800D4DE8_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4DE8_5;   /* temp_s0 in func_800D4DE8 */

typedef struct S_800D4DE8_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800D4DE8_6;   /* global in func_800D4DE8 */

typedef struct S_800D4DE8_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4DE8_7;   /* ((S_800D4DE8_2 *)temp_a0)->unk_08 in func_800D4DE8 */

typedef struct S_800D4DE8_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800D4DE8_8;   /* ((Rec_func_800D4BD4_arg1 *)arg0)->unk_00 in func_800D4DE8 */



extern void *func_8003FC64(s32);
extern s32 rand(void);
extern void func_800D4BD4(void *, void *, void *, s32);
extern s32 D_800814A0;
extern u8 D_80083460[];
extern u8 D_800D4CB0[];
extern u8 D_800DDC40[];

void func_800D4DE8(void *arg0, Rec_func_800D4BD4_arg2 *arg1, s32 arg2) {
    s32 var_s1;
    u16 temp_v0;
    u16 temp_v0_4;
    S_800D4DE8_2 *temp_a0;
    S_800D4DE8_5 *temp_s0;
    void *temp_v0_2;
    S_800D4DE8_3 *temp_v0_3;
    u8 *global;

    temp_a0 = ((Rec_func_800D4BD4_arg1 *)arg0)->unk_24;
    arg1->unk_02.as_s16 =
        (s16)(((S_800D4DE8_7 *)(temp_a0->unk_08))->unk_02 +
              ((Rec_func_800D4BD4_arg1 *)arg0)->unk_3C);
    arg1->unk_06.as_s16 =
        (s16)(((S_800D4DE8_7 *)(temp_a0->unk_08))->unk_06 +
              ((Rec_func_800D4BD4_arg1 *)arg0)->unk_3E);
    arg1->unk_0A.as_s16 =
        (s16)(((S_800D4DE8_7 *)(temp_a0->unk_08))->unk_0A +
              ((Rec_func_800D4BD4_arg1 *)arg0)->unk_40);
    temp_v0 = ((Rec_func_800D4BD4_arg1 *)arg0)->unk_16 + 1;
    ((Rec_func_800D4BD4_arg1 *)arg0)->unk_16 = temp_v0;
    if ((s16)temp_v0 < 0x14) {
        var_s1 = 0;
        do {
            temp_v0_2 = func_8003FC64(0x212);
            if (temp_v0_2 != NULL) {
                func_800D4BD4(temp_v0_2, arg0, arg1, arg2);
                temp_v0_3 = (u8 *)temp_v0_2 + 0x20;
                temp_v0_3->unk_1E = 0xA;
                temp_v0_3->unk_20 = 0xA;
                ((S_800D4DE8_4 *)temp_v0_2)->unk_10 = D_800D4CB0;
                temp_s0 = ((S_800D4DE8_4 *)temp_v0_2)->unk_08;
                temp_s0->unk_0C =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                temp_s0->unk_10 =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                temp_s0->unk_14 =
                    ((rand() & 0x7FFF) - 0x4000) << 7;
                temp_s0->unk_0A =
                    temp_s0->unk_0A -
                    (D_800DDC40[((S_800D4DE8_8 *)(((Rec_func_800D4BD4_arg1 *)arg0)->unk_00))->unk_13] >> 1);
            }
            var_s1 += 1;
        } while (var_s1 < 4);
    }
    temp_v0_4 = ((Rec_func_800D4BD4_arg1 *)arg0)->unk_1E - 1;
    ((Rec_func_800D4BD4_arg1 *)arg0)->unk_1E = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        ((S_800D4DE8_0_pre *)arg0)[-1].unk_00 = ((S_800D4DE8_0_pre *)arg0)[-1].unk_00 | 0x8000;
        D_800814A0 |= 0x8000;
        global = D_80083460;
        ((S_800D4DE8_6 *)global)->unk_0A = ((S_800D4DE8_6 *)global)->unk_0A - 1;
    }
}
