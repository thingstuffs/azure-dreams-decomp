#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80093BAC;
extern M2C_UNK *D_800FE5D8;

s32 func_80093C40(void) {
    D_800FE5D8 = &D_80093BAC;
    return 0;
}
