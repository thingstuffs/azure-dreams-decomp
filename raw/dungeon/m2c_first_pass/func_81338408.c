#include "common.h"
#include "m2c_compat.h"

s32 func_8016F408(s32 arg0) {
    return M2C_FIELD(*(void **)0x80175D54, u8 *, 0xBA) == arg0;
}
