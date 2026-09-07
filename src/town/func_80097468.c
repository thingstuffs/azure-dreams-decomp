#include "common.h"

extern s32 D_80083168;
extern s32 func_80094B58(s32);
extern s32 func_80094C08(void);

s32 func_80094BC8(s32 arg0, s32 arg1) {
    s32 payload;
    s32 result;

    result = func_80094B58(D_80083168);
    if ((s16)result == -1) {
        return -1;
    }
    payload = result + arg1;
    return payload & 0xFFF;
}
