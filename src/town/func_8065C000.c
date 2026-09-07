#include "common.h"

extern s32 func_80016788();
extern s32 func_80016CB4();

s32 func_8065C000(void) {
    s32 less_than_three;

    if (func_80016CB4() == 0) {
        goto return_one;
    }
    less_than_three = func_80016788() < 3;
    if (less_than_three != 0) {
        return 0;
    }
return_one:
    return 1;
}
