#include "common.h"
#include "m2c_compat.h"

extern s32 D_00000DF8;

void func_80000C8C(void) {
    D_00000DF8 = (D_00000DF8 * 8) + *(s32 *)0xE60;
}
