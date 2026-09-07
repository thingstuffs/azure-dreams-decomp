#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8002421C();
extern M2C_UNK func_8003DB94();
extern M2C_UNK func_800478B8();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s16 D_80083160[];
extern u8 D_800DEAE0[];

typedef struct S_8185CB30_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x10];
    u16 unk_1C;
    s16 unk_1E;
    u16 unk_20;
    u16 unk_22;
    s16 unk_24;
} S_8185CB30_0;   /* arg0 in func_8185CB30 */

typedef struct S_8185CB30_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8185CB30_1;   /* temp_v1 in func_8185CB30 */

typedef struct S_8185CB30_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8185CB30_2;   /* arg1 in func_8185CB30 */

typedef struct S_8185CB30_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_8185CB30_3;   /* arg2 in func_8185CB30 */

void func_8185CB30(S_8185CB30_0 *arg0, S_8185CB30_2 *arg1, S_8185CB30_3 *arg2)
{
    s16 temp_v0_2;
    u16 temp_a0;
    u16 temp_v0;
    s16 *temp_s3;
    S_8185CB30_1 *temp_v1;

    temp_v1 = arg0->unk_00;
    temp_v1->unk_14 =
        (u16)(temp_v1->unk_14 + 1);
    temp_s3 = D_80083160;
    temp_a0 = arg0->unk_22;
    temp_v0 = temp_a0 + 1;
    arg0->unk_22 = temp_v0;
    if ((s16)temp_v0 >= 8) {
        arg0->unk_22 = (u16)(temp_a0 - 7);
    }
    if ((s16)arg0->unk_22 ==
        arg0->unk_24) {
        func_8002421C(arg0->unk_00, arg1);
    }
    if (arg0->unk_1E < 0xC1) {
        arg0->unk_1E =
            (s16)((u16)arg0->unk_1E + 8);
    }
    temp_v0_2 = arg0->unk_1C +
        (u16)arg0->unk_1E;
    arg0->unk_1C = (u16)temp_v0_2;
    arg0->unk_1C = (u16)(temp_v0_2 % 0x1000);
    arg0->unk_20 =
        (u16)(arg0->unk_20 + 4);
    arg1->unk_02 =
        (s16)(arg0->unk_06 +
        ((s32)((func_800644B8((s16)arg0->unk_1C) >> 4) *
        (s16)arg0->unk_20) >> 8));
    arg1->unk_06 =
        (s16)(arg0->unk_0A +
        ((s32)((func_80064584((s16)arg0->unk_1C) >> 4) *
        (s16)arg0->unk_20) >> 8));
    arg2->unk_1A =
        (s16)((s32)(0 - ((func_80064584(
        (s16)arg0->unk_1C -
        temp_s3[100]) >> 4) << 8)) >> 8);
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        func_8003DB94(arg2, D_800DEAE0, 0);
    }
}
