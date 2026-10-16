#include "common.h"
#include "m2c_compat.h"

s32 func_80018468(void) {
    return ~(s32 (*)())0x8001848C() != 0;
}
