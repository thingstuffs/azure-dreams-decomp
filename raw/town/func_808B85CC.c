#include "common.h"
#include "m2c_compat.h"

extern s32 D_00004160;

void func_80003DCC(void) {
    D_00004160 = (D_00004160 * 8) + *(s32 *)0x4608;
}
