#include "common.h"
#include "m2c_compat.h"

u8 func_80016788(void) {
    return M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x38), u8 *, 0x33BA);
}
