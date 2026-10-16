#include "common.h"
#include "m2c_compat.h"

void func_80024A88(void *arg0, void *arg1, void *arg2) {
    void *temp_v1;

    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x52) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x52) | 0x8000);
    (M2C_UNK (*)(void *))0x800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
