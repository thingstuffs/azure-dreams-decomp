#include "common.h"
#include "m2c_compat.h"

s32 func_800AB464();                                /* extern */
extern M2C_UNK D_8015FE20;

void func_80162A64(void *arg0) {
    if (func_800AB464() > 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8015FE20;
    }
}
