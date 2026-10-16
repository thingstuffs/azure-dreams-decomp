#include "common.h"
#include "m2c_compat.h"

s32 func_80016BD0(void) {
    return ~(s32 (*)())0x80016BF4() != 0;
}
