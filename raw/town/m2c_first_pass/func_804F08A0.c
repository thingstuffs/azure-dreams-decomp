#include "common.h"
#include "m2c_compat.h"

s32 func_800168A0(void) {
    return ~(s32 (*)())0x800168C4() != 0;
}
