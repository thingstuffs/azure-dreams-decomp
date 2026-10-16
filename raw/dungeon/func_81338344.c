#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A32A4(void *);                      /* extern */
extern s32 D_80175D54;

void func_8016F344(void) {
    void *temp_s0;

    if (D_80175D54 != 0) {
        temp_s0 = D_80175D54 + 0x20;
        func_800A32A4(temp_s0);
        M2C_FIELD(temp_s0, u16 *, -2) = (u16) (M2C_FIELD(temp_s0, u16 *, -2) | 0x8000);
        D_80175D54 = 0;
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
