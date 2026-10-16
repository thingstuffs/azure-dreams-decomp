#include "common.h"
#include "m2c_compat.h"

void func_804083A0(void *arg0) {
    s32 temp_s1;

    temp_s1 = arg0 - 0x20;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32 (*)(s32, s32))0x80404C84(temp_s1, arg0 + 0xC);
    M2C_FIELD(arg0, s32 *, 0x24) = (s32 (*)(s32))0x804076C8(temp_s1);
    (M2C_UNK (*)())0x80400948();
    M2C_FIELD(arg0, s32 *, -0x10) = 0x804081AC;
}
