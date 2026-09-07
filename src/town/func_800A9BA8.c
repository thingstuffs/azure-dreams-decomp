#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082D58.h"

extern M2C_UNK D_800A7360;
extern s32 D_800D0DF8[];



void func_800A7308(Rec_D_80082D58 *arg0, Rec_D_800E3D7C *arg1) {
    arg1->unk_14.as_s32 = D_800D0DF8[arg0->unk_90.as_s16];
    arg0->unk_50.as_pm = &D_800A7360;
}
