#include "common.h"
#include "m2c_compat.h"

s32 func_800AAA74();                                /* extern */
extern M2C_UNK D_8016A514;

void func_8016BE8C(void *arg0) {
    if (func_800AAA74() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016A514;
    }
}
