#include "common.h"
#include "m2c_compat.h"

void func_80016808(void) {
    M2C_FIELD(M2C_FIELD(*(void **)0x80016000, void **, 0x40), s8 *, 0x6F) = 3;
}
