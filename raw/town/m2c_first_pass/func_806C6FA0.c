#include "common.h"
#include "m2c_compat.h"

s32 func_80017FA0(void) {
    return ~(s32 (*)())0x80017FC4() != 0;
}
