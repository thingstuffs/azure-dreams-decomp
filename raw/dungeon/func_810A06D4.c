#include "common.h"
#include "m2c_compat.h"

s32 func_8015DED4(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, u8 *, 0xAE) == 0) {
        return 0;
    }
    M2C_FIELD(arg0, u8 *, 0xAE) = 0U;
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) & 0xBFFFFFFF);
    return 1;
}
