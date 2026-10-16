#include "common.h"
extern s32 func_800187DC(s32 mode);
s32 func_8001690C(void) {
    s32 result;
    if (func_800187DC(3) == 0) {
        result = func_800187DC(2) != 0;
    } else {
        result = 2;
    }
    return result;
}
