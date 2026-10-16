#include "common.h"
#include "m2c_compat.h"

s32 func_800AC7EC();                                /* extern */
extern M2C_UNK D_801714D4;

void func_801740A8(void *arg0) {
    if (func_800AC7EC() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_801714D4;
    }
}
