#include "common.h"
#include "m2c_compat.h"

s32 func_800ACE34();                                /* extern */
extern M2C_UNK D_80152E54;

void func_80155BCC(void *arg0) {
    if (func_800ACE34() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80152E54;
    }
}
