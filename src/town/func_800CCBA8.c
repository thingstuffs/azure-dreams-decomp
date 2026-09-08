#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_800C4174(void *arg0, void *arg1, s32 arg2);




void func_800CA308(Rec_func_80094268_arg0 *arg0, Rec_D_800E3D7C *arg1, s32 arg2) {
    s32 delta;
    s32 delta2;
    s32 delta3;
    u16 timer;

    timer = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = timer;
    if ((timer << 16) <= 0) {
        func_800C4174(arg0, arg1, arg2);
        arg1->unk_00.at02_u16.v = arg0->unk_84.as_u16;
        arg1->unk_04.at02_s16.v = arg0->unk_86.as_u16;
        arg1->unk_08.at02_s16.v = 0;
        return;
    }

    delta = (s16)arg0->unk_84.as_u16 -
            (s16)arg1->unk_00.at02_u16.v;
    if (delta < 0) {
        delta += 7;
    }
    arg1->unk_00.at02_u16.v =
        (u16)(arg1->unk_00.at02_u16.v + (delta >> 3));

    delta2 = (s16)arg0->unk_86.as_u16 - arg1->unk_04.at02_s16.v;
    if (delta2 < 0) {
        delta2 += 7;
    }
    arg1->unk_04.at02_s16.v =
        (s16)((u16)arg1->unk_04.at02_s16.v + (delta2 >> 3));

    delta3 = -arg1->unk_08.at02_s16.v;
    if (delta3 < 0) {
        delta3 += 7;
    }
    arg1->unk_08.at02_s16.v =
        (s16)((u16)arg1->unk_08.at02_s16.v + (delta3 >> 3));
}
