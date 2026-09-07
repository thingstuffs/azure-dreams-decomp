#include "common.h"

extern s32 D_80019178[];

s32 func_8051EA90(void) {
    s32 value;

    value = D_80019178[0] + 1;
    D_80019178[0] = value;
    return value >= 3;
}
