#include "common.h"

extern s32 func_80016250(s32);
extern s32 D_8001967C;
extern s32 D_800196F4[];

s32 func_800169B4(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = 0;

    if (arg2 == 8) {
        result = func_80016250(D_800196F4[D_8001967C]);
    }
    return result;
}
