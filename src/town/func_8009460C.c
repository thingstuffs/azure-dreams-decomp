#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"





extern s32 func_80094220(void *, void *, s32);
extern void func_80094984(void *, void *, s32);
extern void func_80095C80(void *);
extern s32 D_800D00E8;
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

void func_80091D6C(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, s32 arg2) {
    s16 temp_v0;
    s32 temp_s3;

    func_80095C80(arg1);
    if (arg0->unk_0A.as_s16 >= 15) {
        temp_s3 = (s32)((u32)(arg0->unk_34.as_s16 +
                   D_800D0454[21 - arg0->unk_0A.as_s16]) << 16);
        goto selector_join;
    } else {
        temp_s3 = (s32)((u32)arg0->unk_34.as_s16 << 16);
    }

selector_join:
    if (arg0->unk_0A.as_s16 == 19)
        func_80094984(&D_800D00E8, arg0, arg2);
    if (arg0->unk_0A.as_s16 == 15)
        func_80094984(&D_800D00F0, arg0, arg2);
    if (arg0->unk_0A.as_s16 == 12)
        func_80094984(&D_800D00F8, arg0, arg2);
    temp_v0 = (u16)arg0->unk_0A.as_s16 - 1;
    arg0->unk_0A.as_s16 = temp_v0;
    if ((s32)((u32)(u16)temp_v0 << 16) <= 0) {
        arg1->unk_0C.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_14.as_s32 = 0;
        func_80094220(arg0, arg1, arg2);
        return;
    }
    arg1->unk_14.as_s32 = temp_s3 - arg1->unk_08.at00_s32.v;
}
