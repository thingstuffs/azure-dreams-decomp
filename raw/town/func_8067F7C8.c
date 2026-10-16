#include "common.h"
#include "m2c_compat.h"

extern u32 D_800188C8;

s32 func_800167C8(void) {
    return (u32) M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x38), u32 *, 0x2D5C) >= (u32) D_800188C8;
}
