#include "common.h"
#include "m2c_compat.h"

s32 func_80017E84(void) {
    return ~(s32 (*)())0x80017EA8() != 0;
}
