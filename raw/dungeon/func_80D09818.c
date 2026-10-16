#include "common.h"
#include "m2c_compat.h"

s32 func_800ABDBC();                                /* extern */
extern M2C_UNK D_801544BC;

void func_80157018(void *arg0) {
    if (func_800ABDBC() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801544BC;
    }
}
