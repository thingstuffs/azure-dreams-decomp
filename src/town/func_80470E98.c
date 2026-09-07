#include "common.h"

s32 func_8001A220();                                /* extern */

s32 func_80017E98(void) {
    return func_8001A220() < -0x2F;
}
