#include "common.h"
#include "m2c_compat.h"

void func_8016F3E8(s8 arg0) {
    void *temp_v0;

    temp_v0 = *(s32 *)0x80175D54 + 0x20;
    M2C_FIELD(temp_v0, s8 *, 0x9A) = arg0;
    M2C_FIELD(temp_v0, s8 *, 0x9B) = 0;
    M2C_FIELD(temp_v0, s16 *, 0x96) = 0;
}
