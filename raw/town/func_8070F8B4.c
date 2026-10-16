#include "common.h"
#include "m2c_compat.h"

void func_800188B4(s32 arg0) {
    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(s32), 0x280)(arg0 | 0x1000);
}
