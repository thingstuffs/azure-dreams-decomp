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
    if (arg2 == 0x1B) {
        status = func_800191E8(arg0);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            var_v1 = &D_8001A91D;
        } else {
            var_v1 = &D_8001A8BC;
        }
    } else if (arg2 == 0x2C) {
        status = func_800191E8(arg0);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            var_v1 = &D_8001A2E7;
        } else {
            var_v1 = &D_8001A20C;
        }
    } else if (arg2 == 0x31) {
        status = func_800191E8(arg0);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            var_v1 = &D_8001A526;
        } else {
            var_v1 = &D_8001A348;
        }
    } else if (arg2 == 0x34) {
        status = func_800191E8(arg0);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            var_v1 = &D_8001A685;
        } else {
            var_v1 = &D_8001A5E8;
        }
    }
    return var_v1;
}
