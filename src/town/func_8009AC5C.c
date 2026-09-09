#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_80097D54_arg0.h"


extern s32 func_80098988();
extern s16 func_800C2AE8();




void func_800983BC(Rec_func_80097D54_arg0 *arg0, Rec_D_800E3D7C *arg1, s32 arg2) {
    s16 temp_a0;
    u16 temp_v0;
    s32 side_v0;
    s32 side_v1;

    arg1->unk_08.at02_s16.v = func_800C2AE8(arg1);
    temp_v0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0;
    if ((s16)temp_v0 < 0) {
        func_80098988(arg0, arg1, arg2);
        return;
    }
    temp_a0 = arg0->unk_10;
    switch (temp_a0) {
    case 0x400:
        arg1->unk_00.at00_s32.v += 0x120000;
        break;
    case 0xC00:
        arg1->unk_00.at00_s32.v -= 0x120000;
        break;
    case 0:
        arg1->unk_04.at00_s32.v += 0x120000;
        break;
    default:
        arg1->unk_04.at00_s32.v -= 0x120000;
        break;
    }
}
