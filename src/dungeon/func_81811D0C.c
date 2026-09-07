#include "common.h"

typedef struct S_80026D0C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80026D0C_0;   /* arg0 in func_80026D0C */

typedef struct S_80026D0C_1 {
    void * unk_00;
    void * unk_04;
    s16 unk_08;
} S_80026D0C_1;   /* temp_a1 in func_80026D0C */

typedef struct S_80026D0C_2 {
    void * unk_00;
    void * unk_04;
} S_80026D0C_2;   /* temp_v1_2 in func_80026D0C */

typedef struct S_80026D0C_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026D0C_3;   /* ((S_80026D0C_0 *)arg0)->unk_0C in func_80026D0C */

typedef struct S_80026D0C_4 {
    u8 pad_00[0xA];
    u8 unk_0A;
} S_80026D0C_4;   /* ((S_80026D0C_1 *)temp_a1)->unk_00 in func_80026D0C */

typedef struct S_80026D0C_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80026D0C_5;   /* ((S_80026D0C_2 *)temp_v1_2)->unk_04 in func_80026D0C */

typedef struct S_80026D0C_6 {
    u8 pad_00[0xB];
    u8 unk_0B;
} S_80026D0C_6;   /* ((S_80026D0C_2 *)temp_v1_2)->unk_00 in func_80026D0C */

typedef struct S_80026D0C_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026D0C_7;   /* ((S_80026D0C_3 *)(((S_80026D0C_0 *)arg0)->unk_0C))->unk_04 in func_80026D0C */



void func_80026D0C(S_80026D0C_0 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1;
    S_80026D0C_1 *temp_a1;
    S_80026D0C_2 *temp_v1_2;

    temp_v1 = ((arg1 % 72) % 9) * 0xB;
    ((S_80026D0C_7 *)(((S_80026D0C_3 *)(arg0->unk_0C))->unk_04))->unk_08 =
        (s16)(temp_v1 - 0x2B);
    temp_a2 = ((arg1 % 72) / 9) * 0x10;
    ((S_80026D0C_7 *)(((S_80026D0C_3 *)(arg0->unk_0C))->unk_04))->unk_0A =
        (s16)(temp_a2 + 0xF);
    temp_a1 = arg0->unk_10;
    temp_v0 = ((S_80026D0C_4 *)(temp_a1->unk_00))->unk_0A;
    temp_a1 = temp_a1->unk_04;
    temp_v0 = (u32)temp_v0 >> 1;
    temp_v0 -= 0x29;
    temp_a1->unk_08 = (s16)(temp_v1 + temp_v0);
    temp_v1_2 = arg0->unk_10;
    ((S_80026D0C_5 *)(temp_v1_2->unk_04))->unk_0A =
        (s16)(temp_a2 + ((((S_80026D0C_6 *)(temp_v1_2->unk_00))->unk_0B >> 1) + 0xF));
}
