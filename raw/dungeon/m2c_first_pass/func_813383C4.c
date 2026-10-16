#include "common.h"
#include "m2c_compat.h"

void func_8016F3C4(void) {
    void *temp_v1;

    temp_v1 = *(s32 *)0x80175D54 + 0x20;
    M2C_FIELD(temp_v1, s16 *, 0x96) = 0;
    M2C_FIELD(temp_v1, u8 *, 0x9A) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x9A) + 1);
}
