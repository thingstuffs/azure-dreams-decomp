#include "common.h"
#include "m2c_compat.h"

s32 func_80016970(void) {
    return ~(s32 (*)())0x80016994() != 0;
}
