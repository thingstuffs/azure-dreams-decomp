#include "common.h"
#include "m2c_compat.h"

void func_80408394(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = arg2;
}
