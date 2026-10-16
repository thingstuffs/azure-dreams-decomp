#include "common.h"
#include "m2c_compat.h"

s16 func_800BCB04(u16, u16, s16);                   /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;

void func_80168E98(void *arg0, void *arg1) {
    s16 temp_v0;

    if ((s16) M2C_FIELD(arg1, u16 *, 0xA) < func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg1, u16 *, 0xA) + 2))) {
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - ((*((M2C_FIELD(arg0, s16 *, 0x14) * 2) + &D_8006CCD8) * M2C_FIELD(arg0, s16 *, 0x32)) << 0xB));
        M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - ((*((M2C_FIELD(arg0, s16 *, 0x14) * 2) + &D_8006CCE8) * M2C_FIELD(arg0, s16 *, 0x32)) << 0xB));
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + ((0xC0 - M2C_FIELD(arg0, s16 *, 0x32)) << 0xA));
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 8;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
