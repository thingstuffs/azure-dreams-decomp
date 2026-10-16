#include "common.h"
#include "m2c_compat.h"

s32 func_800AC7EC();                                /* extern */
extern M2C_UNK D_8016F78C;

void func_80170A1C(void *arg0) {
    if (func_800AC7EC() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016F78C;
    }
}
