#include "common.h"
#include "m2c_compat.h"

void func_80016228(void) {
    void *temp_v1;

    temp_v1 = *(void **)0x80016000;
    M2C_FIELD(((M2C_FIELD(temp_v1, s32 *, 8) * 8) + M2C_FIELD(temp_v1, s32 *, 0x40)), s8 *, 4) = 3;
}
