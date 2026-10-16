#include "common.h"
#include "m2c_compat.h"

extern void * D_80016000;
void func_80016200(void) {
    void *temp_v1;

    temp_v1 = D_80016000;
    M2C_FIELD(((M2C_FIELD(temp_v1, s32 *, 8) * 8) + M2C_FIELD(temp_v1, s32 *, 0x40)), s8 *, 4) = 2;
}
