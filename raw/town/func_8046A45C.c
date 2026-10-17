#include "common.h"
#include "m2c_compat.h"

s32 func_8001A79C();                                /* extern */
extern void *D_8001E950;

s32 func_8046A45C(void *arg0, s32 arg1) {
    if (M2C_FIELD(D_8001E950, u8 *, 5) != 4) {
        return 1;
    }
    M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) = func_8001A79C();
    return 0;
}
