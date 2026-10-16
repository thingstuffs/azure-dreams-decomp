#include "common.h"
#include "m2c_compat.h"

void func_80016128(void) {
    *(s32 *)0x800174D8 = 0x80017404;
    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x1C), s32 *, 0x40) = 0x8001770A;
}
