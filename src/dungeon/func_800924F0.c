#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"



void func_80097C50(Rec_func_8008ACDC_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, Rec_D_800E3D7C *arg3) {
    arg0->unk_9A.as_s8 = 0x3A;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C.as_s32 = 0;
    arg0->unk_96.as_s16 = 0;
    arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 & ~0x20);
}
