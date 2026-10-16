#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */

void func_800CE62C(void *arg0, void *arg1) {
    u16 temp_v0;
    u32 temp_v1;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C4174();
    }
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) (M2C_FIELD(arg0, s16 *, 0x84) - M2C_FIELD(arg1, s16 *, 2)) / 2));
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x86) - M2C_FIELD(arg1, s16 *, 6);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s16) -M2C_FIELD(arg1, s16 *, 0xA) / 2));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (temp_v1 + (temp_v1 >> 0x1F)) >> 1));
}
