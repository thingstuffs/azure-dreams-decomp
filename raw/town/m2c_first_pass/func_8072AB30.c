#include "common.h"
#include "m2c_compat.h"

s32 func_80016B30(void) {
    return ~(s32 (*)())0x80016B54() != 0;
}
