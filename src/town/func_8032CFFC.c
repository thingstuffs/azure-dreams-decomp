#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_80019D44();
extern M2C_UNK func_80019DFC();
extern M2C_UNK D_8001BB7C;
extern M2C_UNK D_8001C358;
extern u8 D_8001E891;

s32 func_800177FC(s32 arg0, s32 arg1, M2C_UNK arg2) {
    M2C_UNK result;

    result = func_80019DFC(&D_8001BB7C, &D_8001C358, arg0, arg2);
    return func_80019D44(&D_8001BB7C, arg0, arg2) != 0
        ? (s32)&D_8001E891
        : result;
}
