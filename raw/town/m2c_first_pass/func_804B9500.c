#include "common.h"
#include "m2c_compat.h"

s32 func_80017D00(void) {
    return ~(s32 (*)())0x80017D24() != 0;
}
