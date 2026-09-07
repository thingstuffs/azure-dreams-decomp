#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_D_800E3D7C.h"



void func_8008F27C(Rec_D_800CFCB4 *arg0, Rec_D_800E3D7C *arg1, s32 arg2) {
    arg0->unk_35 = 1;
    arg1->unk_08.at00_s32.v = (s32) (arg2 << 0x10);
    arg1->unk_14.as_s32 = 0;
}
