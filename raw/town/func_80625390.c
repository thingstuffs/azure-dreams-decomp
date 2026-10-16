#include "common.h"
#include "m2c_compat.h"

s32 func_80016390(void) {
    return M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x1C), s32 *, 0x38) != 0;
}
