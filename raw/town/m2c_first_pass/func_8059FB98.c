#include "common.h"
#include "m2c_compat.h"

s32 func_80017B98(void) {
    return ~(s32 (*)())0x80017BBC() != 0;
}
