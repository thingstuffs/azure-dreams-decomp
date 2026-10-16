#include "common.h"
#include "m2c_compat.h"

s32 func_800AC5C8();                                /* extern */
extern M2C_UNK D_801533A8;

void func_801563B4(void *arg0) {
    if (func_800AC5C8() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801533A8;
    }
}
