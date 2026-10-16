#include "common.h"
#include "m2c_compat.h"

void func_80165030(void *arg0, void *arg2) {
    u16 temp_v0;
    u16 var_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 2) - 1;
    M2C_FIELD(arg0, u16 *, 2) = temp_v0;
    if ((s16) temp_v0 >= 5) {
        var_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x200;
    } else {
        var_v0 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x200;
    }
    M2C_FIELD(arg2, u16 *, 0x1E) = var_v0;
    M2C_FIELD(arg2, u16 *, 0x1C) = var_v0;
    if ((s16) M2C_FIELD(arg0, u16 *, 2) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(void *)0x800814A0 = (s32) (*(void *)0x800814A0 | 0x8000);
    }
}
