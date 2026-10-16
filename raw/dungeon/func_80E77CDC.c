#include "common.h"
#include "m2c_compat.h"

s32 func_800AB464();                                /* extern */
extern M2C_UNK D_8015F6F4;

void func_801634DC(void *arg0) {
    if (func_800AB464() > 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015F6F4;
    }
}
