#include "common.h"
#include "m2c_compat.h"

s32 func_80170BAC(void) {
    return (*(u16 *)0x80013714 & 0x10) != 0;
}
