#include "common.h"
#include "m2c_compat.h"

s32 func_800AC010();                                /* extern */
s32 func_800AD9B4(M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_80164E54;

void func_80167FBC(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    if ((func_800AC010() != 0) && ((func_800AD9B4(arg2, arg3) << 0x10) > 0)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164E54;
    }
}
