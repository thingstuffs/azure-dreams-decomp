#include "common.h"
#include "m2c_compat.h"

s32 func_800ABAEC();                                /* extern */
extern M2C_UNK D_80164514;

void func_801667F0(void *arg0) {
    if (func_800ABAEC() != 0) {
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164514;
    }
}
