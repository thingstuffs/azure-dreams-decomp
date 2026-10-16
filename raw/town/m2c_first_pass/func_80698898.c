#include "common.h"
#include "m2c_compat.h"

s32 func_80017898(void) {
    return ~(s32 (*)())0x800178BC() != 0;
}
