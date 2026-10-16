#include "common.h"
#include "m2c_compat.h"

s32 func_80017F5C(s32);                             /* extern */
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_80017FAC(void *arg0, s32 arg1) {
    if (D_80019BB0 == 4) {
        return 0;
    }
    M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) = func_80017F5C(D_80019BB4);
    return 1;
}
