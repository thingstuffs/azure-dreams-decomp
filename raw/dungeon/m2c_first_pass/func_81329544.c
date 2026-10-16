#include "common.h"
#include "m2c_compat.h"

void func_80170D44(void) {
    void *temp_v0;

    temp_v0 = *(s32 *)0x80174CDC + 0x20;
    M2C_FIELD(temp_v0, s8 *, 0x9B) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x96) = 0;
}
