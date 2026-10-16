#include "common.h"
#include "m2c_compat.h"

void func_80701274(void) {
    *(s32 *)0x80700A3C = (*(s32 *)0x80700A3C * 8) + *(s32 *)0x807013AC;
}
