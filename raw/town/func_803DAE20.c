#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016470;
extern M2C_UNK D_800164D0;

void func_80017620(s32 arg0) {
    M2C_FIELD(&D_800164D0, s32 *, 0x20) = (s32) *((arg0 * 0xC) + &D_80016470);
}
