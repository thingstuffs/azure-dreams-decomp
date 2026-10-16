#include "common.h"
#include "m2c_compat.h"

void func_8014FF38(void *arg0) {
    s16 temp_v1;
    u16 temp_v0;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xC);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0xE) - 1;
        M2C_FIELD(arg0, u16 *, 0xE) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg0, s16 *, 0xC) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xC) + 1);
            return;
        }
        return;
    case 1:
        if ((u8) M2C_FIELD(arg0, u8 *, 8) < 0x11U) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
            return;
        }
        M2C_FIELD(arg0, u8 *, 8) = (s32) ((s32) M2C_FIELD(arg0, u8 *, 8) + 0xFFEFEFF0);
        break;
    }
}
