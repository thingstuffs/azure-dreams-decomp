#include "common.h"
#include "m2c_compat.h"

s16 func_8001A220(void) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x24), void **, 0x68), void **, 8), s16 *, 0xA);
}
