#include "common.h"

extern s32 D_80083168;
extern s32 func_80094B58(s32);

s32 func_80094BC8(s32 arg0, s32 arg1) {
    s32 result;

    result = func_80094B58(D_80083168);
    if ((s16)result == -1) {
        return -1;
    }
    return (result + arg1) & 0xFFF;
}
