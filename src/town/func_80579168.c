#include "common.h"
#include "m2c_compat.h"

extern void * D_80016000;
s16 func_80016168(void) {
    return M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x38), s16 *, 0x35C0);
}
