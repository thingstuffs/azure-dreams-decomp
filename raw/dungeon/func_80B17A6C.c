#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80044A50(void *);                      /* extern */
M2C_UNK func_800478B8(void *, M2C_UNK *);           /* extern */
extern M2C_UNK D_80083160;
extern s32 D_80151A84;

void func_8015126C(void *arg0, void *arg2) {
    s16 temp_v0;

    if (M2C_FIELD(arg0, u8 *, 0x9A) == 0) {
        D_80151A84 = M2C_FIELD(arg2, s32 *, 8);
        func_800478B8(arg2, &D_80083160);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_80044A50(arg0 - 0x20);
            M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        }
    } else {
        M2C_FIELD(&D_80083160, u8 *, 0xA8) = (u8) (M2C_FIELD(&D_80083160, u8 *, 0xA8) + ((s32) (0x80 - M2C_FIELD(&D_80083160, u8 *, 0xA8)) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        M2C_FIELD(&D_80083160, u8 *, 0xA9) = (u8) (M2C_FIELD(&D_80083160, u8 *, 0xA9) + ((s32) (0x80 - M2C_FIELD(&D_80083160, u8 *, 0xA9)) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        M2C_FIELD(&D_80083160, u8 *, 0xAA) = (u8) (M2C_FIELD(&D_80083160, u8 *, 0xAA) + ((s32) (0x80 - M2C_FIELD(&D_80083160, u8 *, 0xAA)) / (s16) M2C_FIELD(arg0, s16 *, 0x96)));
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            *(s32 *)0x800814A0 |= 0x8000;
        }
    }
}
