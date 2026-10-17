#include "common.h"
#include "m2c_compat.h"

extern void *D_80016000;
extern M2C_UNK D_80018A7C;

void func_8069752C(void) {
    M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK *), 0x218)(&D_80018A7C);
}
