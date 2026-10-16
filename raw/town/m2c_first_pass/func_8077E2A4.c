#include "common.h"
#include "m2c_compat.h"

s32 func_80016AA4(void) {
    return ~(s32 (*)())0x80016AC8() != 0;
}
