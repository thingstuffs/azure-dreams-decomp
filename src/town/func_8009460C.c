#include "common.h"

typedef struct S_80091D6C_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x28];
    s16 unk_34;
} S_80091D6C_0;   /* arg0 in func_80091D6C */

typedef struct S_80091D6C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80091D6C_1;   /* arg1 in func_80091D6C */



extern s32 func_80094220(void *, void *, s32);
extern void func_80094984(void *, void *, s32);
extern void func_80095C80(void *);
extern s32 D_800D00E8;
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

void func_80091D6C(S_80091D6C_0 *arg0, S_80091D6C_1 *arg1, s32 arg2) {
    s16 temp_v0;
    s32 temp_s3;

    func_80095C80(arg1);
    if (arg0->unk_0A >= 15) {
        temp_s3 = (s32)((u32)(arg0->unk_34 +
                   D_800D0454[21 - arg0->unk_0A]) << 16);
        goto selector_join;
    } else {
        temp_s3 = (s32)((u32)arg0->unk_34 << 16);
    }

selector_join:
    if (arg0->unk_0A == 19)
        func_80094984(&D_800D00E8, arg0, arg2);
    if (arg0->unk_0A == 15)
        func_80094984(&D_800D00F0, arg0, arg2);
    if (arg0->unk_0A == 12)
        func_80094984(&D_800D00F8, arg0, arg2);
    temp_v0 = (u16)arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((s32)((u32)(u16)temp_v0 << 16) <= 0) {
        arg1->unk_0C = 0;
        arg1->unk_10 = 0;
        arg1->unk_14 = 0;
        func_80094220(arg0, arg1, arg2);
        return;
    }
    arg1->unk_14 = temp_s3 - arg1->unk_08;
}
