#include "common.h"
#include "m2c_compat.h"

void func_800DA808(void *arg0) {
    if ((s32 (*)())0x800AC7EC() > 0) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0x800D8C64;
    }
}
