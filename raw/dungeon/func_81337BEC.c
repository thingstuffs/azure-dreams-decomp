#include "common.h"
#include "m2c_compat.h"

s32 func_8016EBEC(void) {
    return (*(u16 *)0x80013714 & 0x10) != 0;
}
