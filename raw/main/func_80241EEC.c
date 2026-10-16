#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80024E44(void *);                      /* extern */
extern s32 D_800814A0;

void func_80024EEC(s32 arg0) {
    void *temp_s0;

    if (arg0 != 0) {
        temp_s0 = arg0 + 0x20;
        func_80024E44(temp_s0);
        M2C_FIELD(temp_s0, u16 *, -2) = (u16) (M2C_FIELD(temp_s0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
