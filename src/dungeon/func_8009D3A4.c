#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


void func_800A2B04(Rec_D_800E3D7C *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00.at02_s16.v = (s16) (((s32) (arg1 << 0x10) >> 0xA) + 0x20);
    arg0->unk_04.at02_s16.v = (s16) (((s32) (arg2 << 0x10) >> 0xA) + 0x20);
}
