#include "common.h"
#include "m2c_compat.h"

void func_800DA660(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    if (((s32 (*)())0x800AC82C() != 0) && (((s32 (*)(M2C_UNK, M2C_UNK))0x800AD9B4(arg2, arg3) << 0x10) > 0)) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0x800D8C64;
    }
}
