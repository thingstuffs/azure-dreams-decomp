#include "common.h"

extern s32 D_80100E2C[];

s32 func_800A630C(void) {
    s32 value = D_80100E2C[0];
    D_80100E2C[0] = 0;
    return value & 0x7FFFFFFF;
}
