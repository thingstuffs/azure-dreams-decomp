#include "common.h"
#include "m2c_compat.h"

void func_80024928(void *arg0, void *arg2) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0xE) = (u16) (M2C_FIELD(temp_v1, u16 *, 0xE) | 0x8000);
    (M2C_UNK (*)(void *))0x800478B8(arg2);
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) (((s32 (*)())0x80069EF8() & 0x7F) + 0x20);
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) (((s32 (*)())0x80069EF8() & 0x7F) + 0x20);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) (((s32 (*)())0x80069EF8() & 0x7F) + 0x20);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
