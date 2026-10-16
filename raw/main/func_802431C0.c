#include "common.h"
#include "m2c_compat.h"

void func_800261C0(void *arg0) {
    u16 temp_v1;
    void *temp_a1;

    temp_a1 = arg0 - 0x20;
    temp_v1 = M2C_FIELD(temp_a1, u16 *, 0x1E);
    if (temp_v1 & 0x2000) {
        M2C_FIELD(temp_a1, u16 *, 0x1E) = (u16) (temp_v1 & 0xDFFF);
        M2C_FIELD(arg0, s32 *, -0x10) = (s32) M2C_FIELD(arg0, s32 *, 0x34);
    }
}
