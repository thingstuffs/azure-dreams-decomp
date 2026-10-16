#include "common.h"
#include "m2c_compat.h"

s32 func_800AC480();                                /* extern */
extern M2C_UNK D_80164E94;

void func_80168378(void *arg0) {
    if (func_800AC480() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164E94;
    }
}
