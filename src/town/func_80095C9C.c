#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC();                                /* extern */
extern M2C_UNK (*D_800FE5D8)(s32, M2C_UNK, M2C_UNK);

void func_800933FC(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_800352FC() == 0) {
        D_800FE5D8(arg0, arg1, arg2);
    }
}
