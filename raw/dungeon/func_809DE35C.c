#include "common.h"
#include "m2c_compat.h"

s32 func_800AC480();                                /* extern */
extern M2C_UNK D_8015EE54;

void func_80161B5C(void *arg0) {
    if (func_800AC480() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015EE54;
    }
}
