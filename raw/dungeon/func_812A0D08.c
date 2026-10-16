#include "common.h"
#include "m2c_compat.h"

s32 func_800AA030();                                /* extern */
s32 func_800AC66C(M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_8014C514;

void func_8014D508(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    if ((func_800AA030() != 0) && ((func_800AC66C(arg2, arg3) << 0x10) > 0)) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014C514;
    }
}
