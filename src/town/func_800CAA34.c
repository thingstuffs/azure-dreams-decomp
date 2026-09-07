#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800AB030();                             /* extern */
s32 func_800C2AE8();                          /* extern */


void func_800C8194(s32 arg0, Rec_D_800E3D7C *arg1) {
    s32 temp_v0;
    s32 temp_s0;

    temp_s0 = func_800C2AE8(arg1);
    temp_v0 = func_800AB030(arg0);
    temp_v0 -= 0x4C;
    arg1->unk_08.at02_s16.v = (s16) (temp_s0 + temp_v0);
}
