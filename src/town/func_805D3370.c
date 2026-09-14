#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

extern s32 func_800191E8();
extern M2C_UNK D_8001A20C;
extern M2C_UNK D_8001A2E7;
extern M2C_UNK D_8001A348;
extern M2C_UNK D_8001A526;
extern M2C_UNK D_8001A5E8;
extern M2C_UNK D_8001A685;
extern M2C_UNK D_8001A8BC;
extern M2C_UNK D_8001A91D;




M2C_UNK *func_805D3370(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK *var_v1;
    s32 status;

    var_v1 = NULL;
    if (arg2 != 0x1B) {
        goto case_2c;
    }
    status = func_800191E8(arg0);
    if (status == -0x30) {
        goto case_1_success;
    }
    status = func_800191E8();
    if (status != -0x38) {
        goto case_1_other;
    }
case_1_success:
    var_v1 = &D_8001A91D;
    goto done;
case_1_other:
    var_v1 = &D_8001A8BC;
    goto done;

case_2c:
    if (arg2 != 0x2C) {
        goto case_31;
    }
    status = func_800191E8(arg0);
    if (status == -0x30) {
        goto case_2_success;
    }
    status = func_800191E8();
    if (status != -0x38) {
        goto case_2_other;
    }
case_2_success:
    var_v1 = &D_8001A2E7;
    goto done;
case_2_other:
    var_v1 = &D_8001A20C;
    goto done;

case_31:
    if (arg2 != 0x31) {
        goto case_34;
    }
    status = func_800191E8(arg0);
    if (status == -0x30) {
        goto case_3_success;
    }
    status = func_800191E8();
    if (status != -0x38) {
        goto case_3_other;
    }
case_3_success:
    var_v1 = &D_8001A526;
    goto done;
case_3_other:
    var_v1 = &D_8001A348;
    goto done;

case_34:
    if (arg2 != 0x34) {
        goto done;
    }
    status = func_800191E8(arg0);
    if (status != -0x30) {
        status = func_800191E8();
        if (status != -0x38) {
            goto case_4_other;
        }
    }
    var_v1 = &D_8001A685;
    goto done;
case_4_other:
    var_v1 = &D_8001A5E8;

done:
    return var_v1;
}
