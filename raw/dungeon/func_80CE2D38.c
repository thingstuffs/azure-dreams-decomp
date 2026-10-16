#include "common.h"
#include "m2c_compat.h"

s32 func_800AB378();                                /* extern */
s32 func_800AD9B4(M2C_UNK, M2C_UNK);                /* extern */
extern M2C_UNK D_8014CF20;
extern M2C_UNK D_8014FB98;

void func_8014E538(void *arg0, M2C_UNK arg2, M2C_UNK arg3) {
    M2C_UNK *var_v0;

    if ((func_800AB378() != 0) && ((func_800AD9B4(arg2, arg3) << 0x10) > 0)) {
        if (M2C_FIELD(arg0, u8 *, 0xA7) != 0) {
            var_v0 = &D_8014FB98;
        } else {
            var_v0 = &D_8014CF20;
        }
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = var_v0;
    }
}
