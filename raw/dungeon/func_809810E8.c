#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */

void func_801648E8(void *arg0, void *arg2) {
    s16 temp_v0;
    s32 temp_lo;

    temp_lo = (s32) (M2C_FIELD(arg0, s16 *, 0x96) << 7) / (s16) M2C_FIELD(arg0, s16 *, 0xAA);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
    func_800478B8(arg2);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
