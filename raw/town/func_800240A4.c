#include "common.h"
#include "m2c_compat.h"

extern void *D_80100AF0;

s32 func_800C1804(void) {
    return M2C_FIELD(D_80100AF0, u16 *, 0x1E) & 0x8000;
}
