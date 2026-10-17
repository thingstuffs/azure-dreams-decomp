#include "common.h"
#include "m2c_compat.h"

extern void *D_80016000;

void func_8051FD58(s32 arg0) {
    M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), M2C_UNK (**)(s32), 0x280)(arg0 | 0x1000);
}
