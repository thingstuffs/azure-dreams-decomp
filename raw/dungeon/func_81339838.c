#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D68;

void func_80170838(void) {
    void *temp_v1;

    temp_v1 = D_80175D68 + 0x20;
    M2C_FIELD(temp_v1, s16 *, 0x18) = 0;
    M2C_FIELD(temp_v1, u16 *, 0x12) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x12) + 1);
}
