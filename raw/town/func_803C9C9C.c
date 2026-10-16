#include "common.h"
#include "m2c_compat.h"

s32 func_8001AB68();                                /* extern */
extern void *D_8001E950;

s32 func_8001AC9C(void *arg0, s32 arg1) {
    if (M2C_FIELD(D_8001E950, u8 *, 5) != 9) {
        return 1;
    }
    M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) = func_8001AB68();
    return 0;
}
