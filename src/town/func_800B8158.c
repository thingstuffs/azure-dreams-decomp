#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

extern s32 D_800814A8;


void func_800B58B8(s32 *arg0, Rec_D_800E3D7C *arg1) {
    s32 *var_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    var_a0 = arg0;
    temp_v0 = arg1->unk_4C.as_s32;
    if (temp_v0 != 0) {
        *var_a0 = temp_v0;
        var_a0 += 1;
    }
    temp_v0_2 = arg1->unk_50.at00_s32.v;
    if (temp_v0_2 != 0) {
        *var_a0 = temp_v0_2;
        var_a0 += 1;
    }
    if (arg1 == D_800814A8) {
        temp_a1 = arg1->unk_D8;
        if (temp_a1 != 0) {
            *var_a0 = temp_a1;
        }
    }
}
