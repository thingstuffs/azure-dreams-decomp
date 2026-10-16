#include "common.h"
#include "m2c_compat.h"

s32 func_800AB280();                                /* extern */
extern M2C_UNK D_80164514;

void func_801667B8(void *arg0) {
    if (func_800AB280() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164514;
    }
}
