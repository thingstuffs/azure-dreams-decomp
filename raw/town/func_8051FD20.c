#include "common.h"
#include "m2c_compat.h"

extern void *D_80016000;

void func_8051FD20(void) {
    M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x280)(0x1700);
}
