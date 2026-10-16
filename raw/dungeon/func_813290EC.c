#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_8016F78C;

void func_801708EC(void *arg0, void *arg3) {
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8016F78C;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
}
