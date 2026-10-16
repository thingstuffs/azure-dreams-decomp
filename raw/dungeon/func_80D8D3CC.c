#include "common.h"
#include "m2c_compat.h"

s32 func_800ABDBC();                                /* extern */
extern M2C_UNK D_8014DF1C;

void func_80150BCC(void *arg0) {
    if (func_800ABDBC() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8014DF1C;
    }
}
