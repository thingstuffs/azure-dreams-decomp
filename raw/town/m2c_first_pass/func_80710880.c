#include "common.h"
#include "m2c_compat.h"

s32 func_80019880(void) {
    return ~(s32 (*)())0x800198A4() != 0;
}
