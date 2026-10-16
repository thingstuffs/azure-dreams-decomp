#include "common.h"
#include "m2c_compat.h"

void func_80700D24(void) {
    *(s32 *)0x80700768 = (*(s32 *)0x80700768 * 8) + *(s32 *)0x80700E44;
}
