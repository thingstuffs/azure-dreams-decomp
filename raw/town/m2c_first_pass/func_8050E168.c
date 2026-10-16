#include "common.h"
#include "m2c_compat.h"

s16 func_80016168(void) {
    return M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x38), s16 *, 0x35BE);
}
