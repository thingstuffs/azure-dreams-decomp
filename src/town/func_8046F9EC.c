#include "common.h"

extern s32 func_800196F4();
extern s32 func_80019778();

s32 func_800169EC(void) {
    s32 result = 0;

    if ((func_800196F4(13, 3) != 0) ||
        (func_80019778(13, 3) != 0)) {
        result = 1;
    }
    return result;
}
