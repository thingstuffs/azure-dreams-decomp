#include "common.h"
#include "m2c_compat.h"

extern s32 D_80174CD8;

void func_8017110C(void) {
    void *temp_v0;

    temp_v0 = D_80174CD8 + 0x20;
    M2C_FIELD(temp_v0, s8 *, 0x9B) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x96) = 0;
}
