#include "common.h"
#include "m2c_compat.h"

s32 func_80016728(void) {
    return ~(s32 (*)())0x8001674C() != 0;
}
