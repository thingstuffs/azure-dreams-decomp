#include "common.h"

extern s16 func_80053DA8(s32 arg0);
extern u16 D_80013714;

s32 func_800A56E0(s32 arg0) {
    s32 result;

    if (D_80013714 & 2) {
        result = 0;
    } else {
        result = func_80053DA8(arg0 & 0xFFFF);
    }
    return result;
}
