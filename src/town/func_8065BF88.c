#include "common.h"
#include "m2c_compat.h"

extern void * D_80016000;
u8 func_80016788(void) {
    return M2C_FIELD(M2C_FIELD(D_80016000, void **, 0x38), u8 *, 0x33BA);
}
