#include "common.h"
#include "m2c_compat.h"

s32 func_800AB378();                                /* extern */
s32 func_800AD9B4(M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_801724BC;

void func_80174360(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    if ((func_800AB378() != 0) && ((func_800AD9B4(arg2, arg3) << 0x10) > 0)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801724BC;
    }
}
