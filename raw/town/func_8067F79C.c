#include "common.h"
#include "m2c_compat.h"

s32 func_80016A4C(M2C_UNK *, M2C_UNK);              /* extern */
extern s32 D_800188C8;
extern M2C_UNK D_800188D0;

void func_8001679C(void) {
    D_800188C8 = func_80016A4C(&D_800188D0, 1);
}
