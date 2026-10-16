#include "common.h"
#include "m2c_compat.h"

void func_800DA728(void *arg0) {
    if ((s32 (*)())0x800AC480() != 0) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0x800D8C64;
    }
}
