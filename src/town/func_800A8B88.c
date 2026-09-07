#include "common.h"
#include "m2c_compat.h"

extern s32 D_80082E88;
extern s32 D_80100E2C;

s32 func_800A62E8(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    D_80100E2C = arg3;
    return (D_80082E88 - 0xC) & 0x7FFFFFFF;
}
