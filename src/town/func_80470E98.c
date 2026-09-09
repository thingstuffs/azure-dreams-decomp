#include "common.h"

s32 func_8001A220(s32, s32, s32);                                /* extern */

s32 func_80017E98(s32 arg0, s32 arg1, s32 arg2) {
    return func_8001A220(arg0, arg1, arg2) < -0x2F;
}
