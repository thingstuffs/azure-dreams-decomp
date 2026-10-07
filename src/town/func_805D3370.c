#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

extern s32 func_800191E8();
extern s32 D_8001A20C;
extern s32 D_8001A2E7;
extern s32 D_8001A348;
extern s32 D_8001A526;
extern s32 D_8001A5E8;
extern s32 D_8001A685;
extern s32 D_8001A8BC;
extern s32 D_8001A91D;


M2C_UNK *func_805D3370(s32 value, s32 unused, s32 selector) {
    s32 *result;
    s32 status;

    result = NULL;
    if (selector == 0x1B) {
        status = func_800191E8(value);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            result = &D_8001A91D;
        } else {
            result = &D_8001A8BC;
        }
    } else if (selector == 0x2C) {
        status = func_800191E8(value);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            result = &D_8001A2E7;
        } else {
            result = &D_8001A20C;
        }
    } else if (selector == 0x31) {
        status = func_800191E8(value);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            result = &D_8001A526;
        } else {
            result = &D_8001A348;
        }
    } else if (selector == 0x34) {
        status = func_800191E8(value);
        if (status == -0x30 || (status = func_800191E8()) == -0x38) {
            result = &D_8001A685;
        } else {
            result = &D_8001A5E8;
        }
    }
    return result;
}
