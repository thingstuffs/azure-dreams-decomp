#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80017AFC;

void func_80016360(void) {
    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *), 0x218)(&D_80017AFC);
}
