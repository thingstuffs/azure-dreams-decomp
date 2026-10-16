#include "common.h"
#include "m2c_compat.h"

s32 func_800AB280();                                /* extern */
extern M2C_UNK D_8014C514;

void func_8014E7B8(void *arg0) {
    if (func_800AB280() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014C514;
    }
}
