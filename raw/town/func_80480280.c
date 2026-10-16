#include "common.h"
#include "m2c_compat.h"

void func_80016280(void) {
    void *temp_a0;

    *M2C_FIELD(*(void **)0x80016000, s32 **, 0x1C) = 1;
    temp_a0 = *(void **)0x80016000;
    M2C_FIELD(M2C_FIELD(temp_a0, s32 **, 0x1C), s32 *, 4) = 0x2A;
    M2C_FIELD(M2C_FIELD(temp_a0, s32 **, 0x1C), s32 *, 8) = 8;
}
