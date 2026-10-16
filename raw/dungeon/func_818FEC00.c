#include "common.h"
#include "m2c_compat.h"

s32 func_80069EF8();                                /* extern */
s16 func_800BCB04(u16, u16, s16);                   /* extern */
extern s16 D_80025E80;
extern s32 D_800814A0;

void func_80024400(void *arg0, void *arg1) {
    u16 temp_v0;

    D_80025E80 = 1;
    if ((s16) M2C_FIELD(arg1, u16 *, 0xA) < func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) + 2))) {
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0x20000 + (func_80069EF8() & 0xFFF));
    }
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x32) - 8;
    M2C_FIELD(arg0, u16 *, 0x32) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
