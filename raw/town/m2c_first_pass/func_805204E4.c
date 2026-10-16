#include "common.h"
#include "m2c_compat.h"

s32 func_80017CE4(void) {
    return ~(s32 (*)())0x80017D08() != 0;
}
