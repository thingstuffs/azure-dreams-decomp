#include "common.h"

extern s32 func_800B29A4(void *arg0);

s32 func_8009F6E4(void) {
    s32 result;
    s32 ret;

    result = func_800B29A4((void *)0x8001029C);
    ret = -1;
    if (result >= 20) {
        return ret;
    }
    return result;
}
